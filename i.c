/* a surprising useful little program! (tridge@samba.org) */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

static char escape[14] = {'0',0,0,0,0,0,0,'a','b','t','n','v','f','r'};

static void print_binary(unsigned long long v)
{
	unsigned long long bit;

	if (v == 0ULL)
		printf(" 0b0");
	else
		printf(" 0b");

	for (bit = 1ULL<<63; bit; bit>>=1)
		if (v >= bit)
			printf("%c", (v & bit) ? '1' : '0');
}

static unsigned long long convert_binary(const char *s)
{
	unsigned long long v = 0;

	for (; *s; s++) {
		v <<= 1;
		if (*s == '1')
			v |= 1;
	}
	return v;
}

static void print_one(unsigned long long v) 
{
	printf("%llu 0x%llX 0%llo", v, v, v);
	print_binary(v);

	if (v < 256) {
		if (isprint(v))
			printf(" '%c'", (unsigned char)v);
		else if (v < 14 && escape[v] != 0)
			printf(" '\\%c'", escape[v]);
	}

	if (v < 256 && isprint(v)) printf(" '%c'", (unsigned char)v);
	printf("\n");
}

int main(int argc,char *argv[])
{
	int i;
	char *p;
	unsigned long long v;

	for(i = 1; i < argc; i++) {
		if (strncasecmp(argv[i],"0b",2) == 0) {
			v = convert_binary(argv[i]+2);
			p = NULL;
		} else
			v = strtoull(argv[i],&p,0);

		if (p == argv[i])
			for(;*p;p++)
				print_one(*(unsigned char *)p);
		else
			print_one(v);
	}

	return EXIT_SUCCESS;
}
