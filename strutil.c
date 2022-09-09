#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "strutil.h"

int string_init(string *str)
{
	str->ptr = malloc(1);

	if(str->ptr == NULL) {
		fprintf(stderr, "ERROR ALLOC %s:%d\n", __FILE__, __LINE__);
		return -1;
	}

	str->len = 0;

	return 0;
}

void string_free(string *str)
{
	free(str->ptr);
	str->ptr = NULL;
	str->len = 0;
}

void string_reset(string *str)
{
	string_free(str);
	string_init(str);
}

int string_append_format(string *str, const char *fmt, ...)
{
	va_list args;
	va_start (args, fmt);
	
	size_t fmt_len = vsnprintf(NULL, 0, fmt, args) + 1;
	size_t new_len = 0;

	va_end(args);

	va_start (args, fmt);
	char *tmp = NULL;

	tmp = calloc(fmt_len + 1, sizeof(char));

	if(tmp == NULL) {
		fprintf(stderr, "ERROR ALLOC %s:%d\n", __FILE__, __LINE__);
		va_end(args);
		return -1;
	}

	vsnprintf(tmp, fmt_len, fmt, args);

	new_len = str->len + fmt_len + 1;

	str->ptr = realloc(str->ptr, new_len);

	if(str->ptr == NULL) {
		fprintf(stderr, "ERROR ALLOC %s:%d\n", __FILE__, __LINE__);
		free(tmp);
		va_end(args);
		return -1;
	}

	if(str->len == 0) {
		strncpy(str->ptr, tmp, fmt_len);
	}
	else {
		strncat(str->ptr, tmp, fmt_len);
	}
	
	str->len = new_len;

	free(tmp);

	va_end(args);

	return 0;
}

int char_count(const char *src, const char c)
{
	int n = 0;

	if(src == NULL) {
		return -1;
	}

	for(size_t i = 0; i < strlen(src); i++) {
		if(src[i] == c) n++;
	}

	return n;
}

char *string_replace(char *src, char replace, char with)
{
	if(src == NULL) {
		return NULL;
	}

	char *p = strdup(src);

	for(size_t i = 0; i < strlen(p); i++) {
		if(p[i] == replace) {
			p[i] = with;
		}
	}

	return p;
}

int string_split(char ***result, const char *src, const char *delim)
{
	if(src == NULL) {
		return -1;
	}

	int delim_count = 0;
	int index = 0;
	const char *tmp = src;
	char *copy = strdup(src);
	char *token = NULL;

	while((tmp = strstr(tmp, delim))) {
		tmp++;
		delim_count++;
	}

	delim_count++;

	if(delim_count == 0) {
		free(copy);
		return -1;
	}

	(*result) = malloc(delim_count * sizeof(char *));

	if((*result) == NULL) {
		free(copy);
		return -1;
	}

	while((token = strsep(&copy, delim)) != NULL) {
		(*result)[index] = strdup(token);
		index++;
	}

	free(token);
	free(copy);
	return delim_count;
}
