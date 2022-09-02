#ifndef LIBSTR_H
#define LIBSTR_H

typedef struct {
	char *ptr;
	size_t len;
} string;

/* initialize string struct, set length to 0 and malloc ptr to 0 
   return 0 on succcess */ 
extern int string_init(string *str);

/* free str->ptr, set str->ptr to NULL and set length to 0 */
extern void string_free(string *str);

/* free and init string */
extern void string_reset(string *str);

/* append formated string to str->ptr, realloc if new len is > than str->len.
   update str->len to new length */
extern int string_append_format(string *str, const char *fmt, ...);

/* replace character N in src string with X
   returns new string on success else NULL */
extern char *string_replace(char *src, char replace, char with);

/* split string src on delimeter into array result, return number of elements
   on success else negative */
extern int string_split(char ***result, const char *src, const char *delim);

extern int char_count(const char *src, const char c);

/*
#ifdef DEV
int main(void)
{
	string str;

	string_init(&str);

	string_append_format(&str, "%s", "hello world");

	printf("%s\n", str.ptr);

	string_append_format(&str, " - appended str %s with length %d", "STRING", strlen("STRING"));

	printf("%s\n", str.ptr);

	string_append_format(&str, " : NUMBERS %d %d", 12, 144444);

	printf("%s\n", str.ptr);

	string_free(&str);

	return 0;
}
#endif
*/

#endif
