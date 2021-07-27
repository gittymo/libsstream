/*  libsstream.h
    ©2021 Morgan Evans */

#ifndef COM_PLUS_MEVANSPN_SSTREAM
#define COM_PLUS_MEVANSPN_SSTREAM

#define SSTREAM_MIN_SIZE 256
#define SSTREAM_REALLOC_SIZE 1024
#define SSTREAM_TEMP_BUFFER_SIZE 4096

#define SSTREAM_READ 0
#define SSTREAM_WRITE 1

#include <inttypes.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int32_t pointer;
    int32_t current_buffer_size;
    char * buffer;
    int type;
} STRINGSTREAM;

STRINGSTREAM * CreateStringStream(const int32_t INITIAL_SIZE);
STRINGSTREAM * CreateStringStreamFromData(const char * data, const int32_t data_length);
void FreeStringStream(STRINGSTREAM * ss);
void StringStreamWrite(STRINGSTREAM * ss, char * pattern, ...);
char * StringStreamToString(STRINGSTREAM * ss);
int StringStreamRead(STRINGSTREAM * ss, char * pattern, ...);
int StringStreamSize(STRINGSTREAM * ss);

void __StringStreamReallocate(STRINGSTREAM * ss, int32_t change);

#endif