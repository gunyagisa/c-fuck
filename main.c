#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

typedef struct vector {
    char *head;
    size_t total_size;
    size_t current_size;
}

vector* vec_init()
{
    size_t size = 30;
    vector *vec = (vector *) malloc(sizeof(vector));
    vec->head = (char *) calloc(size, sizeof(char));
    vec->total_size = size;
    vec->current_size = 0;

    return vec;
}

void push_back(vector *vec, char *data, size_t size)
{
    if (vec->total_size >= vec->current_size + size) {
        if (realloc(vec, vec->total_size + size + 30) == NULL) {
            perror("push_back");
            exit(1);
        }

        vec->total_size += size + 30;
    }

    memcpy(vec->head + vec->current_size, data, size);
    vec->current_size += size;
}
