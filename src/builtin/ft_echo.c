
#include "../../include/builtin.h"

int ft_echo(char **argv)
{
  int i;
  int no_new_line;

  i = 1; // skipping echo arg
  no_new_line = 1;
  // check for -n
  while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
  {
    no_new_line = 0;
    i++;
  }
  while (argv[i])
  {
    ft_printf_fd(STDOUT_FILENO, "%s", argv[i]);
    if (argv[i + 1])
      ft_printf_fd(STDOUT_FILENO, " ");
    i++;
  }
  if (!no_new_line)
    ft_printf_fd(STDOUT_FILENO, "\n");
  return (0);
}