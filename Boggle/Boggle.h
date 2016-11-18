#define MAX_CHARS_IN_DICTIONARY_WORD 32
#define MAX_LINE MAX_CHARS_IN_DICTIONARY_WORD
#define BIG_BOGGLE 1
#define SIDES_IN_DICE 6

#if BIG_BOGGLE
#define NUM_ROWS 5
#define NUM_COLS 5
#else
#define NUM_ROWS 4
#define NUM_COLS 4
#endif
#define NUM_DICE (NUM_ROWS * NUM_COLS)
#define MAX_WORDS_FOUND 200

#define FILENAME_DICTIONARY "../AppData/Dictionary.txt"
#define INPUT_NEEDED_TO_CONTINUE 1
#define NUM_GAMES_TO_AVERAGE 1000
#define DEBUG_PRINTING_ON 1
#define AVERAGE_PRINTING_ON 1
//Number of columns for your words
#define PRINT_COLUMNS 8


