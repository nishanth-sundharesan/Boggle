#define GAME_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <assert.h>
#include <stdlib.h> 

#include "types.h"
#include "Boggle.h"
#include "Dictionary.h"
#include "Dice.h"
#include "Game.h"
#include "Trie.h"

#if BIG_BOGGLE
char8_t* boggleDices[NUM_DICE] = { DIE1 , DIE2 , DIE3 , DIE4 , DIE5 , DIE6 , DIE7, DIE8 , DIE9 , DIE10 , DIE11 , DIE12 , DIE13 , DIE14 , DIE15, DIE16 , DIE17 , DIE18 , DIE19 , DIE20 , DIE21 , DIE22 , DIE23 , DIE24 , DIE25 };
#else
char8_t* boggleDices[NUM_DICE] = { DIE1 , DIE2 , DIE3 , DIE4 , DIE5 , DIE6 , DIE7, DIE8 , DIE9 , DIE10 , DIE11 , DIE12 , DIE13 , DIE14 , DIE15, DIE16 };
#endif

char8_t boggleBoard[NUM_ROWS][NUM_COLS];

const int length = 4;
//char8_t tempBoggleBoard[length][length] = { {'A','B','C','D'},{ 'A','B','C','D' },{ 'E','F','G','H' },{ 'E','F','G','H' } };
//char8_t tempBoggleBoard[length][length] = { {'A','B','C','D'},{ 'E','F','G','H' },{ 'I','J','K','L' },{ 'M','N','O','P' } };
//char8_t tempBoggleBoard[length][length] = { { 'A','B','C','D' },{ 'E','F','G','H' },{ 'A','B','C','D' },{ 'E','F','G','H' } };
//char8_t tempBoggleBoard[length][length] = { { 'P','D','J','K' },{ 'A','B','C','D' },{ 'E','F','G','H' },{ 'S','T','M','A' } };
char8_t tempBoggleBoard[length][length] = { { 'P','D','J','K' },{ 'A','S','E','I' },{ 'U','R','N','L' },{ 'S','T','M','A' } };
//char8_t tempBoggleBoard[length][length] = { { 'Q','A','S','D','F' },{ 'I','K','L','M','N' },{ 'H','L','O','P','R' },{ 'Z','X','C','V','U' },{ 'H','E','R','E','I' } };
bool8_t lettersVisited[length][length] = { {false,false,false,false},{ false,false,false,false },{ false,false,false,false },{ false,false,false,false } };
//bool8_t lettersVisited[length][length] = { { false,false,false,false,false },{ false,false,false,false,false },{ false,false,false,false,false },{ false,false,false,false,false } };


char8_t* wordsFound[MAX_WORDS_FOUND];
char8_t lettersFound[MAX_CHARS_IN_DICTIONARY_WORD];
Trie* printedNodes[MAX_WORDS_FOUND];
uint16_t letterIndex = 0;
uint16_t wordIndex = 0;

void resetGame()
{
	//Work on this
	//clearLetters();

	for (int i = 0; i < wordIndex; i++)
	{
		printedNodes[i]->hasWordPrinted = false;
	}
	clearWords();
}

void initGame()
{

}

void buildRandomBoard()
{
	generateRandomCharacters(boggleDices, &boggleBoard[0][0]);
	shuffleCharacterArray(&boggleBoard[0][0]);
}

void printBoard()
{
#if DEBUG_PRINTING_ON
	printf("======Boggle Board======\n\n");
	for (int i = 0; i < NUM_ROWS; i++)
	{
		printf("\t");
		for (int j = 0; j < NUM_COLS; j++)
		{
			printf("%c ", boggleBoard[i][j]);
		}
		printf("\n");
	}
	printf("\n========================\n");
#endif
}

void printWords()
{
#if DEBUG_PRINTING_ON	
	printf("\n\n\n=====Words Found=====");

	if (wordIndex == 0)
	{
		printf("\nNo Words Found");
	}
	else
	{
		for (int i = 0; i < wordIndex; i++)
		{
			printf("\n%s", wordsFound[i]);
		}
	}
	printf("\n=====================");
#endif
}

void searchForWords(Trie* root)
{
	//Just taking some time here to make sure the timer is working properly
	float m = 0.0f;
	for (int n = 0; n < 100000; ++n)
		m += ((float)rand()) / 100000.0f;

	printf("m=%f", m);

	root = root->children;
	Trie* mainRoot = root;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			/*int i = 1;
			int j = 2;*/
			if (tempBoggleBoard[i][j] == root->character)
			{
				addLetterPrintWord(tempBoggleBoard[i][j], &root);
				lettersVisited[i][j] = true;
				root = root->children;
			}
			else if (root->next != NULL)
			{
				while (root->next != NULL && root->character != tempBoggleBoard[i][j])
				{
					root = root->next;
				}
				if (root->character == tempBoggleBoard[i][j])
				{
					addLetterPrintWord(tempBoggleBoard[i][j], &root);
					lettersVisited[i][j] = true;
					root = root->children;
				}
				else
				{
					root = NULL;
				}
			}

			if (root != NULL && mainRoot != root)
			{
				searchWordsForTheLetter(i, j, &root);
			}
			clearLetters();
			root = mainRoot;
			clearAllVisitedNodes();
		}
	}
	root = mainRoot->parent;
}

