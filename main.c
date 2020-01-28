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
        perror("[*][malloc_e]");
        exit(1);
    }

    fprintf(stderr, "[-][malloc_e] %p\n", v);

    return v;
}

void * realloc_e (void *old, size_t size)
{
    void *v;
    fprintf(stderr, "[-][realloc_e] size: %ld\n", size);
    if ((v = realloc(old, size)) == NULL) {
        perror("[*][realloc_e]");
        exit(1);
    }

    fprintf(stderr, "[-][realloc_e] %p\n", v);

    return v;
}

vector* vec_init()
{
    size_t size = 125;
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
    size_t add_size = 125;
    if (vec->total_size <= vec->current_size + size) {
        char *new_head;
        new_head = realloc_e(vec->head, vec->total_size + size + add_size);

        vec->head = new_head;
        vec->total_size += size + add_size;
    }

    memcpy(vec->head + vec->current_size, data, size);

    vec->current_size += size;
}

void printf_vec(vector *vec)
{
    size_t res, used;
    res = vec->total_size;
    used = vec->current_size;
    printf("\n-----<vector output>-----\n");
    printf("reserved: %ld, used: %ld, free: %ld\n\n", res, used, res - used);
    printf("%s\n", vec->head);
}



void file_handler(const char * const file_name, vector *vec)
{
    FILE *fp;
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("file_handler");
        exit(1);
    }

    size_t size = 125;
    char buf[size];
    size_t read_size;

    for (;;) {
        memset(buf, '0', size);
        read_size = fread(buf, 1, size, fp);

        push_back(vec, buf, read_size);
        
        if (read_size != size) break;
    }

    fclose(fp);
}


int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("few argument\n");
        exit(1);
    }

    vector *vec = vec_init();

    file_handler(argv[1], vec);

    printf_vec(vec);

    destroy_vec(vec);
}
