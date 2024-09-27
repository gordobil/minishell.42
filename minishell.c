#include "minishell.h"

int	main(void)
{
  char	*args;

  args = readline("minishell¬");
	if (check_args(args) != 0)
    return (-1);
  minishell(args);
  return (0);
}
