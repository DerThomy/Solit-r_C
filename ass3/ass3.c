//-----------------------------------------------------------------------------
// ass3.c
//
// Solitaire
//
// Group: 04 - study assistant Mathias Kahr
//
// Authors: Simon Joham 11814175
// Thomas Köhler 11827322
//
// Latest Changes: 13.12.2018 (by Simon Joham)
//-----------------------------------------------------------------------------
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Return values of the program
typedef enum _ReturnValue_
{
  EVERYTHING_OK = 0,
  INVALID_ARGUMENTS = 1,
  OUT_OF_MEMORY = 2,
  INVALID_FILE = 3
} ReturnValue;

//Array position of Stacks
typedef enum _StackType_
{
  PICK_OFF_STACK = 0,
  GAME_STACK_1 = 1,
  GAME_STACK_2 = 2,
  GAME_STACK_3 = 3,
  GAME_STACK_4 = 4,
  DEPOSIT_STACK_1 = 5,
  DEPOSIT_STACK_2 = 6
} StackType;

//Stores Card
typedef struct _Card_
{
  char color_;
  char *value_;
  struct _Card_ *next_;
  struct _Card_ *prev_;
}Card;

//Stores a card stack and which type of stack it is (e.g. GameStack)
typedef struct CardStack_
{
  struct _Card_ *top_card_;
  struct _Card_ *bottom_card_;
}CardStack;

void playLoop(CardStack **stacks);
int testForWin(CardStack **stacks);
int countCardStack(CardStack *stack);
char **checkForMoveCommand(char *input);
int checkForCardValue(char *input);
char *getInput();
void initStacks(CardStack **stacks);
void freeStacks(CardStack **stacks);
void renderStacks(CardStack **stacks);
void printRows(CardStack **stacks);
void printPickOffStack(Card *card);
void printOtherStacks(Card *card, int stack);
void *mallocCheck(size_t size);
void copyCard(Card *dest, Card *src);
void addTop(CardStack *stack, char color, char *value);
void delTop(CardStack *stack);
int findCard(CardStack *stack, Card *spec_card);
int move(CardStack **stacks, int dest_stack, char color, char *value);
int compareCards(Card *card1, Card *card2);
int getCardValueAsInt(char *value);
int areCardsSorted(Card *cards, int isGameStack);
void printCard(Card *card);
ReturnValue readCardsFromPath(char *path, CardStack **stacks);
ReturnValue readCardsFromFile(FILE *file, CardStack **stacks);
ReturnValue checkCards(char **input, int lines);
ReturnValue addCardsToStacks(char **cards, CardStack **stacks);
char *getCardValue(char *card);
char *copyString(char *string);
ReturnValue printErrorMessage(ReturnValue return_value);

//------------------------------------------------------------------------------
///
/// Entry function of the program for ass3
///
/// @param argc number of arguments
/// @param argv program arguments
///
/// @return value of ReturnValue which defines type of error
//
int main(int argc, char **argv)
{
  if(argc != 2)
  {
    return printErrorMessage(INVALID_ARGUMENTS);
  }

  CardStack **stacks = mallocCheck(sizeof(CardStack *) * 7);
  initStacks(stacks);

  ReturnValue return_value = readCardsFromPath(argv[1], stacks);

  if(return_value == EVERYTHING_OK)
  {
    playLoop(stacks);
  }
  freeStacks(stacks);

  return printErrorMessage(return_value);
}

