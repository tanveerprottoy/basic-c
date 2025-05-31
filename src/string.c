#include <stdint.h>

typedef struct {
    char* chars;
    int32_t length;
} String;

void print_chars(String str) {
    for (int i = 0; i < str.length; i++) {
        printf("%c", str.chars[i]);
    }
}
