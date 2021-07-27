/*	testlib.c
		Test libsstream
		(C)2021 Morgan Evans */

#include "libsstream.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv)
{
	char * testdata = "Hello 123 world! 456\0";
	printf("Full string = '%s'\n", testdata);
	STRINGSTREAM * ss = CreateStringStreamFromData(testdata, strlen(testdata));
	if (ss != NULL) {
		char h[8], w[8];
		int val = 0;
		if (StringStreamRead(ss, "%s %i %s", &h, &val, &w)) {
			printf("First string = %s, Second string = %s, int value = %i\n", h, w, val);
		}
		int val2 = 0;
		if (StringStreamRead(ss, "%i", &val2)) {
			printf("Second int value = %i\n", val2);
		}
		int val3 = 0;
		if (StringStreamRead(ss, "%i", &val3)) {
			printf("Third int value = %i\n", val3);
		} else {
			printf("Can't read fifth value.\n");
		}
		FreeStringStream(ss);
	} else {
		printf("Problem creating StringStream structure from data.\n");
	}
	return 0;
}
