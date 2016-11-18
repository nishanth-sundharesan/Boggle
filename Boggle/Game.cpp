#define GAME_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

#include "types.h"
#include "Boggle.h"
#include "Dictionary.h"
#include "Dice.h"
#include "Game.h"

#if BIG_BOGGLE
char8_t* boggleBoard[NUM_DICE] = { DIE1 , DIE2 , DIE3 , DIE4 , DIE5 , DIE6 , DIE7, DIE8 , DIE9 , DIE10 , DIE11 , DIE12 , DIE13 , DIE14 , DIE15, DIE16 , DIE17 , DIE18 , DIE19 , DIE20 , DIE21 , DIE22 , DIE23 , DIE24 , DIE25 };
#else
char8_t boggleBoard[NUM_DICE][SIDES_IN_DICE + 1] = { DIE1 , DIE2 , DIE3 , DIE4 , DIE5 , DIE6 , DIE7, DIE8 , DIE9 , DIE10 , DIE11 , DIE12 , DIE13 , DIE14 , DIE15, DIE16 };
#endif

char8_t displayedBoggleBoard[NUM_DICE];

void resetGame()
{

}
void initGame()
{

}
void buildRandomBoard()
{	
	generateRandomCharacters(boggleBoard);
	shuffleCharacterArray();
}

void printBoard()
{
#if DEBUG_PRINTING_ON
	/*for (int i = 0; i < NUM_DICE; i++)
	{
		printf("%c\n", displayedBoggleBoard[i]);
	}*/
#endif
}

void printWords()
{
#if DEBUG_PRINTING_ON

#endif
}


void searchForWords()
{
	//Just taking some time here to make sure the timer is working properly
	float j = 0.0f;
	for (int i = 0; i < 100000; ++i)
		j += ((float)rand()) / 100000.0f;

	printf("j=%f", j);
}

int32_t rangedRandom(int32_t min, int32_t max)
{
	return (rand() % (max - min)) + min;

	//min is inclusive
	//max is exclusive
}

void generateRandomCharacters(char8_t **boggleBoard)
{		
	int randomNumber;
	for (int i = 0; i < NUM_DICE; i++)
	{
		randomNumber = rangedRandom(0, SIDES_IN_DICE);
		assert(randomNumber != SIDES_IN_DICE);

		displayedBoggleBoard[i] = boggleBoard[i][randomNumber];
	}
}

void shuffleCharacterArray()
{
	char8_t tempCharacter;	
	int randomNumber;

	for (int i = 0; i < NUM_DICE; i++)
	{
		randomNumber = rangedRandom(0, NUM_DICE);
		assert(randomNumber != NUM_DICE);

		tempCharacter = displayedBoggleBoard[i];
		displayedBoggleBoard[i] = displayedBoggleBoard[randomNumber];
		displayedBoggleBoard[randomNumber] = tempCharacter;
	}
}


