#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main()
{

  int pipe_fd[2];
  pid_t pid;
  char write_msg[] = "Hello word from parent ";
  char read_msg[100];

  if (pipe(pipe_fd) == -1)
  {
    perror("Pipe is faild\n");
    return 1;
  }

  pid = fork();

  if (pid < 0)
  {
    perror("Fork is faild\n");
    return 1;
  }

  if (pid == 0)
  {
    close(pipe_fd[1]);

    read(pipe_fd[0], read_msg, sizeof(read_msg));
    printf("The message recived is : %s\n", read_msg);
    close(pipe_fd[0]);
    printf("Child prcess is terminated\n ");
  }
  else
  {

    close(pipe_fd[0]);
    printf("Parent process is writing to the pipe \n");
    write(pipe_fd[1], write_msg, strlen(write_msg));
    close(pipe_fd[1]);

    wait(NULL);
    printf("Parent process is terminated\n");
  }
}
