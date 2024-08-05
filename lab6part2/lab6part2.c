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

char* readWord(int* wordSize) {
  printf("How many characters are there in the word?");
  scanf("%d", wordSize);  // no need for &. wordsize is a pointer pointing to an address
  char* word = (char*)malloc((size_t)(*wordSize+1) *sizeof(char));  // wordarray is the dynamically allocated array
  printf("What is the word that you are looking for?\n");
    scanf(" %s", word);
      return word;
  }

void readWordPuzzle(const int Size, char puzzle[][Size]) {
  printf("Please enter the word puzzle:\n");
  for (int x = 0; x < Size; x++) {    // to loop thru each row
    for (int y = 0; y < Size; y++) {  // to loop thru each col
      scanf(" %c",&puzzle[x][y]);  // space before %c so it ignores white spaces
    }
  }
}

void printWordPuzzle(const int Size, char puzzle[][Size]) {
  printf("The word puzzle entered is\n");
  for (int x = 0; x < Size; x++) {    // Again loops over rows
    for (int y = 0; y < Size; y++) {  // and loops over columns
      printf("%c ", puzzle[x][y]);    // space is added after c to add space
                                      // betweeen each character in puzzle
    }  // also prints out the character at each position
    printf("\n");
  }
}

void printWord(char* word, const int wordSize) {
   printf("The word you are looking for is:\n%s\n", word);
}

/////////////////////////////////////////////////////

int changeInRowIndex[8]={-1, -1, -1, 1, 1, 1, 0, 0};
int changeInColIndex[8]={0, 1,-1, 0., 1, -1, 1, -1};
const char*directionNames[] = {"north", "north-east", "north-west", "south", "south-east", "south-west", "east", "west"};

bool inBounds(int row, int col, const int Size){
  return (row>=0 && row<Size && col>=0 && col<Size);
}

bool check1D(const int Size, char puzzle[][Size], const int wordSize, char*
word, int rowLoc, int colLoc, int dir){
  // the row and column indices will change for each of the 8 directions
  
  /* 
  north: move up = decrease row by 1, col stays the same.
  north-east: move up + to the right= decrease row by 1, increase col by 1 
  north-west: move up + to the left = decrease row by 1, decrease col by 1 
  south: move down = increase row, col stays the same.
  south-east: down + to the right = increase row by 1, increase col by 1
  south-west: down+ to the left = increase row by 1, decrease col by 1 
  East: move to the right = row is the same, increase col by 1 
  West: move to the left = row is the same, decrease col by 1
    */

   int row = rowLoc;
   int col = colLoc;
   
   // iterate thru each character in the word and apply the direction changes 
   for (int x=0; x<wordSize; x++){
    row = row + x*changeInRowIndex[dir];
    col = col + x*changeInColIndex[dir];
    
    if (puzzle[row][col]!=word[x] || (!inBounds(row, col, Size))){
    return false;
    }
   }
   return true;
}

void search(const int Size, char puzzle[][Size], const int wordSize,char* word){
// iterate through each row and col
for (int row=0; row<Size; row++){
  for (int col=0; col<Size; col++){
    // must have a loop that iterates over each of the 8 directions for each element in my array 
    // this loop will go in each direction to see if word starts there 
    // dir 0= north, dir1=north-east, dir2=north-west, dir 3=south, dir4=south-east, dir5=south-west, dir6=east, dir7=west
    for (int dir=0; dir<8; dir++){
      if (check1D(Size, puzzle, wordSize, word, row, col, dir)){
        printf("%s can be found at row, col = (%d,%d) in the %s direction.\n", word, row+1, col+1, directionNames[dir]);
        return;
      }
    }
  }
}
printf("%s cannot be found!\n", word);
}
