#include "../../include/builtin.h"

char *create_env_entry(char *key, char *value)
{
    char *entry_p1;
    char *final_entry;

    entry_p1 = ft_strjoin(key, "=");
    if(!entry_p1)
        return (NULL);
    final_entry = ft_strjoin(entry_p1, value);
    free(entry_p1);
    return (final_entry);
}

int update_existing_env_var(t_list *node, char *key, char *value)
{
    char *new_content;

    new_content = create_env_entry(key, value);
    if (!new_content)
        return (1);
    free(node->content);
    node->content = new_content;
    return (0);
}

int add_new_env_var(t_list **env_list, char *key, char *value)
{
    char *new_content;
    t_list *new_node;

    new_content = create_env_entry(key, value);
    if (!new_content)
        return (1);
    new_node = ft_lstnew(new_content);
    if (!new_node)
        return (1);
    ft_lstadd_back(env_list, new_node);
    return (0);
}

void ft_set_env_var(t_list **env_list, char *key, char *value)
{
    t_list *current;
    char *env_entry;
    size_t key_len;
    char *equal_sign;

    if (!env_list || !key || !value)
        return;
    key_len = ft_strlen(key);
    current = *env_list;
    while(current)
    {
        env_entry = (char *)current->content;
        equal_sign = ft_strchr(env_entry, '=');
        if (equal_sign && (size_t)(equal_sign - env_entry) == key_len
            && ft_strncmp(env_entry, key, key_len) == 0)
        {
            update_existing_env_var(current, key, value);
            return;
        }
        current = current->next;
    }
    add_new_env_var(env_list, key, value);
}