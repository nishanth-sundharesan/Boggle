#define BOGGLE_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <string.h>

#include "types.h"
#include "Boggle.h"
#include "Dictionary.h"
#include "Dice.h"
#include "Game.h"
#include "Trie.h"

int32_t main(int32_t argc, char8_t *argv[])
{	
	char8_t *fileName = FILENAME_DICTIONARY;
	time_t t;
	char8_t inChar = 0x00;
	LARGE_INTEGER ticksPerSecond;
	LARGE_INTEGER startTime, endTime, elapsedTime;
#if !INPUT_NEEDED_TO_CONTINUE
	float_t timeToAverage[NUM_GAMES_TO_AVERAGE];
#endif
	//Get the high resolution counter's accuracy
	QueryPerformanceFrequency(&ticksPerSecond);

	srand((unsigned int)time(&t));
	
	Trie* root;	
	bool8_t done = parseDictionaryFile(fileName, &root);
	int32_t gameCounter = 0;

	while (!done)
	{
		initGame();
		buildRandomBoard();
#if DEBUG_PRINTING_ON
		printBoard();
#endif
		QueryPerformanceCounter(&startTime);
		searchForWords(root);
		QueryPerformanceCounter(&endTime);
		elapsedTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
		float_t timeInMilliseconds = 1000.0f* ((float_t)elapsedTime.QuadPart / (float_t)ticksPerSecond.QuadPart);

#if DEBUG_PRINTING_ON
		printf("\nSearch took %f milliseconds.\n", timeInMilliseconds);
		printWords();
#endif

#if INPUT_NEEDED_TO_CONTINUE
		printf("\nPress q to quit, any other key to continue:");
		scanf_s("%c", &inChar);
		fflush(stdin);
		if (inChar == 'q')
			done = true;
		if (!done)
			resetGame();
#else 
		timeToAverage[gameCounter++] = (float_t)timeInMilliseconds;
		if (gameCounter < NUM_GAMES_TO_AVERAGE )
		{			
			resetGame();
		}
		else
		{
			float_t average = 0.0f;
			for (int32_t i = 0; i < NUM_GAMES_TO_AVERAGE; ++i)
			{
				average += timeToAverage[i];
			}
			average /= (float_t)NUM_GAMES_TO_AVERAGE;

#if AVERAGE_PRINTING_ON
			printf("\nThe average of the %d games was %2.4f milliseconds\n", NUM_GAMES_TO_AVERAGE, average);
#endif
			done = true;
		}
#endif
	}	
	finalizeGame(&root);
	getchar();
}