void searchWordsForTheLetter(int row, int col, Trie** root)
{
	for (int i = row - 1; i <= row + 1; i++)
	{
		if (i >= 0 && i < length)
		{
			for (int j = col - 1; j <= col + 1; j++)
			{
				if (j >= 0 && j < length)
				{
					if (lettersVisited[i][j] == true)
					{
						continue;
					}

					if (tempBoggleBoard[i][j] == (*root)->character)
					{
						addLetterPrintWord(tempBoggleBoard[i][j], root);
						if ((*root)->children == NULL)
						{
							removeLetter();
							if ((*root)->next == NULL)
							{
								if ((*root)->isChildNode)
								{
									(*root) = (*root)->parent;
									if (!(*root)->isChildNode)
									{
										(*root) = (*root)->parent;
									}
									removeLetter();
									return;
								}
								else
								{
									(*root) = (*root)->parent;
								}
							}
						}
						else
						{
							(*root) = (*root)->children;
							lettersVisited[i][j] = true;
							searchWordsForTheLetter(i, j, (root));
							lettersVisited[i][j] = false;
						}
					}
					else if ((*root)->next != NULL)
					{
						while ((*root)->next != NULL && (*root)->character != tempBoggleBoard[i][j])
						{
							(*root) = (*root)->next;
						}

						if ((*root)->character == tempBoggleBoard[i][j])
						{
							addLetterPrintWord(tempBoggleBoard[i][j], root);
							if ((*root)->children == NULL)
							{
								removeLetter();
								(*root) = (*root)->parent;
							}
							else
							{
								(*root) = (*root)->children;
								lettersVisited[i][j] = true;
								searchWordsForTheLetter(i, j, (root));
								lettersVisited[i][j] = false;
							}
						}
						else
						{
							(*root) = (*root)->parent;
						}
					}
				}
			}
		}
	}

	//Setting proper parent node
	if ((*root)->isChildNode)
	{
		(*root) = (*root)->parent;
		if (!(*root)->isChildNode)
		{
			(*root) = (*root)->parent;
		}
	}
	else
	{
		(*root) = (*root)->parent->parent;
	}
	removeLetter();
}

void addLetterPrintWord(char8_t character, Trie** root)
{
	lettersFound[letterIndex++] = character;

	if ((*root)->hasWordEnded && (!(*root)->hasWordPrinted))
	{
		(*root)->hasWordPrinted = true;
		lettersFound[letterIndex] = '\0';

		wordsFound[wordIndex] = (char8_t*)malloc(letterIndex + 1);
		strcpy_s(wordsFound[wordIndex], letterIndex + 1, lettersFound);
		printedNodes[wordIndex] = (*root);
		wordIndex++;

		assert(wordIndex != MAX_WORDS_FOUND);
	}
}

void clearLetters()
{
	letterIndex = 0;
}

void clearWords()
{
	wordIndex = 0;
}

void removeLetter()
{
	letterIndex--;
}

void clearAllVisitedNodes()
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			lettersVisited[i][j] = false;
		}
	}
}

int32_t rangedRandom(int32_t min, int32_t max)
{
	return (rand() % (max - min)) + min;

	//min is inclusive
	//max is exclusive
}

void generateRandomCharacters(char8_t **boggleBoard, char8_t *displayedBoggleBoard)
{
	int randomNumber;
	for (int i = 0; i < NUM_DICE; i++)
	{
		randomNumber = rangedRandom(0, SIDES_IN_DICE);
		assert(randomNumber >= 0 && randomNumber < SIDES_IN_DICE);

		displayedBoggleBoard[i] = boggleBoard[i][randomNumber];
	}
}

void shuffleCharacterArray(char8_t *displayedBoggleBoard)
{
	char8_t tempCharacter;
	int randomNumber;

	for (int i = 0; i < NUM_DICE; i++)
	{
		randomNumber = rangedRandom(0, NUM_DICE);
		assert(randomNumber >= 0 && randomNumber < NUM_DICE);

		tempCharacter = displayedBoggleBoard[i];
		displayedBoggleBoard[i] = displayedBoggleBoard[randomNumber];
		displayedBoggleBoard[randomNumber] = tempCharacter;
	}
}


