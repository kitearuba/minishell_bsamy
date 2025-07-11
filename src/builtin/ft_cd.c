#include "../../include/builtin.h"

char *get_cd_target_path(char **args, t_list *env_list)
{
    char    *target_path;     // Variable 1: Le chemin cible à retourner
    char    **env_array_temp; // Variable 2: Tableau temporaire pour ft_getenv

    target_path = NULL; // Initialisation sécurisée
    env_array_temp = convert_env_list_to_array(env_list);
    if (!env_array_temp)
        return (NULL);
    if (!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        target_path = ft_getenv(env_array_temp, "HOME"); // Utilise le tableau char**
        if (!target_path)
        {
            ft_printf_fd(STDERR_FILENO, "minishell: cd: HOME not set\n");
            free(env_array_temp);
            return (NULL);
        }
    }
    else if (ft_strcmp(args[1], "-") == 0)
    {
        target_path = ft_getenv(env_array_temp, "OLDPWD"); // Utilise le tableau char**
        if (!target_path)
        {
            ft_printf_fd(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
            free(env_array_temp);
            return (NULL);
        }
        target_path = ft_strdup(target_path);
        if (!target_path)
        { // Gérer l'erreur de strdup
             free(env_array_temp);
             return (NULL);
        }
        ft_printf_fd(STDOUT_FILENO, "%s\n", target_path); // Afficher le chemin pour 'cd -'
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
    return (target_path); // Retourne le chemin cible (alloué ou dupliqué)
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
    char    *target_path; // Variable 1
    char    *old_pwd_buf; // Variable 2
    char    **env_array;  // Variable 3: Le nouveau tableau temporaire
    int     exit_status;  // Variable 4

    target_path = NULL;
    old_pwd_buf = NULL;
    exit_status = 0;
    old_pwd_buf = getcwd(NULL, 0); // Alloue de la mémoire pour l'ancien PWD
    if (!old_pwd_buf)
        return (1); // Gérer l'erreur si getcwd échoue
    env_array = convert_env_list_to_array(bash->env_list);
    if (!env_array)
    {
        free(old_pwd_buf);
        return (1); // Gérer l'erreur d'allocation
    }
    if (!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        target_path = ft_getenv(env_array, "HOME"); // Utilise le tableau char**
        if (!target_path)
            ft_printf_fd(STDERR_FILENO, "minishell: cd: HOME not set\n");
    }
    else if (ft_strcmp(args[1], "-") == 0)
    {
        target_path = ft_getenv(env_array, "OLDPWD"); // Utilise le tableau char**
        if (!target_path)
            ft_printf_fd(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
        else
            ft_printf_fd(STDOUT_FILENO, "%s\n", target_path); // Afficher le chemin pour 'cd -' comme bash
    }
    else
        target_path = args[1]; // Le chemin est l'argument directement
    if (target_path && chdir(target_path) != 0)
    {
        ft_printf_fd(STDERR_FILENO, "minishell: cd: %s: %s\n", target_path, strerror(errno));
        exit_status = 1;
    }
    else if (!target_path) // Cas où HOME/OLDPWD n'est pas défini et qu'il n'y a pas d'argument
        exit_status = 1;
    if (exit_status == 0) // Seulement si cd a réussi
        update_pwd_vars(bash, old_pwd_buf); // S'assurer que update_pwd_vars travaille avec t_bash*
    free(old_pwd_buf);
    free(env_array); 
    return (exit_status);
}