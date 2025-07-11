#include "../../include/builtin.h"

int count_env_vars(char **envp)
{
    int count;

    count = 0;
    if (!envp)
        return (0);
    while (envp[count])
        count++;
    return(count);
}

char *get_var_name(const char *env_line)
{
    char *equal_pos;
    char *name;
    int len;

    equal_pos = ft_strchr(env_line, '=');
    if (!equal_pos)
        return (ft_strdup(env_line)); // Si pas de '=', toute la ligne est le nom
    
    len = equal_pos - env_line;
    name = malloc(len + 1);
    if (!name)
        return (NULL);
    
    ft_strlcpy(name, env_line, len + 1);
    return (name);
}

char **copy_env_array(char **envp, int count)
{
    char **arr;
    int i;

    arr = malloc(sizeof(char *) * (count + 1));
    if (!arr) return (NULL);
    i = 0;
    while (i < count)
    {
        arr[i] = envp[i];
        i++;
    }
    arr[i] = NULL;
    return (arr);
}

void print_single_env_entry(char *env_entry)
{
    char *equal_pos;
    char *name;
    char *value;

    equal_pos = ft_strchr(env_entry, '=');
    if (equal_pos)
    {
        name = ft_substr(env_entry, 0, equal_pos - env_entry);
        value = equal_pos + 1;
        printf("declare -x %s=\"%s\"\n", name, value);
        free(name);
    }
    else
        printf("declare -x %s\n", env_entry);
}