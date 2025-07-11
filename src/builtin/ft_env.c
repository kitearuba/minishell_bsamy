
#include "../../include/builtin.h"

int ft_env(t_bash *minishell)
{
    t_list *current;
    char *env_entry;

    if (!minishell || !minishell->env_list)
    {
        ft_printf_fd(STDERR_FILENO, "minishell: env: environment not found or empty\n");
        return (0);
    }
    current = minishell->env_list;
    while(current)
    {
        env_entry = (char *)current->content;
        if (env_entry && ft_strchr(env_entry, '='))
            ft_printf_fd(STDOUT_FILENO, "%s\n", env_entry);
        current = current->next;
    }
    return (0);
}