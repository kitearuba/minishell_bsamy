
#include "../../include/builtin.h"

int ft_pwd(void)
{
    char buffer[1024];
    char *current_working_dir;

    current_working_dir = getcwd(buffer, sizeof(buffer));
    if (current_working_dir == NULL)
    {
        perror("minishell: pwd");
        return (1);
    }
    return (0);
}