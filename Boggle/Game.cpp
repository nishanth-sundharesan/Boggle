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
bool8_t lettersVisited[NUM_ROWS][NUM_COLS] = { { false,false,false,false,false },{ false,false,false,false,false },{ false,false,false,false,false },{ false,false,false,false,false } };
#else
char8_t* boggleDices[NUM_DICE] = { DIE1 , DIE2 , DIE3 , DIE4 , DIE5 , DIE6 , DIE7, DIE8 , DIE9 , DIE10 , DIE11 , DIE12 , DIE13 , DIE14 , DIE15, DIE16 };
bool8_t lettersVisited[NUM_ROWS][NUM_COLS] = { {false,false,false,false},{ false,false,false,false },{ false,false,false,false },{ false,false,false,false } };
#endif

char8_t boggleBoard[NUM_ROWS][NUM_COLS];
char8_t* wordsFound[MAX_WORDS_FOUND];
char8_t lettersFound[MAX_CHARS_IN_DICTIONARY_WORD];
Trie* printedNodes[MAX_WORDS_FOUND];
int32_t letterIndex = 0;
int32_t wordIndex = 0;

void resetGame()
{
	freeAllFoundWords();
	resetWordsFound();
	clearLetters();
	clearWords();
}

/*	Function: resetWordsFound
*	-----------------------------------
*	Description: This function resets all the hasWordPrinted boolean for the nodes that have been printed. This is necessary because we need them to be printed for the next iteration of the game loop if they are found.
*/
void resetWordsFound()
{
	for (int32_t i = 0; i < wordIndex; i++)
	{
		printedNodes[i]->hasWordPrinted = false;
	}
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
	for (int32_t i = 0; i < NUM_ROWS; i++)
	{
		printf("\t");
		for (int32_t j = 0; j < NUM_COLS; j++)
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
	printf("\n\n=====Words Found=====");

	if (wordIndex == 0)
	{
		printf("\nNo Words Found");
	}
	else
	{
		for (int32_t i = 0; i < wordIndex; i++)
		{
			printf("\n%s", wordsFound[i]);
		}
	}
	printf("\n=====================");
#endif
}

/*	Function: searchForWords
*	-----------------------------------
*	Description: This function loops through the letters of the boggle board and searches for all the words starting with that letter. If any words are found, it will be added to the wordsFound[].
*	Parameters:
*				root = The root of the Trie data structure containing the dictionary of words
*/
void searchForWords(Trie* root)
{
	root = root->children;																//Traverse to the root's children
	Trie* mainRoot = root;																//and save that first child.
	for (int32_t i = 0; i < NUM_ROWS; i++)												//Loop through the boggle board
	{
		for (int32_t j = 0; j < NUM_COLS; j++)
		{
			if (boggleBoard[i][j] == root->character)									//If the letter in the board matches the node's letter
			{
				addLetterPrintWord(boggleBoard[i][j], &root);							//Save the letter in an array.
				lettersVisited[i][j] = true;											//Mark the position of the found letter as visited
				root = root->children;													//Note that I'm not checking if the found letter was the last letter of the word as this is the first letter and our dictionary only has words more than 4 letters.
			}
			else if (root->next != NULL)
			{
				while (root->next != NULL && root->character != boggleBoard[i][j])		//If the letter is not found in the children's node, then loop through the *next pointers or the siblings and search for the letter.
				{
					root = root->next;
				}
				if (root->character == boggleBoard[i][j])								//If the letter is found.
				{
					addLetterPrintWord(boggleBoard[i][j], &root);						//Save the letter in an array.
					lettersVisited[i][j] = true;										//Mark the position of the found letter as visited
					root = root->children;
				}
				else
				{
					root = NULL;
				}
			}

			if (root != NULL && mainRoot != root)
			{
				searchWordsForTheLetter(i, j, &root);									//After finding the first letter, search for the remaining letters.
			}
			clearLetters();
			root = mainRoot;															//Reset back the root node to the main root's child.
			clearAllVisitedNodes();
		}
	}
	root = mainRoot->parent;															//After searching all the words reset the root to the Trie data structure's root.
}

/*	Function: searchForWords
*	-----------------------------------
*	Description: This function takes in the position of the previously found letter and the child node of the previously found node and finds all the words
*				 from the dictionary whose letters occur after the previously found letter. Hence this function will be called recursively.
*	Parameters:
*				row = The row index of the previously found letter.
*				col = The column index of the previously found letter.
*				root = The child node of the previously found node.
*/
void searchWordsForTheLetter(int32_t row, int32_t col, Trie** root)
{
	for (int32_t i = row - 1; i <= row + 1; i++)												//Check for all the surrounding letters from the found letter
	{
		if (i >= 0 && i < NUM_ROWS)																//Check if it's a valid row index
		{
			for (int32_t j = col - 1; j <= col + 1; j++)										//Check for all the surrounding letters from the found letter
			{
				if (j >= 0 && j < NUM_COLS)														//Check if it's a valid column index
				{
					if (lettersVisited[i][j] == true)											//Check if the letter is already visited
					{
						continue;																//If yes, then skip the current loop.
					}

					if (boggleBoard[i][j] == (*root)->character)								//If the letter is found in the child node.
					{
						addLetterPrintWord(boggleBoard[i][j], root);
						if ((*root)->children == NULL)
						{
							removeLetter();														//Remove the added letter
							if ((*root)->next == NULL)
							{
								if ((*root)->isChildNode)										//If the node is a child node, then remove an additional letter and traverse back to the parent
								{
									(*root) = (*root)->parent;
									if (!(*root)->isChildNode)									//If the traversed parent node is not a child node and is a sibling node then traverse back one more time to find the parent node.
									{
										(*root) = (*root)->parent;
									}
									removeLetter();
									return;														//Return back from the recursive call as both the child node and the sibling nodes are not present.
								}
								else
								{
									(*root) = (*root)->parent;
								}
							}
						}
						else																	//If the child node exists
						{
							(*root) = (*root)->children;										//Traverse to the child node
							lettersVisited[i][j] = true;										//Mark the current position as visited
							searchWordsForTheLetter(i, j, (root));								//Make recursive calls and search for the subsequent letters
							lettersVisited[i][j] = false;										//After returning back from the recursive call, mark the current position as not visited
						}
					}
					else if ((*root)->next != NULL)												//If the letter is not found in the child node, then check if the letter is present in the siblings node.
					{
						while ((*root)->next != NULL && (*root)->character != boggleBoard[i][j])//Loop through the siblings until the letter is found
						{
							(*root) = (*root)->next;
						}

						if ((*root)->character == boggleBoard[i][j])							//If the letter is found
						{
							addLetterPrintWord(boggleBoard[i][j], root);						//Add the letter to the letterArray and check if the letter found is the last letter of the word
							if ((*root)->children == NULL)
							{
								removeLetter();
								(*root) = (*root)->parent;
							}
							else																//If the child node exists
							{
								(*root) = (*root)->children;									//Traverse to the child node
								lettersVisited[i][j] = true;									//Mark the current position as visited
								searchWordsForTheLetter(i, j, (root));							//Make recursive calls and search for the subsequent letters
								lettersVisited[i][j] = false;									//After returning back from the recursive call, mark the current position as not visited
							}
						}
						else
						{
							(*root) = (*root)->parent;											//If the letter is not found then reset back the node to it's parent's node.
						}
					}
				}
			}
		}
	}

	//Setting the proper parent node such that the parent node is not a sibling node
	if ((*root)->isChildNode)
	{
		(*root) = (*root)->parent;
		if (!(*root)->isChildNode)																//If the traversed parent node is a sibling node, then traverse to the parent node one more time.
		{
			(*root) = (*root)->parent;
		}
	}
	else
	{
		(*root) = (*root)->parent->parent;														//If the node is a sibling node, then traverse back 2 times.
	}
	removeLetter();
}

/*	Function: addLetterPrintWord
*	-----------------------------------
*	Description: This function adds the letter to the lettersFound[] and increments the index of the lettersFound[]. If the letter added is 'Q', then it adds an additional letter 'U' as 'Q' is treated is 'QU'.
*				 It then checks if the added letter was the last letter of the word, if yes then it checks if the word has already printed, if it's not printed, then it adds the word to the wordsFound[].
*	Parameters:
*				character = The found letter.
*				root = The node which contains the found letter. Both are separated for understanding purposes.
*/
void addLetterPrintWord(char8_t character, Trie** root)
{
	lettersFound[letterIndex++] = character;
	if (character == 'Q')
	{
		lettersFound[letterIndex++] = 'U';
	}

	if ((*root)->hasWordEnded && (!(*root)->hasWordPrinted))
	{
		(*root)->hasWordPrinted = true;
		lettersFound[letterIndex] = '\0';

		wordsFound[wordIndex] = (char8_t*)malloc(letterIndex + 1);
		strcpy_s(wordsFound[wordIndex], letterIndex + 1, lettersFound);
		printedNodes[wordIndex] = (*root);														//Save the pointer of the node in an array. This array will be looped through and the boolean hasWordPrinted will be re-setted for the next game loop.
		wordIndex++;

		assert(wordIndex != MAX_WORDS_FOUND);
	}
}

/*	Function: resetWordsFound
*	-----------------------------------
*	Description: This function decrements the index of the lettersFound[]. However, if the decremented letter is 'U' and the letter previous to it is 'Q' then decrement one more index.
*/
void removeLetter()
{
	letterIndex--;
	if (lettersFound[letterIndex] == 'U' && (letterIndex - 1) >= 0 && lettersFound[letterIndex - 1] == 'Q')
	{
		letterIndex--;
	}
}

void clearAllVisitedNodes()
{
	for (int32_t i = 0; i < NUM_ROWS; i++)
	{
		for (int32_t j = 0; j < NUM_COLS; j++)
		{
			lettersVisited[i][j] = false;
		}
	}
}

/*	Function: rangedRandom
*	-----------------------------------
*	Description: Generates a random number between min and max. Min is inclusive, Max is exclusive.
*	Parameters:
*				min = the minimum value of the random number(inclusive).
*				max = the maximum value of the random number(exclusive).
*/
int32_t rangedRandom(int32_t min, int32_t max)
{
	return (rand() % (max - min)) + min;
}

/*	Function: generateRandomCharacters
*	-----------------------------------
*	Description: For each position in the boggle board this function creates a random letter from the Dice of that position.
*	Parameters:
*				boggleDices = pointer to the boggle dices array.
*				boggleBoard = pointer to the boggle board array.
*/
void generateRandomCharacters(char8_t **boggleDices, char8_t *boggleBoard)
{
	int32_t randomNumber;
	for (int32_t i = 0; i < NUM_DICE; i++)
	{
		randomNumber = rangedRandom(0, SIDES_IN_DICE);
		assert(randomNumber >= 0 && randomNumber < SIDES_IN_DICE);

		boggleBoard[i] = boggleDices[i][randomNumber];
	}
}

/*	Function: shuffleCharacterArray
*	-----------------------------------
*	Description: This function shuffles all the characters present in the boggleBoard array. It goes through each element and replaces it with the random element in the array.
*	Parameters:
*				boggleBoard = pointer to the boggle board array.
*/
void shuffleCharacterArray(char8_t *boggleBoard)
{
	char8_t tempCharacter;
	int32_t randomNumber;

	for (int32_t i = 0; i < NUM_DICE; i++)
	{
		randomNumber = rangedRandom(0, NUM_DICE);
		assert(randomNumber >= 0 && randomNumber < NUM_DICE);

		tempCharacter = boggleBoard[i];
		boggleBoard[i] = boggleBoard[randomNumber];
		boggleBoard[randomNumber] = tempCharacter;
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

void finalizeGame(Trie** root)
{
	deleteTrieNodes(root);
	freeAllFoundWords();
}

void freeAllFoundWords()
{
	for (int32_t i = 0; i < wordIndex; i++)
	{
		free(wordsFound[i]);
	}
}