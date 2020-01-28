#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

typedef struct {
    char *head;
    size_t total_size;
    size_t current_size;
} vector;

void * malloc_e(size_t size)
{
    void *v;
    if ((v = malloc(size)) == NULL) {
        perror("malloc_e");
        exit(1);
    }

    fprintf(stderr, "[malloc_e] %p\n", v);

    return v;
}

void * realloc_e (void *old, size_t size)
{
    void *v;
    if ((v = realloc(old, size)) == NULL) {
        perror("realloc_e");
        exit(1);
    }

    fprintf(stderr, "[realloc_e] %p\n", v);

    return v;
}

vector* vec_init()
{
    size_t size = 30;
    vector *vec = (vector *) malloc_e(sizeof(vector));
    vec->head = (char *) malloc_e(sizeof(char) * size);
    vec->total_size = size;
    vec->current_size = 0;

    return vec;
}

void destroy_vec(vector *vec) 
{
    free(vec->head);
    free(vec);
}

void push_back(vector *vec, char *data, size_t size)
{
    if (vec->total_size <= vec->current_size + size) {
        char *new_head;
        new_head = realloc_e(vec, vec->total_size + size + 30);

        vec->head = new_head;
        vec->total_size += size + 30;
    }

    memcpy(vec->head + vec->current_size, data, size);

    vec->current_size += size;
}

void printf_vec(vector *vec)
{
    printf("%s\n", vec->head);
}

int main(int argc, char *argv[])
{
    vector *vec = vec_init();

    char *buf = "hello world";

    push_back(vec, buf, strlen(buf));
    printf_vec(vec);

    destroy_vec(vec);
}
