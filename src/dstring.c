#include "dstring/dstring.h"


#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>


#ifndef STRING_CHUNK_SIZE
    #define STRING_CHUNK_SIZE 10
#endif


struct dstring_s {
    char* characters;
    uint64_t allocated_length;
    uint64_t used_length;
};


// Create a new empty string
string* string_new() {
    string* ret = calloc(1, sizeof(string));
    ret->allocated_length = STRING_CHUNK_SIZE;
    ret->used_length = 0;
    ret->characters = calloc(STRING_CHUNK_SIZE, sizeof(char));

    return ret;
}

// Create a new string from a C string
string* string_from(char* c_string) {
    string* ret = string_new();
    string_append_cstring(ret, c_string);
    return ret;
}

// Destroy a string when it's no longer needed
void string_destroy(string* string) {
    free(string->characters);
    free(string);
}

// Append a character to the end of the string
void string_append_char(string* str, char c) {
    str->characters[str->used_length] = c;
    if (++(str->used_length) >= str->allocated_length) {
        str->allocated_length += STRING_CHUNK_SIZE;
        char* tmp = realloc(str->characters, str->allocated_length * sizeof(char));
        if (tmp == NULL) {
            fprintf(stderr, "Failed to reallocate dstring (%s)\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        str->characters = tmp;
    }
}

// Append an entire C string to the end of the string
void string_append_cstring(string* string, char* cstring) {
    uint64_t str_len = strlen(cstring);
    for (uint64_t i = 0; i < str_len; i++) {
        string_append_char(string, cstring[i]);
    }
}

// Append a managed string to the end of the string
void string_append_string(string* str, string* str1) {
    string_append_cstring(str, string_to_cstring(str1));
}

// Creates an exact copy of the string
string* string_duplicate(string* str) {
    string* ret = malloc(sizeof(string));
    ret->used_length = str->used_length;
    ret->allocated_length = str->allocated_length;
    ret->characters = malloc(ret->allocated_length);
    memcpy(ret->characters, str->characters, ret->allocated_length);
    return ret;
}

// Creates a C string from the string
char* string_to_cstring(string* str) {
    char* ret = calloc(str->used_length + 1, sizeof(char));
    memcpy(ret, str->characters, str->used_length);
    return ret;
}


// Create a new string from a section of the given string
string* string_substring(string* str, uint64_t start, uint64_t length) {
    if (start > str->used_length || start + length > str->used_length) {
        fprintf(stderr, "Invalid substring specification\n");
	exit(EXIT_FAILURE);
    }

    string *sub_string = string_new();
    char buffer[length];

    memcpy(buffer, &str->characters[start], length);
    buffer[length] = '\0';

    string_append_cstring(sub_string, buffer);

    return sub_string;
}

// Get a character from a specified place in a string
char string_character_at(string* str, uint64_t index) {
    if (index > str->used_length) {
        fprintf(stderr, "Invalid string index\n");
	exit(EXIT_FAILURE);
    }

    return str->characters[index];
}

