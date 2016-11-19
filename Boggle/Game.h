#ifdef GAME_CPP
#define extern 
#endif

struct WordList
{
	char8_t *word;
	struct WordList *nextWord;
};
typedef struct WordList wordListT;

extern wordListT *topOfWordList;

void initGame();
void buildRandomBoard();
int32_t rangedRandom(int32_t min, int32_t max);
void searchForWords(Trie* root);
void printBoard();
void printWords();
void resetGame();
void generateRandomCharacters(char8_t **charArray);
void shuffleCharacterArray();

void searchWordsForTheLetter(int row, int col, Trie** root);
bool isChildNode(Trie *root);
void addLetter(char8_t character);
void clearWords();
void removeLetter();
void printTheWord();

#undef extern