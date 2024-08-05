#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void readWordPuzzle(const int Size, char puzzle[][Size]);
char* readWord(int* wordSize);
void printWordPuzzle(const int Size, char puzzle[][Size]);
void printWord(char* word, const int wordSize);

void search(const int Size, char puzzle[][Size], const int wordSize,char* word);
bool inBounds(int row, int col, const int Size);

int main(void) {
  const int Size = 20;
  char puzzle[Size][Size];
  readWordPuzzle(Size, puzzle);
  int wordSize = 0;
  char* word = readWord(&wordSize);
  printWordPuzzle(Size, puzzle);
  printf("The word you are looking for is\n");
  printWord(word, wordSize);
  printf("\n");
  printf("Do you want to search? (Y or N)\n");
  char isSearch;
  scanf(" %c", &isSearch);
  if (isSearch == 'Y' || isSearch == 'y') {
    search(Size, puzzle, wordSize, word);
  }
  free(word);
  return 0;
}

////// FUNCTION 1 ////////////////////////////////////////////////
void readWordPuzzle(const int Size, char puzzle[][Size]) {
  printf("Please enter the word puzzle:\n");
  for (int x = 0; x < Size; x++) {    // to loop thru each row
    for (int y = 0; y < Size; y++) {  // to loop thru each col
      scanf(" %c",
            &puzzle[x][y]);  // space before %c so it ignores white spaces
    }
  }
}

  /////// FUNCTION 2 ////////////////////////////////
  char* readWord(int* wordSize) {
    printf("How many characters are there in the word?");
    scanf("%d", wordSize);  // no need for &. wordsize is a pointer pointing to an address
    char* word = (char*)malloc((*wordSize) *sizeof(char));  // wordarray is the dynamically allocated array
    printf("What is the word that you are looking for?");
    for (int x = 0; x < *wordSize; x++) {
      scanf(" %c", &word[x]);
    }
    return word;
  }

  /////////// FUNCTION 3 /////////////////////////////////////////////
  void printWordPuzzle(const int Size, char puzzle[][Size]) {
    printf("The word puzzle entered is\n");
    for (int x = 0; x < Size; x++) {    // Again loops over rows
      for (int y = 0; y < Size; y++) {  // and loops over columns
        printf("%c ", puzzle[x][y]);    // space is added after c to add space betweeen each character in puzzle
      }  // also prints out the character at each position
      printf("/n");
    }
  }

  /////////// FUNCTION 4 //////////////////////////////////////////////
  void printWord(char* word, const int wordSize) {
    printf("The word you are looking for is\n");
    for (int x = 0; x < wordSize; x++){
        printf("%c ", word[x]);  // accesses each character in the word
      }
    printf("\n");
  }

///////////////////////////////////////////////////////////////////