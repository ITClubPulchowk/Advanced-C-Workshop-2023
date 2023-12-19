#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
	size_t len;
	const char *str;
} String;

static String interned_strings[256];
static int interned_strings_count;

const char *string_intern_range(const char *start, const char *end)
{
	size_t len = end - start;
	
	for (String *it = interned_strings; it != interned_strings + interned_strings_count; ++it) {
		if (it->len == len && strncmp(it->str, start, len) == 0) {
			return it->str;
		}
	}
	char *str = malloc(len + 1);
	memcpy(str, start, len);
	str[len] = 0;
	interned_strings[interned_strings_count++] = (String){.len = len, .str = str};
	return str;
}

const char *str_intern(const char *str)
{
	return string_intern_range(str, str + strlen(str));
}

int main()
{
	char x[] = "Identical String";
	char y[] = "Identical String";
	assert(x != y);
	assert(str_intern(x) == str_intern(y));
	char z[] = "Identical";
	assert(str_intern(x) != str_intern(z));
	return 0;
}