int areCardsSorted(Card *cards, int isGameStack)
{
  if(isGameStack == 1)
  {
    Card *copy_card = cards;
    while(copy_card->prev_ != NULL)
    {
      //(*stacks[dest_stack]->top_card_->value_)-1
      if((*copy_card->value_)-1 != *copy_card->prev_->value_)
      {
        return 0;
      }
      copy_card = copy_card->prev_;
    }
  }
  else
  {
    Card *copy_card = mallocCheck(sizeof(Card *));
    copy_card = cards;
    while(copy_card->prev_ != NULL)
    {
      //(*stacks[dest_stack]->top_card_->value_)-1
      if((*copy_card->value_)+1 != *copy_card->prev_->value_)
      {
        return 0;
      }
      copy_card = copy_card->prev_;
    }
  }
  return 1;
}
//------------------------------------------------------------------------------
///
/// Main game loop. Gets user input and renders gameboard until exit
///
/// @param stacks all the seven game stacks
///
//
void playLoop(CardStack **stacks)
{
  char *input = NULL;
  int running = 1;
  char **move_command = NULL;
  renderStacks(stacks);
  do
  {
    printf("esp> ");
    input = getInput();
    for(int ch = 0; ch < strlen(input); ch++)
      input[ch] = tolower(input[ch]);
    if(!strcmp(input, "help\n"))
    {
      printf("possible command:\n");
      printf(" - move <color> <value> to <stacknumber>\n");
      printf(" - help\n");
      printf(" - exit\n");
    }
    else if(!strcmp(input, "exit\n"))
    {
      running = 0;
    }
    else if((move_command = checkForMoveCommand(input)) != NULL)
    {
      if(move_command[1][0] < '1' || move_command[1][0] > '9')
        move_command[1][0] = toupper(move_command[1][0]);
      if(!move(stacks,atoi(move_command[2]),toupper(move_command[0][0]),copyString(move_command[1])))
       printf("[INFO] Invalid move command!\n");
      else
      {
        renderStacks(stacks);
        if(testForWin(stacks))
          break;
      }
      free(move_command);
    }
    else
    {
      printf("[INFO] Invalid command!\n");
    }
    free(input);
  } while(running);
}

int testForWin(CardStack **stacks)
{
  if(countCardStack(stacks[DEPOSIT_STACK_1]) == 13 && countCardStack(stacks[DEPOSIT_STACK_2]) == 13)
    return 1;
  return 0;
}

int countCardStack(CardStack *stack)
{
  Card *old_card = stack->top_card_;
  int count = 0;
  for(; old_card != NULL;)
  {
    count++;
    old_card = old_card->next_;
  }
  return count;
}

//------------------------------------------------------------------------------
///
/// Checks the user input for a valid move command
///
/// @param input input of the user
///
/// @return char ** with all the move parameters or null if failed
//
char **checkForMoveCommand(char *input)
{
  char *move, *col, *val, *to, *dest;
  char **move_command = mallocCheck(sizeof(char *) * 3);
  int return_null = 0;
  if(input != NULL)
    move = strtok(input, " ");
  else
    return_null = 1;
  if(move != NULL && !strcmp(move, "move"))
  {
    col = strtok(NULL, " ");
    if(col != NULL && (!strcmp(col,"red") || !strcmp(col,"black")))
    {
      move_command[0] = col;
      val = strtok(NULL, " ");
      if(checkForCardValue(val))
      {
        move_command[1] = val;
        to = strtok(NULL, " ");
        if(to != NULL && !strcmp(to, "to"))
        {
          dest = strtok(NULL, "\n");
          if(dest != NULL && strlen(dest) == 1 && dest[0] >= '0' && dest[0] <= '6')
          {
            move_command[2] = dest;
          }
          else 
            return_null = 1;
        }
        else 
          return_null = 1;
      }
      else 
        return_null = 1;
    }
    else 
      return_null = 1;
  }
  else 
    return_null = 1;
  if(return_null)
  {
    free(move_command);
    return NULL;
  }
  return move_command;
}

//------------------------------------------------------------------------------
///
/// Checks the input string for a valid card value
///
/// @param input string to be tested
///
/// @return 0 if no valid value or 1 if valid
//
int checkForCardValue(char *input)
{
  if(input == NULL)
    return 0;
  if(strlen(input) <= 2 && strlen(input) > 0)
  {
    if(!strcmp(input, "a") || !strcmp(input, "k") || !strcmp(input, "q") || !strcmp(input, "j"))
      return 1;
    else if(strlen(input) == 1 && isdigit(input[0]) && strcmp(input, "1"))
      return 1;
    else if(!strcmp(input, "10"))
      return 1;
  }
  return 0;
}

//------------------------------------------------------------------------------
///
/// Gets the input of the user for commands (help, exit, move)
///
/// @return string with user input
//
char *getInput()
{
  char *input = malloc(sizeof(char) * 20);
  int count = 0;
  int trimmed = 0;
  int realloced = 1;
  int ch = getchar();
  while(ch != '\n' && ch != EOF)
  {
    if(!isspace(ch) || trimmed)
    {
      trimmed = 1;
      if(!isspace(ch))
      {
        input[count] = ch;
        ch = getchar();
      }
      else
      {
        do{
          ch = getchar();
        } while(isspace(ch) && ch != '\n');
      	if(ch == '\n' || ch == EOF)
          break;
        else
        {
          input[count] = ' ';
        }
      }
      if(++count + 2 > sizeof(char) * 20 * realloced)
        input = realloc(input, sizeof(char) * 20 * ++realloced);
    }
    else 
      ch = getchar();
  }
  input[count] = '\n';
  input[count + 1] = '\0';
  return input;
}

