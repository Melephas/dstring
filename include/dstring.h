#pragma once


#include <stdint.h>


/* Represents a dynamically allocated and managed string
 */
typedef struct dstring_s string;


// Create a new empty string
string* string_new();

// Create a new string from a C string
string* string_from(char* c_string);

// Destroy a string when it's no longer needed
void string_destroy(string* str);

// Append a character to the end of the string
void string_append_char(string* str, char c);

// Append an entire C string to the end of the string
void string_append_cstring(string* str, char* cstring);

// Append a managed string to the end of the string
void string_append_string(string* str, string* str1);

// Creates an exact copy of the string
string* string_duplicate(string* str);

// Creates a C string from the string
char* string_to_cstring(string* str);

// Create a new string from a section of the given string
string* string_substring(string* str, uint64_t start, uint64_t length);

// Get a character from a specified place in a string
char string_character_at(string* str, uint64_t index);
