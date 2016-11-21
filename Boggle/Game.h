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
void generateRandomCharacters(char8_t **charArray, char8_t *displayedBoggleBoard);
void shuffleCharacterArray(char8_t *displayedBoggleBoard);

void searchWordsForTheLetter(int row, int col, Trie** root);
void clearAllVisitedNodes();
void clearLetters();
void removeLetter();
void clearWords();
void addLetterPrintWord(char8_t character, Trie** root);

#undef extern