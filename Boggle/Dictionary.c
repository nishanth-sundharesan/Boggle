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

void parseDictionaryFile(char8_t *fileName, int32_t *numberOfWords,Trie** root)
{
	FILE *dictionaryDataToRead = NULL;

	errno_t errorNumber = fopen_s(&dictionaryDataToRead, fileName, "r");
	assert(errorNumber == 0);

	char8_t readLine[MAX_CHARS_IN_DICTIONARY_WORD];
	//Trie* root;
	CreateTrieRootNode(root);

	while (fgets(readLine, 100, dictionaryDataToRead) != NULL)
	{				
		if (strlen(readLine) > 4)
		{
			AddTrieNode(readLine, *root);	
		}
	}
	//PrintTrie(*root);


	fclose(dictionaryDataToRead);
}

