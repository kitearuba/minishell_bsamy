#include "../../include/minishell.h"

int	ft_cd(char **argv, t_bash *bash)
{
	if (!argv[1])
	{
		ft_putendl_fd("minishell: cd: missing argument", STDERR_FILENO);
		bash->exit_status = 1;
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		perror("minishell: cd");
		bash->exit_status = 1;
		return (1);
	}
	bash->exit_status = 0;
	return (0);
}
