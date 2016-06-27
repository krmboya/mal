#include <stdio.h>

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
  while (1) {
    fputs("user> ", stdout);
    fgets(input, 256, stdin);
    printf("%s", rep(input));
  }
  return 0;
}
