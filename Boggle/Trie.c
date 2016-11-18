#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "Trie.h"

void AddTrieNode(char8_t *word, Trie* mainRoot)
{
	Trie* root = mainRoot;

	//printf("%s\n", word);
	//while (*word != '\n' && *word != '\0')
	while (true)
	{
		if (*word == '\n' || *word == '\0')
		{
			root->hasWordEnded = true;
			break;
		}

		assert(*word != '\n');
		assert(*word != '\0');

		if (*word >= 'A' && *word <= 'Z')
		{
			if (root->children == NULL)
			{
				Trie* node = (Trie *)malloc(sizeof(Trie));
				node->character = *word;
				node->children = NULL;
				node->next = NULL;
				node->hasWordEnded = false;

				root->children = node;

				root = node;
			}
			else
			{
				root = root->children;

				if (root->character == *word)
				{
					//root = root->children;
				}
				else
				{
					while (root->next != NULL)
					{
						root = root->next;
					}

					if (root->character != *word)
					{
						Trie* node = (Trie *)malloc(sizeof(Trie));
						node->character = *word;
						node->children = NULL;
						node->next = NULL;
						node->hasWordEnded = false;

						root->next = node;
						root = node;
					}
				}
			}
		}
		word++;
		//printf("%c", *(word++));
	}
}

void CreateTrieRootNode(Trie** root)
{
	*root = (Trie *)malloc(sizeof(Trie));
	(*root)->character = '\0';
	(*root)->next = NULL;
	(*root)->children = NULL;
}

void PrintTrie(Trie* mainRoot)
{
	mainRoot = mainRoot->children;
	printf("%c\n", mainRoot->character);

	mainRoot = mainRoot->next;
	while (mainRoot != NULL)
	{
		printf("%c\n", mainRoot->character);
		mainRoot = mainRoot->next;
	}
}