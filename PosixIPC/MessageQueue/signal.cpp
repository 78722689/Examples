#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#define  ONE_K  1024
void StrCln(int);
void DoWork(char **, int);

void ADLM(int size)
{
  char *buffer;
  if (signal((SIGUSR1), StrCln) == SIG_ERR) {
    printf("Could not install user signal");
    abort();
  }
  DoWork(&buffer, size);
  return;
}

void StrCln(int SIG_TYPE)
{
  printf("Failed trying to malloc storage\n");
  return;
}

void DoWork(char **buffer, int size)
{
  while (*buffer !=NULL)
    *buffer = NULL;//= (char *)malloc(size*ONE_K);
  if (*buffer == NULL) {
     if (raise(SIGUSR1)) {
        printf("Could not raise user signal");
        abort();
     }
  }
  return;
}

int main()
{
    ADLM(sizeof(int));
    
    return 1;
}
