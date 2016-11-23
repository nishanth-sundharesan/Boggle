#define DICTIONARY_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "Dictionary.h"
#include "Boggle.h"
#include "Game.h"
#include "Trie.h"

bool8_t parseDictionaryFile(char8_t *fileName, int32_t *numberOfWords, Trie** root)
{
	//Declaring the file pointer
	FILE *dictionaryDataToRead = NULL;

	errno_t errorNumber = fopen_s(&dictionaryDataToRead, fileName, "r");
	assert(errorNumber == 0);
	if (errorNumber != 0)
	{
		printf("Unable to open the file %s", fileName);
		return true;
	}

	char8_t readLine[MAX_CHARS_IN_DICTIONARY_WORD];
	createTrieRootNode(root);

	while (fgets(readLine, MAX_CHARS_IN_DICTIONARY_WORD, dictionaryDataToRead) != NULL)
	{
		if (checkIfValidWord(readLine))
		{
			addTrieNodes(readLine, *root);
		}
	}	

	fclose(dictionaryDataToRead);
	return false;
}

bool8_t checkIfValidWord(char8_t word[])
{
	bool8_t isValidWord = true;
	uint16_t letterCount = 0;

	while (true)
	{
		if (word[letterCount] == '\n' || word[letterCount] == '\0')
		{
			break;
		}
		else if (!(word[letterCount] >= START_CHAR && word[letterCount] <= END_CHAR))
		{
			isValidWord = false;
			break;
		}
		else if ((word[letterCount] == 'Q') && (word[letterCount + 1] != 'U'))
		{
			isValidWord = false;
			break;
		}
		letterCount++;
	}

	if (isValidWord && letterCount >= MAX_CHARS_IN_A_WORD)
	{
		return true;
	}
	else
	{
		return false;
	}
}