//------------------------------------------------------------------------------
///
/// mallocs all seven game stacks and sets default values
///
/// @param stacks all seven game stacks
///
//
void initStacks(CardStack **stacks)
{
  for(int stack = 0; stack < 7; stack++)
  {
    stacks[stack] = mallocCheck(sizeof(CardStack));
    stacks[stack]->top_card_ = NULL;
    stacks[stack]->bottom_card_ = NULL;
  }
}

//------------------------------------------------------------------------------
///
/// frees all stacks given to it
///
/// @param stacks list of stacks
///
//
void freeStacks(CardStack **stacks)
{
  for(int stack = 0; stack < 7; stack++)
  {
    Card *next = NULL;
    for(Card *card = stacks[stack]->top_card_; card != NULL; card = next)
    {
      next = card->next_;
      free(card->value_);
      free(card);
    }
    free(stacks[stack]);
  }
  free(stacks);
}

//------------------------------------------------------------------------------
///
/// frees all stacks given to it
///
/// @param stacks list of stacks
///
//
void renderStacks(CardStack **stacks)
{
  printf("0   | 1   | 2   | 3   | 4   | DEP | DEP\n");
  printf("---------------------------------------\n");
  printRows(stacks);
}

//------------------------------------------------------------------------------
///
/// prints all rows of the gaming board
///
/// @param stacks all seven gaming stacks
///
//
void printRows(CardStack **stacks)
{
  Card *pick_off_card = stacks[PICK_OFF_STACK]->bottom_card_;
  Card **other_stacks_cards = malloc(sizeof(Card *) * 7);
  for(int row = 0; row < 16; row++)
  {
    printPickOffStack(pick_off_card);
    for(int stack = GAME_STACK_1; stack <= DEPOSIT_STACK_2; stack++)
    {
      if(row == 0)
        other_stacks_cards[stack] = stacks[stack]->bottom_card_;
      else
        other_stacks_cards[stack] = other_stacks_cards[stack] == NULL ? NULL : other_stacks_cards[stack]->prev_;
      printOtherStacks(other_stacks_cards[stack], stack);
    }
    printf("\n");
    pick_off_card = pick_off_card == NULL ? NULL : pick_off_card->prev_;
  }
  free(other_stacks_cards);
}

//------------------------------------------------------------------------------
///
/// prints cell the PickOffStack in a row
///
/// @param card card to be printed
///
//
void printPickOffStack(Card *card)
{
  if(card != NULL)
  {
    if(card->prev_ != NULL)
      printf("X   ");
    else
    {
      printCard(card);
      strlen(card->value_) > 1 ? printf(" ") : printf("  ");
    }
  }
  else
    printf("    ");
}

//------------------------------------------------------------------------------
///
/// prints cells of the other Stacks in a row
///
/// @param card card to be printed
/// @param stack indicates which stack (look at struct _StackTypes_)
///
//
void printOtherStacks(Card *card, int stack)
{
  printf("| ");
    if(card != NULL)
    {
      printCard(card);
      if(stack != DEPOSIT_STACK_2)
        strlen(card->value_) > 1 ? printf(" ") : printf("  ");
      else
        if(strlen(card->value_) == 1)
          printf(" ");
    }
    else
      stack == DEPOSIT_STACK_2 ? printf("   ") : printf("    ");
}

//------------------------------------------------------------------------------
///
/// mallocs the given size and checks if memory is full (null ptr given back)
///
/// @param size size to be malloced
///
//
void *mallocCheck(size_t size)
{
  void *buffer = malloc(size);
  if(buffer == NULL)
    exit(printErrorMessage(OUT_OF_MEMORY));
  return buffer;
}

//------------------------------------------------------------------------------
///
/// copies the values of one card to another
///
/// @param dest destination card
/// @param src source card
///
//
void copyCard(Card *dest, Card *src)
{
  dest->color_ = src->color_;
  dest->value_ = src->value_;
}

//------------------------------------------------------------------------------
///
/// add card to the beginning of a card stack
///
/// @param stack stack to be added to
/// @param color color of card
/// @param value value of card
///
//
void addTop(CardStack *stack, char color, char *value)
{
  // make new card and copy data to it:
  Card *new_card = mallocCheck(sizeof(Card));
  new_card->color_ = color;
  new_card->value_ = value;

  Card *old_top = stack->top_card_;
  new_card->next_ = old_top;    // next points to previous top card
  new_card->prev_ = NULL;
  if(old_top != NULL)
    old_top->prev_ = new_card;
  else
    stack->bottom_card_ = new_card;
  stack->top_card_ = new_card; // top now points to new card
}

