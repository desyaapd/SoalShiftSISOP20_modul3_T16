#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  int fd[2];
pid_t pid;

  //membuat proses pipe
  pipe(fd);
  pid = fork();

  //membaca fd (file descriptor) dengan fungsi dup2 pada direktori tersebut
  if (pid == 0) {
    dup2(fd[1], 1);
  close(fd[0]);
  
  //membaca list file dalam direktori
    char *argv[] = {"ls", NULL};
    execv("/bin/ls", argv);
  }
  while(wait(NULL) > 0);

  dup2(fd[0], 0);
  close(fd[1]);
  
  //menghitung banyaknya file yang telah didapat dengan fungsi wc(word count)
  char *argv[] = {"wc", "-l", NULL};
  execv("/usr/bin/wc", argv);

}

