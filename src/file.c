#include "stdio.h"

// open_text_file opens a text file for writing
// and returns a FILE pointer.
// the caller must close the file after using it
// by calling fclose(*FILE)
FILE* open_text_file(char path[]) {
    FILE* file_ptr;

    // open the file in write mode
    // write mode opens the file for writing, creating it if
    // it doesn't exist
    // this mode will overwrite the file if it already exists
    file_ptr = fopen(path, "w");
    if (file_ptr == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    return file_ptr;
}

// read_text_file reads the content of a text file
// and returns a FILE pointer.
// the caller must close the file after using it
// by calling fclose(*FILE)
void* read_text_file(char path[]) {
    FILE* file_ptr;

    // open the file in read mode
    file_ptr = fopen(path, "r");
    if (file_ptr == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    // fread(NULL, 0, 0, file_ptr);

    // read the content of the file
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file_ptr) != NULL) {
        // print the content of the file
        printf("%s", buffer);
    }

    // close the file
    fclose(file_ptr);
}

// write_text_file writes "Hello, World!" to a file named "example.txt"
// and closes the file after writing
void write_text_file(char path[]) {
    FILE* file_ptr;

    // write mode opens the file for writing, creating it if
    // it doesn't exist
    // this mode will overwrite the file if it already exists
    file_ptr = fopen(path, "w");
    if (file_ptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Data to be inserted
    char str[] = "This is the content written to the file.\n";

    // write to the file
    fputs(str, file_ptr);
    // Alternatively, you can use fprintf to write formatted output
    // fprintf(file_ptr, "%s", str);
    // or simply write a string directly
    // fprintf(file_ptr, "Hello, World!\n");

    // close the file
    fclose(file_ptr);
}

void read_binary_file(char path[]) {
    FILE* file_ptr;

    // open the file in binary read mode
    file_ptr = fopen(path, "rb");
    if (file_ptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // read the content of the file
    // buffer of size 256 bytes
    char buffer[256];
    size_t bytes_read;

    // read the content of the file in binary format
    while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), file_ptr)) > 0) {
        // print the content of the file
        fwrite(buffer, sizeof(char), bytes_read, stdout);
        printf("%s\n", buffer);
    }

    // close the file
    fclose(file_ptr);
}

void write_binary_file(char path[]) {
    FILE* file_ptr;

    // open the file in binary write mode
    // this mode will create the file if it doesn't exist
    // and overwrite it if it does
    file_ptr = fopen(path, "wb");
    if (file_ptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Data to be inserted
    char data[] = "This is the content written to the file\n";

    // write the data to the file in binary format
    fwrite(&data, sizeof(char[41]), 1, file_ptr);

    // close the file
    fclose(file_ptr);
}
