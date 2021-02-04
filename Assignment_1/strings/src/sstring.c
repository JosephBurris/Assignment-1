#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/sstring.h"

bool string_valid(const char *str, const size_t length)
{
	if(str == NULL || length <= 0) {
		return false;
	}

	int count;
	for(count = 0; count < length; count++) {
		if(*(str) == '\0') {
			return true;
		}
		else {
			str++;
		}
	}
	return false;
}

char *string_duplicate(const char *str, const size_t length)
{
	if(str == NULL || length <= 0) {
		return NULL;
	}
	
	char *newString = malloc(sizeof(char) * length);
	strcpy(newString, str);
	return newString;
}

bool string_equal(const char *str_a, const char *str_b, const size_t length)
{
	if(str_a == NULL) {
		return false;
	}
	if(str_b == NULL) {
		return false;
	}
	if(length <= 0) {
		return false;
	}

	if(strcmp(str_a, str_b) == 0) {
		return true;
	}
	else {
		return false;
	}
}

int string_length(const char *str, const size_t length)
{
	if(str == NULL) {
		return -1;
	}
	else if(length <= 0) {
		return -1;
	}
	else {
		return strlen(str);
	}
}

int string_tokenize(const char *str, const char *delims, const size_t str_length, char **tokens, const size_t max_token_length, const size_t requested_tokens)
{
	if(str == NULL) {
		return 0;
	}
	if(delims == NULL) {
		return 0;
	}
	if(str_length <= 0) {
		return 0;
	}
	if(tokens == NULL) {
		return 0;
	}
	if(requested_tokens <= 0) {
		return 0;
	}
	if(max_token_length <= 0) {
		return 0;
	}

	int count = 0;
	char original[30];
	char s[2];
	char* c = malloc(10*sizeof(char));
	int i;
	for(i=0; i < (int)requested_tokens-1; i++) {
		if((tokens++ == NULL)) {
			return -1;
		}
	}
	strcpy(original,str);
	strcpy(s, delims);
	
	c = strtok(original, s);
	tokens = &c;
	while(c != NULL) {
		count++;
		c = strtok(NULL, s);
	}
	return count;
}

bool string_to_int(const char *str, int *converted_value)
{
	if(str == NULL) {
		return false;
	}
	if(converted_value == NULL) {
		return false;
	}
	if(strlen(str) > 12) {
		return false;
	}

	if(strpbrk(str, " ")) {
		char* intStr;
		char splitter[12];
		strcpy(splitter, str);
		intStr = strtok(splitter, " ");
		*converted_value = atoi(intStr);
		return true;
	}
	
	*converted_value = atoi(str);
	return true;
}