//------------------------------------------------------------------------------
///
/// deletes top card of stack and gives it back
///
/// @param stack stack of which the top card should be deleted
///
/// @return card that was deleted
//
void delTop(CardStack *stack)
{
  Card *old_top = stack->top_card_;  // remember the old top card

  Card copy_old_top;
  copyCard(&copy_old_top, old_top);

  old_top->next_->prev_ = NULL;
  stack->top_card_ = old_top->next_;       // move top card down
  if(stack->top_card_->next_ == NULL)
  {
    stack->bottom_card_ = stack->top_card_;
  }
  free(old_top->value_);
  free(old_top);            // now we can free the old card
}
//------------------------------------------------------------------------------
///
/// includes all the game logic of the move command, it moves cards between stacks if its not against game rules
///
/// @param stacks list of stacks
/// @param dest_stack the stack that gets the cards
/// @param color the color of the card that needs to be moved
/// @param value the value of the card that needs to be moved
///
/// @return a ReturnValue which shows if the move Command was valid
//
int move(CardStack **stacks, int dest_stack, char color, char *value)
{
  //1. Find the stack which holds the card
  StackType src_stack = 0;
  Card *move_card = mallocCheck(sizeof(Card));
  move_card->color_ = color;
  move_card->value_ = value;

  int position = 0;
  if(!strcmp(stacks[PICK_OFF_STACK]->top_card_->value_, value) && (stacks[PICK_OFF_STACK]->top_card_->color_ == color))
  {
    src_stack = PICK_OFF_STACK;
  }
  else
  {
    for(int a = 1; a < 7; a++)
    {
      position = findCard(stacks[a], move_card);
      if(position != -1)
      {
        src_stack = a;
        break;
      }
    }
  }

  if(position == -1 || dest_stack == 0 || (src_stack == 5 || src_stack == 6))
  {
    printf("position = -1 or dest stack = 0 or srcstack = 5 srcstack = 6");
    free(move_card->value_);
    free(move_card);
    return 0;
  }
  if(stacks[dest_stack]->top_card_ != NULL)
  {
    if((dest_stack > 0 && dest_stack < 5) && ((stacks[dest_stack]->top_card_->color_ == color) || (getCardValueAsInt(stacks[dest_stack]->top_card_->value_)-1 != getCardValueAsInt(value)))) //muss noch wirklich einen value niedriger gemacht werden
    {
      printf("same color or wrong value: %c %d", color, getCardValueAsInt(value));
      free(move_card->value_);
      free(move_card);
      return 0;
    }
    else if((dest_stack == 5 || dest_stack == 6) && ((stacks[dest_stack]->top_card_->color_ != color)|| (getCardValueAsInt(stacks[dest_stack]->top_card_->value_)+1 != getCardValueAsInt(value))))
    {
      printf("not same color or wrong value: %c %d", color, getCardValueAsInt(value));
      free(move_card->value_);
      free(move_card);
      return 0;
    }
  }
  else
  {
    if((dest_stack > 0 && dest_stack < 5) && strcmp(value, "K"))
    {
      printf("empty game stack but card is not K");
      free(move_card->value_);
      free(move_card);
      return 0;
    }
    else if((dest_stack == 5 || dest_stack == 6) && strcmp(value, "A"))
    {
      printf("empty dep stack but card is not A");
      free(move_card->value_);
      free(move_card);
      return 0;
    }
  }


  //2. Copy the cards that will be moved
  //Find the position of the card in the specific stack
  Card *copy_top = stacks[src_stack]->top_card_;
  if(position != 0)
  {
    int counter = 0;
    while(counter < position)
    {
      copy_top = copy_top->next_;
      counter++;
    }
    //move_card->prev_->next_ = move_card;
  }
  move_card->next_ = NULL;
  move_card->prev_ = copy_top->prev_;

  if((src_stack > 0 && src_stack < 5) && (areCardsSorted(move_card,1) != 1))
  {
    //printf("game stack but not sorted");
    free(move_card->value_);
    free(move_card);
    return 0;
  }
  else if((src_stack == 5 || src_stack == 6) && (areCardsSorted(move_card,0) != 1))
  {
    //printf("dep stack but not sorted");
    free(move_card->value_);
    free(move_card);
    return 0;
  }
  //3. Delete the cards from src_stack from top_card and bottom_card
  if(position == 0)
  {
    delTop(stacks[src_stack]);
  }
  else if(compareCards(stacks[src_stack]->bottom_card_, copy_top))
  {
    //printf("bottom \n%d\n", position);
    stacks[src_stack]->bottom_card_ = NULL;
    stacks[src_stack]->top_card_ = NULL;
  }
  else
  {
    stacks[src_stack]->top_card_ = copy_top->next_;
    stacks[src_stack]->top_card_->prev_ = NULL;
    if(stacks[src_stack]->top_card_->next_ == NULL) // Überflüssig, da bottom_card automatisch gleich top card ist.. ändert sich ja nicht
    {
      stacks[src_stack]->bottom_card_ = stacks[src_stack]->top_card_;
    }
  }
  //4. Add the cards to dest_stack
  if(move_card->prev_ == NULL)
  {
    addTop(stacks[dest_stack],color,value);
  }
  else
  {
    Card* copy_move_card = move_card;
    while(copy_move_card != NULL)
    {
      addTop(stacks[dest_stack],copy_move_card->color_, copy_move_card->value_);
      copy_move_card = copy_move_card->prev_;
    }
  }
  
  free(move_card);
  return 1;
}

