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

const int length = 4;
//char8_t tempBoggleBoard[length][length] = { {'A','B','C','D'},{ 'A','B','C','D' },{ 'E','F','G','H' },{ 'E','F','G','H' } };
//char8_t tempBoggleBoard[length][length] = { {'A','B','C','D'},{ 'E','F','G','H' },{ 'I','J','K','L' },{ 'M','N','O','P' } };
//char8_t tempBoggleBoard[length][length] = { { 'A','B','C','D' },{ 'E','F','G','H' },{ 'A','B','C','D' },{ 'E','F','G','H' } };
//char8_t tempBoggleBoard[length][length] = { { 'P','D','J','K' },{ 'A','B','C','D' },{ 'E','F','G','H' },{ 'S','T','M','A' } };
char8_t tempBoggleBoard[length][length] = { { 'P','D','J','K' },{ 'A','S','E','I' },{ 'U','R','N','L' },{ 'S','T','M','A' } };
//char8_t tempBoggleBoard[length][length] = { { 'P','D','J','K','C' },{ 'A','S','E','I','O' },{ 'U','R','N','L','F' },{ 'S','T','M','A','S' } };
bool8_t lettersVisited[length][length] = { {false,false,false,false},{ false,false,false,false },{ false,false,false,false },{ false,false,false,false } };
//bool8_t lettersVisited[length][length] = { { false,false,false,false,false },{ false,false,false,false,false },{ false,false,false,false,false },{ false,false,false,false,false } };



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
			lettersVisited[i][j] = true;
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

			searchWordsForTheLetter(i, j, &root);
			//break;
			clearWords();
			root = mainRoot;
			clearAllVsitedNodes();
		}
	}

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

					if (i == row && j == col)
					{
						continue;
					}

					if (tempBoggleBoard[i][j] == (*root)->character)
					{
						addLetter(tempBoggleBoard[i][j]);
						if ((*root)->hasWordEnded && (!(*root)->hasWordPrinted))
						{
							(*root)->hasWordPrinted = true;
							printTheWord();
						}

						if ((*root)->children == NULL)
						{
							//Can write better here
							if ((*root)->next == NULL)
							{
								removeLetter();
								if ((*root)->isChildNode)
								{
									(*root) = (*root)->parent;
									if (!(*root)->isChildNode)
									{
										(*root) = (*root)->parent;
									}
									removeLetter();

									//lettersVisited[i][j] = false;
									return;
								}
								else
								{
									(*root) = (*root)->parent;
									/*if (!(*root)->isChildNode)
									{
										(*root) = (*root)->parent;
									}*/
								}
								//Check if it is a linked node or child node, if child node, only then you can return
								//No need to check additional conditions while returning
								//return;
							}
							else
							{
								//(*root) = (*root)->next;
								//(*root) = temp;
								removeLetter();
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
					else
					{
						if ((*root)->next != NULL)
						{
							Trie* temp = (*root);

							while ((*root)->next != NULL && (*root)->character != tempBoggleBoard[i][j])
							{
								(*root) = (*root)->next;
							}

							if ((*root)->character == tempBoggleBoard[i][j])
							{
								addLetter(tempBoggleBoard[i][j]);
								if ((*root)->hasWordEnded && (!(*root)->hasWordPrinted))
								{
									(*root)->hasWordPrinted = true;
									printTheWord();
								}

								if ((*root)->children == NULL)
								{
									if ((*root)->next == NULL)
									{
										removeLetter();
										if ((*root)->isChildNode)
										{
											printf("Insideeeeeeeee-------------------------------");
											removeLetter();
											(*root) = (*root)->parent;
											if (!(*root)->isChildNode)
											{
												(*root) = (*root)->parent;
											}
											return;
										}
										else
										{
											(*root) = (*root)->parent;
											/*	if (!(*root)->isChildNode)
												{
													(*root) = (*root)->parent;
												}*/
										}
									}
									else
									{
										//(*root) = (*root)->next;
										(*root) = temp;
										removeLetter();
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
							else
							{
								(*root) = temp;
							}
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
		//while (!(*root)->isChildNode)		
		if (!(*root)->isChildNode)
		{
			(*root) = (*root)->parent;
		}

	}
	else
	{
		(*root) = (*root)->parent->parent;
		//while (!(*root)->isChildNode)
		/*if (!(*root)->isChildNode)
		{
			(*root) = (*root)->parent;
		}*/
	}
	removeLetter();
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

	//k--;
}

void clearAllVsitedNodes()
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
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


