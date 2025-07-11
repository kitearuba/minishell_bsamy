#include "../../include/builtin.h"

void remove_env_var(t_bash *bash, const char *name)
{
    char **new_env;
    char *var_name;
    int i;
    int j;
    int count;

    if (!bash || !bash->env || !name)
        return;
    count = count_env_vars(bash->env);
    new_env = malloc(sizeof(char *) * (count + 1));
    if (!new_env)
        return;
    i = 0;
    j = 0;
    while (bash->env[i])
    {
        var_name = get_var_name(bash->env[i]);
        if (var_name && ft_strcmp(var_name, name) != 0)
        {
            new_env[j] = ft_strdup(bash->env[i]);
            j++;
        }
        free(var_name);
        free(bash->env[i]);
        i++;
    }
    new_env[j] = NULL; 
    free(bash->env);
    bash->env = new_env;
}