//------------------------------------------------------------------------------
///
/// Compares two cards
///
/// @param card1 first card
/// @param card2 secound card
///
/// @return 0 if not same 1 if same
//
int compareCards(Card *card1, Card *card2)
{
  if(card1 == NULL && card2 == NULL)
    return 1;
  if(card1 == NULL || card2 == NULL)
    return 0;
  if(toupper(card1->color_) == toupper(card2->color_))
  {
    if(card1->value_[0] > '0' && card1->value_[0] < '9')
      return card1->value_[0] == card2->value_[0] ? 1 : 0;
    else
      return toupper(card1->value_[0]) == toupper(card2->value_[0]) ? 1 : 0;
  }
  return 0;
}

//------------------------------------------------------------------------------
///
/// Takes card value and returns it as int indicating its value
///
/// @param value vlaue to be converted
///
/// @return value as integer
//
int getCardValueAsInt(char *value)
{
  if((strlen(value) == 1 && (*value > '2' && *value < '9')) || !strcmp(value, "10"))
  {
    return atoi(value);
  }
  else if(strlen(value) == 1)
  {
    switch(toupper(*value))
    {
      case 'A':
        return 1;
      case 'J':
        return 11;
      case 'Q':
        return 12;
      case 'K':
        return 13;
      default:
        return 0;
    }
  }
  return 0;
}

//------------------------------------------------------------------------------
///
/// finds a card in a given stack
///
/// @param stack stack to search in
/// @param spec_card card to be searched
///
/// @return searched card position or -1 if not found
//
int findCard(CardStack *stack, Card *spec_card)
{
    int counter = 0;
    Card *old_top = stack->top_card_;
    while(old_top != NULL)
    {
      if(compareCards(old_top, spec_card))
      {
        return counter;
      }
      old_top = old_top->next_; //move one card down
      counter++;
    }
  return -1;
}

//------------------------------------------------------------------------------
///
/// prints a given cards value and color (e.g. BLACK 10 -> B10)
///
/// @param card card to be printed
///
//
void printCard(Card *card)
{
  if(card->color_ != '\0' && card->value_ != NULL)
    printf("%c%s", card->color_, card->value_);
}

//------------------------------------------------------------------------------
///
/// reads the cards from given path
///
/// @param path string with path
/// @param stacks all seven card stacks
///
/// @return error type or 0 for success
//
ReturnValue readCardsFromPath(char *path, CardStack **stacks)
{
  FILE *file = fopen(path, "r");
  if(file == NULL)
  {
    return INVALID_FILE;
  }
  ReturnValue read_return_value = readCardsFromFile(file, stacks);

  fclose(file);
  return read_return_value;
}

