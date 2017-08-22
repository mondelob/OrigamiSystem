#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define PROGRAM_NAME "orsh"
/* The name of the program */

#define DEFAULT_PROMPT ">"
/* The default prompt */

#define SH_SL_ERROR 54
/* The return code of sh_splitline error */

#define SH_SL_BUFSIZE 64
/* The buf of the splitted line */

#define SH_SL_DELIMITERS "\t\r\n\a "
/* The delimiters to split the line */

#define SH_LA_ERROR 64
/* The return code of sh_launch error */

/* Return codes:
 * -  0: all correct
 * -  1:
 * - 54: error on sh_splitline
 * - 64: error on sh_launch
*/

int sh_cd(char ** argv);
int sh_help(char ** argv);
int sh_exit(char ** argv);
/* Declaration of builtin functions */

char *
builtin_str[] =
{
  "cd",
  "help",
  "exit"
};
/* The built-in shell commands */

int
(*builtin_func[]) (char **) =
{
  &sh_cd,
  &sh_help,
  &sh_exit
};
/* The built-in corresponding functions */

int
sh_num_builtin()
{
  return sizeof(builtin_str) / sizeof(char *);
}
/* The number of built-ins */

int
sh_cd(char ** argv)
{

  if (argv[1] == NULL)
    fprintf(stderr, "%s: error on: 'cd', expected argument\n",
      PROGRAM_NAME);
  else
    if (chdir(argv[1]) != 0)
      fprintf(stderr, "%s: cd: %s\n", PROGRAM_NAME, strerror(errno));
  /* Check for the first argument existence */

  return 1;
}
/* Change directory built-in function */

int
sh_help(char ** argv)
{

  printf("Print help\n");
  /* Show help */

  return 1;
}
/* Help built-in function */

int
sh_exit(char ** argv)
{
  return 0;
}
/* Exit built-in function*/

ssize_t
sh_readline(char ** line)
{

  ssize_t bufsize = 0;
  /* The buffer size */

  bufsize = getline(line, &bufsize, stdin);
  /* Get the readed line */

  return bufsize;

}
/* Read the user line */

char **
sh_splitline(char * line)
{

  int bufsize = SH_SL_BUFSIZE;
  /* The buffer size */

  int position = 0;
  /* The position on token list */

  char ** argv;
  /* The list of tokens */

  char * token;
  /* The splitted token */

  if ((argv = malloc(bufsize * sizeof(char *))) == NULL)
  {
    fprintf(stderr, "%s: error allocating memory for tokens on 'sh_splitline'\n",
      PROGRAM_NAME);
    exit(SH_SL_ERROR);
  }
  /* Allocate memory for tokens and handle the error */

  token = strtok(line, SH_SL_DELIMITERS);
  /* Split the first token */

  while (token != NULL)
  {
    argv[position] = token;
    /* Assign token */

    position++;
    /* Add one to position */

    if (position >= bufsize)
    {

      bufsize += SH_SL_BUFSIZE;
      /* Add more buffer */

      if ((argv = realloc(argv, bufsize * sizeof(char *))) == NULL)
      {
        fprintf(stderr, "%s: error reallocating memory for tokens on 'sh_splitline'\n",
          PROGRAM_NAME);
        exit(SH_SL_ERROR);
      }
      /* Allocate memory and handle error */

    }
    /* Allocate more memory if necessary */

    token = strtok(NULL, SH_SL_DELIMITERS);
    /* Split the next token */

  }
  /* Add every splitted token from the readed line */

  return argv;

}
/* Split the line per arguments */

int
sh_launch(char ** argv)
{

  pid_t pid;
  /* The return of the fork function */

  pid_t wpid;
  /* The waiting PID */

  int status;
  /* The wait status */

  if ((pid = fork()) < 0)
  {
    fprintf(stderr, "%s: error forking main program\n", PROGRAM_NAME);
    exit(SH_LA_ERROR);
  }
  /* Fork to the new program, handle error on forking */

  if (pid == 0)
  {
    if (execvp(argv[0], argv) < 0)
    {
      fprintf(stderr, "%s: error executing the program: '%s'\n", PROGRAM_NAME,
        argv[0]);
      exit(SH_LA_ERROR);
    }
    exit(0);
  }
  /* Child process, execute the input program */
  else
  {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while(WIFEXITED(status) == 0 && WIFSIGNALED(status) == 0);
    /* Wait for child PID */
  }
  /* Parent process */

  return 1;

}
/* Launch a set of commands */

int
sh_execute(char ** argv)
{

  if (argv[0] == NULL)
    return 1;
  /* Don't parse empty command */

  for (int i = 0; i < sh_num_builtin(); i++)
    if (strcmp(argv[0], builtin_str[i]) == 0)
      return (*builtin_func[i])(argv);
  /* Check for a built-in function */

  return sh_launch(argv);
  /* Execute normally the function */

}
/* Execute the command */

void
sh_loop(char * sh_prompt)
{

  char * line;
  /* The readed line */

  ssize_t len;
  /* The size of the user input */

  char ** argv;
  /* The readed arguments */

  int status;
  /* The status of the shell */

  do {

    printf("%s ", sh_prompt);
    /* Show prompt */

    len = sh_readline(&line);
    /* Read the user input line */

    // if (len < 2)
    //   continue;
    /* The user must have input something */

    argv = sh_splitline(line);
    /* Split the arguments */

    status = sh_execute(argv);
    /* Execute the command */

    free(line);
    free(argv);
    /* Free the memory */

  } while(status);

}
/* Main loop of the shell */

int
main(int argc, char * argv[])
{

  char * sh_prompt = DEFAULT_PROMPT;
  /* Load configuration files */

  sh_loop(sh_prompt);
  /* Execute main loop */

  /* Perform shutdown */

  return 0;

}
