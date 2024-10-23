//Code by Lance S.

#include <stdio.h>
#include <ctype.h> 

// Letter Count defines a struct to store the count for each letter
struct LetterCount {
    char letter;
    int count;
};

// countLetters counts the letters in the file
void countLetters(struct LetterCount counts[], int size) {
    char ch;
    
    //this while loops to read characters until end of the file
    while (!feof(stdin)) {
        scanf("%c", &ch);  // Reads one character at a time
        
        // Checks if the character is a letter
        if (isalpha(ch)) {
            ch = tolower(ch);  // Convert to lowercase for consistency
            
            // Increments the count for the corresponding letter
            counts[ch - 'a'].count++;
        }
    }
}

int main() {
    // Create an array of LetterCount structs, one for each letter
    struct LetterCount counts[26];
    
    // Initialize the counts array
    for (int i = 0; i < 26; i++) {
        counts[i].letter = 'a' + i;  
        counts[i].count = 0;        
    }
    
    // Calls the function to count the letters in the file
    countLetters(counts, 26);
    
    // Outputs the results
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", counts[i].letter, counts[i].count);
    }
    
    return 0;
}


    

