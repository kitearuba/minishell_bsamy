#include "../../include/builtin.h"



int ft_unset(char **args, t_bash *bash)
{
    int i;
    int exit_status;

    if (!args || !bash)
        return (1);
    exit_status = 0;
    i = 1; // to ignore unset
    if (!args[i])
        return (0);
    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
        {
            ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            exit_status = 1;
        }
        else
            remove_env_var(bash, args[i]);
        i++;
    }
    return (exit_status);
}