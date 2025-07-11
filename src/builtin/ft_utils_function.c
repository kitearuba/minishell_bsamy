#include "../../include/builtin.h"

int is_valid_identifier(const char *name)
{
    int i;

    i = 1;
    if (!name || !*name)
        return (0);
    // check the first character
    if (!ft_isalpha(name[0]) && name[0] != '_')
        return (0);
    // rest can be letter, dig, underscore
    while (name[i])
    {
        if(!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int parse_assignement(const char *arg, char **name, char **value)
{
    char *equal_pos;

    if (!arg || !name || !value)
        return (1);
    equal_pos = ft_strchr(arg, '=');
    if (equal_pos)
    {
        *name = ft_substr(arg, 0, equal_pos - arg);
        *value = ft_strdup(equal_pos + 1);
    }
    else
    {
        *name = ft_strdup(arg);
        *value = NULL;
    }
    if (*name == NULL)
        return (1);
    return (0);
}

char **convert_env_list_to_array(t_list *env_list)
{
    int     count;
    char    **env_array;
    t_list  *current;

    count = 0;
    current = env_list;
    while (current)
    {
        count++;
        current = current->next;
    }
    env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array)
        return (NULL);
    current = env_list;
    count = 0;
    while (current)
    {
        env_array[count] = (char *)current->content;
        count++;
        current = current->next;
    }
    env_array[count] = NULL;
    return (env_array);
}