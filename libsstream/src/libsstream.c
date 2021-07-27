/*  libsstream.c
    A simple wrapper for char arrays that can be used to write data to a string as if it were a stream.
    ©2021 Morgan Evans */

#include "libsstream.h"

STRINGSTREAM * CreateStringStream(const int32_t INITIAL_SIZE)
{
    STRINGSTREAM * ss = (STRINGSTREAM *) malloc(sizeof(STRINGSTREAM));
    ss->current_buffer_size = INITIAL_SIZE > SSTREAM_MIN_SIZE ? INITIAL_SIZE : SSTREAM_MIN_SIZE;
    ss->buffer = (char *) malloc(sizeof(char) * ss->current_buffer_size);
    ss->pointer = 0;
    ss->type = SSTREAM_WRITE;
    return ss;
}

STRINGSTREAM * CreateStringStreamFromData(const char * data, const int32_t data_length)
{
    STRINGSTREAM * ss = NULL;
    if (data != NULL && data_length > 0) {
        ss = (STRINGSTREAM *) malloc(sizeof(STRINGSTREAM));
        if (ss != NULL) {
            ss->current_buffer_size = data_length;
            ss->buffer = (char *) malloc(sizeof(char) * ss->current_buffer_size);
            memcpy(ss->buffer, data, sizeof(char) * data_length);
            ss->pointer = 0;
            ss->type = SSTREAM_READ;
        }
    }
    return ss;
}

void FreeStringStream(STRINGSTREAM * ss)
{
    if (ss != NULL) {
        if (ss->buffer != NULL) {
            free(ss->buffer);
            ss->buffer = NULL;
        }
        ss->current_buffer_size = ss->pointer = 0;
    }
}

void __StringStreamReallocate(STRINGSTREAM * ss, int32_t change)
{
    if (ss != NULL) {
        if (ss->buffer != NULL && ss->current_buffer_size > SSTREAM_MIN_SIZE) {
            ss->current_buffer_size += change != 0 ? change : SSTREAM_REALLOC_SIZE;
            ss->buffer = (char *) realloc(ss->buffer, ss->current_buffer_size);
        }
    }
}

void StringStreamWrite(STRINGSTREAM * ss, char * pattern, ...)
{
    if (ss != NULL && ss->buffer != NULL && pattern != NULL && ss->type == SSTREAM_WRITE) {
        va_list arguments;
        va_start(arguments, pattern);
        char * buffer = (char *) malloc(sizeof(char) * SSTREAM_TEMP_BUFFER_SIZE);
        const int OUTPUT_SIZE = vsprintf(buffer, pattern, arguments) + 1;
        va_end(arguments);
        if (OUTPUT_SIZE > ss->current_buffer_size - ss->pointer) {
            __StringStreamReallocate(ss, OUTPUT_SIZE);
        }
        strcpy(ss->buffer + ss->pointer, buffer);
        ss->pointer += OUTPUT_SIZE - 1;
        free(buffer);
    }    
}

int StringStreamRead(STRINGSTREAM * ss, char * pattern, ...)
{
    if (ss != NULL && ss->buffer != NULL && ss->current_buffer_size > 1 && ss->type == SSTREAM_READ && ss->pointer < ss->current_buffer_size
        && pattern != NULL) {
        int args_count = 0;
        int i = 0;
        while (i < 256 && pattern[i] > 31) {
            if (pattern[i] == '%') args_count++;
            i++;
        }

        if (args_count == 0) return 0;
        
        int char_ptr = ss->pointer + 1, last_arg_char = 0;
        char char_at_ptr = 0;
        int args_read = 0;
        do {
            char_at_ptr = ss->buffer[char_ptr];
            ss->buffer[char_ptr] = 0;
            va_list arguments;
            va_start(arguments, pattern);
            args_read = vsscanf(ss->buffer + ss->pointer, pattern, arguments);
            va_end(arguments);
            ss->buffer[char_ptr] = char_at_ptr;
            char_ptr++;
            if (args_read == args_count && last_arg_char == 0) last_arg_char = char_ptr;
        } while (char_ptr <= ss->current_buffer_size && args_read <= args_count);
        while (ss->buffer[last_arg_char] > 32 && last_arg_char < ss->current_buffer_size) last_arg_char++;
        if (args_read == args_count) ss->pointer = last_arg_char;
        return args_read == args_count ? 1 : 0;
    } else {
        return 0;
    }
}

char * StringStreamToString(STRINGSTREAM * ss)
{
    char * string = NULL;
    if (ss != NULL && ss->pointer > 0) {
        string = (char *) malloc(sizeof(char) * (ss->pointer + 1));
        memcpy(string, ss->buffer, ss->pointer);
        string[ss->pointer] = 0;
    }
    return string;
}

int StringStreamSize(STRINGSTREAM * ss)
{
    int size = 0;
    if (ss != NULL) {
        size = ss->type == SSTREAM_READ ? ss->current_buffer_size : ss->pointer;
    }
    return size;
}