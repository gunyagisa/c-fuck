#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define MEMORY_SIZE 128
#define STACK_SIZE  64

u_int64_t stack[STACK_SIZE];
u_int64_t sp = 0;

void push(u_int64_t addr)
{
  stack[sp++] = addr;
}

u_int64_t pop()
{
  u_int64_t ret = stack[--sp];
  return ret;
}

int main(int argc, char * argv[])
{
  if (argc < 2) {
    printf("few arguments\n");
    exit(1);
  }

  char *input = argv[1];
  u_int8_t mem[MEMORY_SIZE] = {};
  u_int32_t ptr = 0;


  u_int8_t output[256] = {};
  u_int pos = 0;

  int n = 0;
  char ch;

  while (*input != 0) {
    fprintf(stderr, "[%x]", input);
    fprintf(stderr, "implemented: %c\t ptr: %d\t *ptr: %d\t sp: %ld\n", *input, ptr, mem[ptr], sp);
    switch (*input) {
      case '>':
        ++ptr;
        ++input;
        break;
      case '<':
        --ptr;
        ++input;
        break;
      case '+':
        mem[ptr]++;
        ++input;
        break;
      case '-':
        mem[ptr]--;
        ++input;
        break;
      case '.':
        output[pos++] = mem[ptr];
        //putchar(mem[ptr]);
        ++input;
        break;
      case ',':
        ch = getchar();
        if (ch != EOF)
          mem[ptr] = ch;
        ++input;
        break;
      case '[':
        if (mem[ptr] == 0) {
          n = 0;
          while (1) {
            ++input;
            if (*input == ']' && n == 0) {
              ++input;
              break;
            }

            if (*input == '[')
              n++;
            else if (*input == ']')
              n--;

          }
        } else {
          push((u_int64_t)input);
          ++input;
        }
        break;
      case ']':
        if (mem[ptr] != 0) {
          input = stack[sp-1];
          input++;
        } else {
          --sp;
          ++input;
        }
        break;
      default:
        fprintf(stderr, "can not implement: %c\n", *input);
        ++input;
        break;
    }
  }

  fprintf(stdout, "output: %s\n", output);
  return 0;
}
