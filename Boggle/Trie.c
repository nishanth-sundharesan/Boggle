#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "Trie.h"

/*	Function: createEmptyNode
*	-----------------------------------
*	Description: This function takes in a 'word'(array of characters) and the 'root' node. It creates a node for each letter in the word and
*				 adds it to the Trie data structure.
*	Parameters:
*				word = The letters of the word will be added.
*				root = The root of the Trie data structure.
*/
void addTrieNodes(char8_t *word, Trie* root)
{
	while (true)
	{
		if (*word == '\n' || *word == '\0')									//If the word has ended
		{
			root->hasWordEnded = true;										//Then change the 'hasWordEnded' boolean of the node to true. This node contains the last letter of the word.
			break;															//Exit from the loop.
		}

		if (root->children == NULL)											//If the children is NULL
		{
			Trie* node = createTrieNode(*word);							    //Then create a new Trie node with the character in it.

			node->isChildNode = true;										//Make isChildNode as true. This will always be true inside this condition as we haven't traversed from the *next or through the sibling nodes.
			node->parent = root;											//Assign it's parent node.

			root->children = node;
			root = node;													//Make the newly created node as the root node. Subsequent characters or letters will be added from this node.
		}
		else
		{
			root = root->children;											//If the children is not NULL, then go to the children's node
			Trie* parentNode = root;

			if (root->character != *word)									//Check if character or the letter is already present. If yes then skip the condition and continue with the next letter
			{
				while (root->next != NULL && root->character != *word)		//If not, then traverse through it's *next pointers or siblings until the node is the last node or the character is found
				{
					root = root->next;
				}

				if (root->character != *word)								//If the character or letter is already present, then skip the condition and continue with the next letter
				{
					Trie* node = createTrieNode(*word);						//If not, then create a new Trie node with with the character in it.

					node->isChildNode = false;								//Make isChildNode as false as the node is traversed from the *next.
					node->parent = parentNode;								//Assign it's parent node.

					root->next = node;
					root = node;											//Make the newly created node as the root node. Subsequent characters or letters will be added from this node.
				}
			}
		}
		if (*word == 'Q')													//If we find the letter 'Q' then increment the word pointer as we already know that the letter followed by 'Q' is always 'U'.
		{																	//We won't be adding the letter 'U' which is followed by 'Q' in our data structure as the letter 'Q' is considered as 'QU' while reading from the board.
			word++;
		}
		word++;																//Increment the word pointer to the next letter or character
	}
}

/*	Function: deleteTrieNodes
*	-----------------------------------
*	Description: This function takes in the root node. It traverses through the complete list of child nodes and frees all the nodes. It then finally frees the root node.
*	Parameters:
*				root = The root of the Trie data structure.
*/
void deleteTrieNodes(Trie** root)
{
	Trie* previousNode;
	while ((*root) != NULL)
	{
		while ((*root)->children != NULL)														//Traverse through the nodes until it is the last child node.
		{
			(*root) = (*root)->children;
		}

		while ((*root)->next != NULL)															//Traverse through the last child node using *next(siblings) until it is the last node.
		{
			previousNode = (*root);
			(*root) = (*root)->next;
		}

		if ((*root)->children == NULL && (*root)->next == NULL)									//If the node doesn't contain any children or it's next node, then it's time to free that node.
		{
			if ((*root)->isChildNode)															//If the last node is a child node.
			{
				(*root) = (*root)->parent;														//Assign the root node to it's parent's node
				if ((*root) != NULL)															//This condition fails if it's the ultimate root node
				{
					free((*root)->children);													//And free the last node
					(*root)->children = NULL;
				}
				else
				{
					free((*root));																//This condition succeeds for the ultimate root node
					break;
				}
			}
			else
			{
				(*root) = previousNode;															//If the last node is not a child node then free the last node and assign the root node to it's previously traversed node.
				free((*root)->next);
				(*root)->next = NULL;
			}

			if (!((*root)->isChildNode) && (*root)->children == NULL && (*root)->next == NULL)	//If the newly assigned node is not a child node and it is the last node, then assign the newly assigned node to it's parent's node.
			{																					//If we do not do this, then in the next loop, previousNode and the newly assigned node will both point to the same node.
				(*root) = (*root)->parent;
			}
		}
	}
}
	
/*	Function: createTrieNode
*	-----------------------------------
*	Description: Creates a Trie node and assigns some default values to the members of the node.
*	Parameters:
*				letter = The character to be assigned after creating the node.
*	Returns:	Returns the pointer to the dynamically created Trie node.
*/
Trie* createTrieNode(char8_t letter)
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

/*	Function: createTrieRootNode
*	-----------------------------------
*	Description: Creates the root node for the Trie data structure. It will have it's data as NULL or \0.
*	Parameters:
*				root = The root node to be created.
*/
void createTrieRootNode(Trie** root)
{
	*root = createTrieNode('\0');
	(*root)->isChildNode = true;
	(*root)->parent = NULL;
}