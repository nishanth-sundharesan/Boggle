#define DICTIONARY_CPP

/*
* This program contains functions that,
* 1. Opens the dictionary file and reads all the words present in that file.
* 2. Checks if the word is valid.
* 3. Creates Trie data structure for all the letters of the valid word.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "Dictionary.h"
#include "Boggle.h"
#include "Game.h"
#include "Trie.h"

/*	Function: parseDictionaryFile
*	-----------------------------------
*	Description: This function takes the file name of the dictionary and the root node.
*				 It then creates the root node, reads all the words from the dictionary and creates the Trie data structure for all the letters from the read words.
*	Parameters:
*				fileName = The file name of the dictionary file.
*	Returns:	Returns false if the file is opened and successfully read, otherwise true. This returned boolean will be used as a condition for game loop, hence it is inversed.
*/
bool8_t parseDictionaryFile(char8_t *fileName, Trie** root)
{
	//Declaring the file pointer.
	FILE *dictionaryDataToRead = NULL;

	//Open the dictionary file in read mode.
	errno_t errorNumber = fopen_s(&dictionaryDataToRead, fileName, "r");
	assert(errorNumber == 0);
	if (errorNumber != 0)
	{
		printf("Unable to open the file %s", fileName);										//If there was any error while opening the file then print an error message and exit the game.
		return true;
	}

	char8_t readLine[MAX_CHARS_IN_DICTIONARY_WORD];
	createTrieRootNode(root);																//Create the root node for the Trie data structure.
	while (fgets(readLine, MAX_CHARS_IN_DICTIONARY_WORD, dictionaryDataToRead) != NULL)		//Read each line(which is a single word) from the dictionary file.
	{
		if (checkIfValidWord(readLine))														//Check if the read word is a valid word.
		{
			addTrieNodes(readLine, *root);													//If it is a valid word, then add the letters from that word to the Trie data structure.
		}
	}	

	//Close the opened file.
	fclose(dictionaryDataToRead);
	return false;
}

/*	Function: checkIfValidWord
*	-----------------------------------
*	Description: This function takes an entire word as a parameter and check if it's a valid word.
*				 Rules for a valid word.
*					a) The letters in the word must be between 'A' and 'Z'.
*					b) If there is a word with the letter 'Q' and the letter followed by it is not 'U', then it's an invalid word
*					c) The letters in the word must be more than the MAX_CHARS_IN_A_WORD. It's 4 in our program.
*	Parameters:
*				word = The word to be checked for validity.
*	Returns:	Returns true if the word is valid or false if invalid.
*/
bool8_t checkIfValidWord(char8_t word[])
{
	bool8_t isValidWord = true;
	int32_t letterCount = 0;

	while (true)
	{
		if (word[letterCount] == '\n' || word[letterCount] == '\0')							//If the word has ended, then exit the loop
		{
			break;
		}
		else if (!(word[letterCount] >= START_CHAR && word[letterCount] <= END_CHAR))		//Checking if the letter is between START_CHAR and END_CHAR
		{
			isValidWord = false;															//If it is not, then it is an invalid word
			break;
		}
		else if ((word[letterCount] == 'Q') && (word[letterCount + 1] != 'U'))				//If the letter found is 'Q' and the letter found after it is not 'U', then it's an invalid word
		{
			isValidWord = false;
			break;
		}
		letterCount++;
	}

	if (isValidWord && letterCount >= MAX_CHARS_IN_A_WORD)									//If the letters in the word is less than MAX_CHARS_IN_A_WORD, then it's an invalid word.
	{
		return true;
	}
	else
	{
		return false;
	}
}

