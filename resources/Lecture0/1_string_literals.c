#include <stdio.h>

// Function that returns a pointer to the first byte of the string
char *getFirstByteOfString(char *str) {
    return str;
}

int main() {
    char myString[] = "Hello, world!"; // Example string

    // Call the function and store the returned pointer
    char *firstByte = getFirstByteOfString(myString);

    // Print the pointer value and the character it points to
    printf("Pointer to the first byte: %p\n", (void *)firstByte); //  explicitly cast the pointer to void * when using %p to avoid any potential issues with pointer mismatching.

    printf("Character at that pointer: %c\n", *firstByte);

    return 0;
}

