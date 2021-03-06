#ifdef GAME_CPP
#define extern 
#endif

void initGame();
void buildRandomBoard();
int32_t rangedRandom(int32_t min, int32_t max);
void searchForWords(Trie* root);
void printBoard();
void printWords();
void resetGame();
void resetWordsFound();
void finalizeGame(Trie** root);
void generateRandomCharacters(char8_t **charArray, char8_t *displayedBoggleBoard);
void shuffleCharacterArray(char8_t *displayedBoggleBoard);
void searchWordsForTheLetter(int32_t row, int32_t col, Trie** root);
void clearAllVisitedNodes();
void clearLetters();
void removeLetter();
void clearWords();
void freeAllFoundWords();
void addLetterPrintWord(char8_t character, Trie** root);

#undef extern