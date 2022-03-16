#include "../include/dstring.h"


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
            fprintf(
                    stderr,
                    "Failed to reallocate dstring (%s)\n",
                    strerror(errno)
            );
            exit(1);
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


// returns a sub string from a string
string* string_substring(string* str,uint64_t start,uint64_t length)
{
	/*there is no checking to make sure the length or offset entered is valid.I assumed, it would be checked before call?.
	 * I randomly wrote this anyway,you can get rid of it if it doesn't fit with your design.*/
	if(length>str->used_length || start>str->used_length)
	{
		printf("invalid inputs for string_substring function.");
		exit(EXIT_FAILURE);
	}

	/*allocate new string and create some static memory of length bytes*/
	string *sub_string = string_new();
	char buffer[length];

	/*copy the range of bytes into local buffer with terminating '\0'*/
	memcpy(buffer,&str->characters[start],length);
	buffer[length]='\0';

	/*append extracted buffer to sub_string*/
	string_append_cstring(sub_string,buffer);

	/*return structure*/
	return sub_string;
}

/*returns character at given string offset*/
char string_character_at(string* str,uint64_t index)
{
	/*Making sure to stay within boundries and not cause seg fault,seg fault would have the desired affect and thus
	 * exit the program and make these lines below redundant, however dynamic memory can be very weird, that i thought
	 * it was a good idea to include, remove if you like or change*/
	if(index>str->used_length)
	{
		printf("Out of bounds!\n");
		exit(EXIT_FAILURE);
	}

	/*return the byte at requested offset*/
	return(str->characters[index]);	
}
