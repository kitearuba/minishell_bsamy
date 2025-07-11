#include "../../include/builtin.h"

char *get_cd_target_path(char **args, t_list *env_list)
{
    char    *target_path;
    char    **env_array_temp;

    target_path = NULL;
    env_array_temp = convert_env_list_to_array(env_list);
    if (!env_array_temp)
        return (NULL);
    if (!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        target_path = ft_getenv(env_array_temp, "HOME");
        {
            ft_printf_fd(STDERR_FILENO, "minishell: cd: HOME not set\n");
            free(env_array_temp);
            return (NULL);
        }
    }
    else if (ft_strcmp(args[1], "-") == 0)
    {
        target_path = ft_getenv(env_array_temp, "OLDPWD");
        if (!target_path)
        {
            ft_printf_fd(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
            free(env_array_temp);
            return (NULL);
        }
        target_path = ft_strdup(target_path);
        if (!target_path)
        {
             free(env_array_temp);
             return (NULL);
        }
        ft_printf_fd(STDOUT_FILENO, "%s\n", target_path);
    }
    else
    {

        target_path = ft_strdup(args[1]);
        if (!target_path)
        {
            free(env_array_temp);
            return (NULL);
        }
    }
    free(env_array_temp);
    return (target_path);
}

int update_pwd_vars(t_bash *minishell, char *old_pwd_buf)
{
    char new_pwd_buf[1024];

    ft_set_env_var(&minishell->env_list, "OLDPWD", old_pwd_buf);
    if (getcwd(new_pwd_buf, sizeof(new_pwd_buf)))
    {
        ft_set_env_var(&minishell->env_list, "PWD", new_pwd_buf);
        return (0);
    }
    else
    {
        perror("minishell: cd: error getting new directory after chdir");
        return (1);
    }
}

int ft_cd(char **args, t_bash *bash)
{
    char    *target_path;
    char    *old_pwd_buf;
    char    **env_array;
    int     exit_status;

    target_path = NULL;
    old_pwd_buf = NULL;
    exit_status = 0;
    old_pwd_buf = getcwd(NULL, 0);
    if (!old_pwd_buf)
        return (1);
    env_array = convert_env_list_to_array(bash->env_list);
    if (!env_array)
    {
        free(old_pwd_buf);
        return (1);
    }
    if (!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        target_path = ft_getenv(env_array, "HOME");
        if (!target_path)
            ft_printf_fd(STDERR_FILENO, "minishell: cd: HOME not set\n");
    }
    else if (ft_strcmp(args[1], "-") == 0)
    {
        target_path = ft_getenv(env_array, "OLDPWD");
        if (!target_path)
            ft_printf_fd(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
        else
            ft_printf_fd(STDOUT_FILENO, "%s\n", target_path);
    }
    else
        target_path = args[1];
    if (target_path && chdir(target_path) != 0)
    {
        ft_printf_fd(STDERR_FILENO, "minishell: cd: %s: %s\n", target_path, strerror(errno));
        exit_status = 1;
    }
    else if (!target_path)
        exit_status = 1;
    if (exit_status == 0)
        update_pwd_vars(bash, old_pwd_buf);
    free(old_pwd_buf);
    free(env_array); 
    return (exit_status);
}