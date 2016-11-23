#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "Trie.h"

void addTrieNodes(char8_t *word, Trie* root)
{
	while (true)
	{
		if (*word == '\n' || *word == '\0')
		{
			root->hasWordEnded = true;
			break;
		}

		if (root->children == NULL)
		{
			Trie* node = createEmptyNode(*word);

			node->isChildNode = true;
			node->parent = root;

			root->children = node;
			root = node;
		}
		else
		{
			root = root->children;
			Trie* parentNode = root;

			if (root->character != *word)
			{
				while (root->next != NULL && root->character != *word)
				{
					root = root->next;
				}

				if (root->character != *word)
				{
					Trie* node = createEmptyNode(*word);

					node->isChildNode = false;
					node->parent = parentNode;

					root->next = node;
					root = node;
				}
			}
		}
		if (*word == 'Q')
		{
			word++;
		}
		word++;
	}
}

void deleteTrieNodes(Trie** root)
{
	Trie* previousNode;
	while ((*root) != NULL)
	{
		while ((*root)->children != NULL)
		{
			(*root) = (*root)->children;
		}

		while ((*root)->next != NULL)
		{
			previousNode = (*root);
			(*root) = (*root)->next;
		}

		if ((*root)->children == NULL && (*root)->next == NULL)
		{
			if ((*root)->isChildNode)
			{
				(*root) = (*root)->parent;
				if ((*root) != NULL)
				{
					free((*root)->children);
					(*root)->children = NULL;
				}
				else
				{
					free((*root));
					break;
				}
			}
			else
			{
				(*root) = previousNode;
				free((*root)->next);
				(*root)->next = NULL;
			}

			if (!((*root)->isChildNode) && (*root)->children == NULL && (*root)->next == NULL)
			{
				(*root) = (*root)->parent;
			}
		}
	}
}
	
/*	Function: createEmptyNode
*	-----------------------------------
*	Description: Creates a Trie node and assigns some default values to the members of the node.
*	Parameters:
*				letter = The character to be assigned after creating the node.
*	Returns:	Returns the pointer to the dynamically created Trie node.
*/
Trie* createEmptyNode(char8_t letter)
{
	Trie* node = (Trie *)malloc(sizeof(Trie));
	assert(node != NULL);

	node->character = letter;
	node->children = NULL;
	node->next = NULL;
	node->hasWordEnded = false;
	node->hasWordPrinted = false;
	return node;
}

void createTrieRootNode(Trie** root)
{
	*root = createEmptyNode('\0');
	(*root)->isChildNode = true;
	(*root)->parent = NULL;
}