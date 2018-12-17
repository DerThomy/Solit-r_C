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
#include <errno.h>

//Return values of the program
typedef enum _ReturnValue_
{
  EVERYTHING_OK = 0,
  INVALID_ARGUMENTS = 1,
  OUT_OF_MEMORY = 2,
  INVALID_FILE = 3
} ReturnValue;

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
typedef struct Card_
{
  char color;
  int value;
  struct Card_ *next;
}Card;

//Stores a card stack and which type of stack it is (e.g. GameStack)
typedef struct CardStack_
{
  struct Card_ *Cards; //the stack of cards
  char *stack_type;
}CardStack;

enum CardValue
{
   A = 1,
   J = 11,
   Q = 12,
   K = 13
};

void *malloc_check(size_t size);
void copyCard(Card *dest, Card *src);
void freeCard(Card *s);
void addTop(Card **top, char color, int value);
Card delTop(Card **top);
Card *FindCard(Card **top, Card *spec_card);
void printCard(Card card);
ReturnValue readCardsFromPath(char *path, CardStack **card_stack);
ReturnValue readCardsFromFile(FILE *file, CardStack **card_stack);
ReturnValue checkCards(char **input, int lines);
ReturnValue addCardsToStacks(CardStack **card_stack);
ReturnValue printErrorMessage(ReturnValue return_value);

int main(int argc, char **argv)
{
  if(argc != 2)
  {
    return printErrorMessage(INVALID_ARGUMENTS);
  }

  CardStack **stacks = malloc_check(sizeof(CardStack *) * 7);
  for(int stack = 0; stack < 7; stack++)
    stacks[stack] = malloc(sizeof(CardStack));

  ReturnValue return_value = readCardsFromPath(argv[1], stacks);

  for(int stack = 0; stack < 7; stack++)
  {
    free(stacks[stack]);
  }
  free(stacks);
  return printErrorMessage(return_value);;
}

void *malloc_check(size_t size)
{
  void *buffer = malloc(size);
  if(buffer == NULL)
    exit(printErrorMessage(OUT_OF_MEMORY));
  return buffer;
}

void copyCard(Card *dest, Card *src)
{
  dest->color = src->color;
  dest->value = src->value;
}

void freeCard(Card *s)
{
  //So nicht möglich, da wir mit stacks arbeiten
  //free(s->next);
}

//Adds new card to the top
void addTop(Card **top, char color, int value)
{
  // make new card and copy data to it:
  Card *new_card = malloc_check(sizeof(Card));
  new_card->color = color;
  new_card->value = value;

  new_card->next = *top;    // next points to previous top card
  *top = new_card;          // top now points to new card
}

//Deletes top card
Card delTop(Card **top)
{
  Card *old_top = *top;  // remember the old top card

  Card copy_old_top;
  copyCard(&copy_old_top, old_top);

  *top = old_top->next;       // move top card down
  free(old_top);              // now we can free the old card
  return copy_old_top;                // and return the card we remembered
}

//Searches for a specific card
Card *FindCard(Card **top, Card *spec_card)
{
   Card *old_top = *top;
   while(old_top->next != NULL)
   {
     if(old_top->color == spec_card->color && old_top->value == spec_card->value )
     {
       //if a matching card is found, the whole stack starting with the specific card will be returned
       copyCard(spec_card, old_top);
       return spec_card;
     }
     old_top = old_top->next; //move one card down
   }

  return NULL;
}

void printCard(Card card)
{
  printf("%c%d", card.color, card.value);
}

ReturnValue readCardsFromPath(char *path, CardStack **card_stack)
{
  FILE *file = fopen(path, "r");
  if(file == NULL)
  {
    return INVALID_FILE;
  }
  ReturnValue read_return_value = readCardsFromFile(file, card_stack);

  fclose(file);
  return read_return_value;
}

ReturnValue readCardsFromFile(FILE *file, CardStack **card_stack)
{
  char **cards = malloc_check(27*8);
  char *line;
  int len, line_counter, ch;
  ReturnValue return_value = EVERYTHING_OK;
  for(line_counter = 0; (ch = getc(file)) != EOF; )
  {
    ch = toupper(ch);
    line = malloc_check(8);
    line[0] = 0;
    for (len=0; ch != '\n' && ch != EOF; )
    {
      if(len > 7)
      {
        printf("too long");
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
      //printf("%s %d\n", line, (unsigned int)strlen(line));
      cards[line_counter++] = line;
    }
    else
      free(line);
    if(return_value != EVERYTHING_OK)
      break;
  }
  return_value = return_value == EVERYTHING_OK ? checkCards(cards, line_counter) : return_value;
  return_value = return_value == EVERYTHING_OK ? addCardsToStacks(cards, card_stack) : return_value;
  for(int li = 0; li < line_counter; li++)
      free(cards[li]);
  free(cards);
  return return_value;
}

ReturnValue checkCards(char **input, int lines)
{
  if(lines < 26 || lines > 26)
  {
    printf("too short or big");
    return INVALID_FILE;
  }
    
  char **cards = (char *[]){
    "REDA", "RED2", "RED3", "RED4", "RED5", "RED6", "RED7",
    "RED8", "RED9", "RED10", "REDJ", "REDQ", "REDK",
    "BLACKA", "BLACK2", "BLACK3", "BLACK4", "BLACK5", "BLACK6",
    "BLACK7", "BLACK8", "BLACK9", "BLACK10", "BLACKJ", "BLACKQ", "BLACKK"
  };
  char **included_cards = malloc_check(lines*8);
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
            printf("not unique %s\n", input[line]);
            free(included_cards);
            return INVALID_FILE;
          }
        }
        included_cards[included_counter++] = input[line];
        continue;
      }
    }
  }
  free(included_cards);
  return included_counter == 26 ? EVERYTHING_OK : INVALID_FILE;
}

ReturnValue addCardsToStacks(char **cards, CardStack **card_stack)
{
  for(int card = 0; card < 26; card++)
  {
    
  }
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