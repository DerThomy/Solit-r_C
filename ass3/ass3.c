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
typedef struct Card_
{
  char color;
  int value;
  struct Card_ *next;
}Card;
//Stores Cards in a Stack and which type of stack it is (e.g. GameStack)
typedef struct CardStack_
{
  struct Card_ Cards;
  char *stack_type;
}CardStack;

//Return values of the program
typedef enum _ReturnValue_
{
  EVERYTHING_OK = 0,
  INVALID_ARGUMENTS = 1,
  OUT_OF_MEMORY = 2,
  INVALID_FILE = 3
} ReturnValue;

enum CardValue
{
   A = 1,
   J = 11,
   Q = 12,
   K = 13
};


ReturnValue printErrorMessage(ReturnValue return_value);
ReturnValue readCardsFromPath(char *path);
ReturnValue readCardsFromFile(FILE* file);

int main(int argc, char **argv)
{
  printf("%d\n",argc);

  if(argc != 2)
  {
    return printErrorMessage(INVALID_ARGUMENTS);
  }

  //char **cards = malloc(26*3);

  return 0;
}

ReturnValue readCardsFromPath(char *path)
{
  FILE* file = fopen(path, "r");
  if(file == NULL)
  {
    return INVALID_FILE;
  }
  ReturnValue read_return_value = readCardsFromFile(file);

  fclose(file);
  return read_return_value;
}

ReturnValue readCardsFromFile(FILE* file)
{
//  for(int variable_iterator = 0; variable_iterator < 4; variable_iterator++)
//  {
//    ReturnValue
//            return_value = readSingleValue(file, variables[variable_iterator]);
//    if(return_value != EVERYTHING_OK)
//    {
//      return return_value;
//    }
//  }
  return EVERYTHING_OK;
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