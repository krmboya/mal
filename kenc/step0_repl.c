#include <stdio.h>

#include <dbg.h>

char* read(char* x)
{
  return x;
}

char* eval(char* x)
{
  return x;
}

char* print(char* x)
{
  return x;
}

char* rep(char* x)
{
  return print(eval(read(x)));
}

int main(int argc, char* argv[])
{
  char input[256];
  char *s = NULL;
  int rc = 0;
  while (1) {
    rc = fputs("user> ", stdout);
    check(rc != EOF, "Could not write to stdout.");
    s = fgets(input, 256, stdin);
    if (s == NULL) {
      break;
    }
    printf("%s", rep(input));
  }
  putchar('\n');
  return 0;
 error:
  return 1;
}
