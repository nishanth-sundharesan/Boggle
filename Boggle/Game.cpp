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
#include "Trie.h"

#if BIG_BOGGLE
char8_t* boggleBoard[NUM_DICE] = { DIE1 , DIE2 , DIE3 , DIE4 , DIE5 , DIE6 , DIE7, DIE8 , DIE9 , DIE10 , DIE11 , DIE12 , DIE13 , DIE14 , DIE15, DIE16 , DIE17 , DIE18 , DIE19 , DIE20 , DIE21 , DIE22 , DIE23 , DIE24 , DIE25 };
#else
char8_t boggleBoard[NUM_DICE][SIDES_IN_DICE + 1] = { DIE1 , DIE2 , DIE3 , DIE4 , DIE5 , DIE6 , DIE7, DIE8 , DIE9 , DIE10 , DIE11 , DIE12 , DIE13 , DIE14 , DIE15, DIE16 };
#endif

char8_t displayedBoggleBoard[NUM_DICE];

char8_t tempBoggleBoard[4][4] = { {'A','B','C','D'},{'E','F','G','H'},{ 'I','J','K','L' },{ 'E','F','G','H' } };
int length = 4;


char8_t wordsFound[MAX_CHARS_IN_DICTIONARY_WORD];
int k = 0;

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

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			printf("%c ", tempBoggleBoard[i][j]);
		}
		printf("\n");
	}
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


void searchForWords(Trie* root)
{
	//Just taking some time here to make sure the timer is working properly
	/*float j = 0.0f;
	for (int i = 0; i < 100000; ++i)
		j += ((float)rand()) / 100000.0f;

	printf("j=%f", j);
*/

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			root = root->children;



			if (tempBoggleBoard[i][j] == root->character)
			{
				addLetter(tempBoggleBoard[i][j]);
				if (root->hasWordEnded)
				{
					printTheWord();
				}

				root = root->children;				
			}
			else
			{
				if (root->next != NULL)
				{
					while (root->next != NULL && root->character != tempBoggleBoard[i][j])
					{
						root = root->next;
					}

					if (root->character == tempBoggleBoard[i][j])
					{
						addLetter(tempBoggleBoard[i][j]);
						if (root->hasWordEnded)
						{
							printTheWord();
						}
						root = root->children;
					}
				}
			}

			searchWordsForTheLetter(i, j, root);
			//searchWordsForTheLetter(i, j, root);
			break;
			clearWords();
		}
	}

}

void searchWordsForTheLetter(int row, int col, Trie* root)
{


	for (int i = row - 1; i <= row + 1; i++)
	{
		if (i >= 0 && i < length)
		{
			for (int j = col - 1; j <= col + 1; j++)
			{
				if (j >= 0 && j < length)
				{

					if (i == row && j == col)
					{
						continue;
					}

					if (tempBoggleBoard[i][j] == root->character)
					{
						addLetter(tempBoggleBoard[i][j]);
						if (root->hasWordEnded)
						{
							printTheWord();
						}

						if (root->children == NULL)
						{
							//Can write better here
							if (root->next == NULL)
							{
								root = root->parent;
								removeLetter();
								if (isChildNode(root))
								{
									return;
								}
								//Check if it is a linked node or child node, if child node, only then you can return
								//No need to check additional conditions while returning
								//return;
							}
							else
							{
								root = root->next;
								removeLetter();
								//return;
							}
						}
						else
						{
							root = root->children;
							searchWordsForTheLetter(i, j, root);
						}
					}
					else
					{
						if (root->next != NULL)
						{
							Trie* temp = root;

							while (root->next != NULL && root->character != tempBoggleBoard[i][j])
							{
								root = root->next;
							}

							if (root->character == tempBoggleBoard[i][j])
							{
								addLetter(tempBoggleBoard[i][j]);
								if (root->hasWordEnded)
								{
									printTheWord();
								}

								if (root->children == NULL)
								{
									if (root->next == NULL)
									{
										root = root->parent;
										removeLetter();
										//return;
									}
									else
									{
										root = root->next;
										removeLetter();
										//return;
									}
								}
								else
								{
									root = root->children;
									searchWordsForTheLetter(i, j, root);
								}
							}
							else
							{
								root = temp;
							}
						}
					}
				}
			}
		}
	}

	//Setting proper parent node

	if (isChildNode(root))
	{
		root = root->parent;
	}
	else
	{
		root = root->parent->parent;
	}
	/*if (root->parent->children != NULL)
	{
		if (root->parent->children->character == root->character)
		{
			root = root->parent;
		}
		else
		{
			root = root->parent->parent;
		}
	}
	else
	{
		root = root->parent->parent;
	}*/

	removeLetter();
}

bool isChildNode(Trie *root)
{
	if (root->parent->children != NULL && root->parent->children->character == root->character)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void addLetter(char8_t character)
{
	wordsFound[k++] = character;
}

void clearWords()
{
	k = 0;
}

void removeLetter()
{
	k--;
}

void printTheWord()
{
	wordsFound[k] = '\0';
	printf("%s\n", wordsFound);

	k = 0;
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


