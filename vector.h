#include <stdio.h>

typedef struct {
    char *head;
    size_t total_size;
    size_t current_size;
} Vector;

void file_handler(const char const *, Vector *);

Vector *vec_init();
void destroy_vec(Vector *vec);