//------------------------------------------------------------------------------
///
/// reads all the cards from a given file
///
/// @param file file with cards
/// @param stacks all seven card stacks
///
/// @return error type or 0 for success
//
ReturnValue readCardsFromFile(FILE *file, CardStack **stacks)
{
  char **cards = mallocCheck(27*8);
  char *line;
  int len, line_counter, ch;
  ReturnValue return_value = EVERYTHING_OK;
  for(line_counter = 0; (ch = getc(file)) != EOF; )
  {
    line = mallocCheck(8);
    line[0] = 0;
    for (len=0; ch != '\n' && ch != EOF; )
    {
      if(len > 7)
      {
        return_value = INVALID_FILE;
        free(line);
        break;
      }
      if(!isspace(ch) && !isblank(ch))
        line[len++] = ch;
      ch = getc(file);
    }
    if(strlen(line) != 0)
    {
      line[len] = '\0';
      cards[line_counter++] = line;
    }
    else
      free(line);
    if(return_value != EVERYTHING_OK)
      break;
  }
  return_value = return_value == EVERYTHING_OK ? checkCards(cards, line_counter) : return_value;
  return_value = return_value == EVERYTHING_OK ? addCardsToStacks(cards, stacks) : return_value;
  for(int li = 0; li < line_counter; li++)
      free(cards[li]);
  free(cards);
  return return_value;
}

//------------------------------------------------------------------------------
///
/// checks if all cards are correctly given (e.g. no doubles, too many / few, etc)
///
/// @param input all cards in strings
/// @param lines number of lines / cards
///
/// @return error type or 0 for success
//
ReturnValue checkCards(char **input, int lines)
{
  if(lines < 26 || lines > 26)
  {
    return INVALID_FILE;
  }
    
  char **cards = (char *[]){
    "REDA", "RED2", "RED3", "RED4", "RED5", "RED6", "RED7",
    "RED8", "RED9", "RED10", "REDJ", "REDQ", "REDK",
    "BLACKA", "BLACK2", "BLACK3", "BLACK4", "BLACK5", "BLACK6",
    "BLACK7", "BLACK8", "BLACK9", "BLACK10", "BLACKJ", "BLACKQ", "BLACKK"
  };
  char **included_cards = mallocCheck(lines*8);
  int included_counter = 0;
  int line, card;
  for(line = 0; line < lines; line++)
  {
    for(card = 0; card < lines; card++)
    {
      if(!strcmp(input[line], cards[card]))
      {
        for(int included = 0; included < included_counter; included++)
        {
          if(!strcmp(input[line], included_cards[included]))
          {
            free(included_cards);
            return INVALID_FILE;
          }
        }
        char *car = cards[card];
        included_cards[included_counter++] = input[line];
        continue;
      }
    }
  }
  free(included_cards);
  return included_counter == 26 ? EVERYTHING_OK : INVALID_FILE;
}

//------------------------------------------------------------------------------
///
/// adds all cards from file to the game stacks (following given rules)
///
/// @param cards all cards in given order
/// @param stacks all seven game stacks
///
/// @return error type or 0 for success
//
ReturnValue addCardsToStacks(char **cards, CardStack **stacks)
{
  int card = 25;
  for(int round = 0; round < 4; round++)
  {
    for(int stack = GAME_STACK_1 + round; stack <= GAME_STACK_4; stack++)
    {
      addTop(stacks[stack], cards[card][0], getCardValue(cards[card]));
      card--;
    }
  }
  for(int po_card = 0; po_card <= card; po_card++)
  {
    addTop(stacks[PICK_OFF_STACK], cards[po_card][0], getCardValue(cards[po_card]));
  }
  return EVERYTHING_OK;
}

//------------------------------------------------------------------------------
///
/// gets the value from a card given as string
///
/// @param card card from which to get the value
///
/// @return card value (string because of the possibility of "10")
//
char *getCardValue(char *card)
{
  switch(card[0])
  {
    case 'R':
      return copyString(&card[3]);
    case 'B':
      return copyString(&card[5]);
    default:
      return NULL;
  }
}

//------------------------------------------------------------------------------
///
/// Copys a string and gives it back (WARNING: RETURN STRING HAS TO BE FREED!!!)
///
/// @param string string to be copied
///
/// @return copied string (malloced)
//
char *copyString(char *string)
{
  char *copy = malloc(sizeof(string));
  strcpy(copy, string);
  return copy;
}

//------------------------------------------------------------------------------
///
/// Print message which describes the return value.
///
/// @param return_value type of main return value
///
/// @return parameter return_value
//
ReturnValue printErrorMessage(ReturnValue return_value)
{
  switch(return_value)
  {
    case INVALID_ARGUMENTS:
      printf("[ERR] Usage: ./ass3 [file-name]\n");
      break;
    case OUT_OF_MEMORY:
      printf("[ERR] Out of memory.\n");
      break;
    case INVALID_FILE:
      printf("[ERR] Invalid file!\n");
      break;
    case EVERYTHING_OK:
      //left blank intentionally
      break;
  }
  return return_value;
}