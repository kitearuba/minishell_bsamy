
#include "../../include/builtin.h"

int process_export_arg(char *arg, t_bash *bash)
{
    char *name;
    char *value;
    int  ret;

    name = NULL;
    value = NULL;
    ret = 0;

    if (!bash)
        return (1);
    if (parse_assignement(arg, &name, &value) != 0)
    {
        ft_printf_fd(STDERR_FILENO, "minishell: export: %s: assignation invalide\n", arg);
        ret = 1;
    }
    else if (!is_valid_identifier(name))
    {
        ft_printf_fd(STDERR_FILENO, "minishell: export: '%s': identifiant non valide\n", arg);
        ret = 1;
    }
    else
        ft_set_env_var(&(bash->env_list), name, value);
    free(name);
    if (value) free(value);
    return (ret);
}

int ft_export(char **argv, t_bash *bash)
{
    int i;
    int exit_code;

    exit_code = 0;
    i = 0;

    if (!bash)
        return (1);
    if (!argv || !argv[0] || !argv[1])
    {
        char **env_array_temp = convert_env_list_to_array(bash->env_list);
        if (!env_array_temp)
            return (1);
        char **sorted_env_array = sort_env_array(env_array_temp);
        if (!sorted_env_array)
        {
            free(env_array_temp);
            return (1);
        }
        print_export_vars(sorted_env_array);
        free(env_array_temp);
        free(sorted_env_array);

        return (0);
    }
    i = 1;
    while (argv[i])
    {
        if (process_export_arg(argv[i], bash) != 0)
            exit_code = 1;
        i++;
    }
    return (exit_code);
}

char **sort_env_array(char **envp)
{
    int     count;
    char    **sorted_arr;
    char    *temp;
    int     i;
    int     j;

    count = 0;
    while (envp[count]) count++;
    sorted_arr = copy_env_array(envp, count);
    if (!sorted_arr) return (NULL);
    i = -1;
    while (i++ < count - 1)
    {
        j = 0;
        while (j < count - i - 1)
        {
            if (ft_strcmp(sorted_arr[j], sorted_arr[j + 1]) > 0) {
                temp = sorted_arr[j];
                sorted_arr[j] = sorted_arr[j + 1];
                sorted_arr[j + 1] = temp;
            }
            j++;
        }
    }
    return (sorted_arr);
}


void print_export_vars(char **envp)
{
    char **sorted_envp;
    int i;

    sorted_envp = sort_env_array(envp);
    if (!sorted_envp)
        return;
    i = 0;
    while (sorted_envp[i])
    {
        print_single_env_entry(sorted_envp[i]);
        i++;
    }
    free(sorted_envp);
}