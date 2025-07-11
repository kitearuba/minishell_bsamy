
#include "../../include/builtin.h"

int process_export_arg(char *arg, t_bash *bash) // Signature modifiée
{
    char *name;  // Variable 1
    char *value; // Variable 2
    int  ret;    // Variable 3

    name = NULL;
    value = NULL;
    ret = 0;

    // Assurez-vous que bash n'est pas NULL, bien que ft_export devrait déjà le vérifier.
    if (!bash)
        return (1);

    // Analyse l'assignation (ex: "VAR=VALEUR")
    if (parse_assignement(arg, &name, &value) != 0)
    {
        ft_printf_fd(STDERR_FILENO, "minishell: export: %s: assignation invalide\n", arg);
        ret = 1;
    }
    // Vérifie si le nom de la variable est valide
    else if (!is_valid_identifier(name))
    {
        ft_printf_fd(STDERR_FILENO, "minishell: export: '%s': identifiant non valide\n", arg);
        ret = 1;
    }
    // Tente de définir la variable d'environnement en utilisant la liste du shell
    // Note: set_env_var doit prendre t_list **env_list
    else
    {
        // set_env_var ne retourne généralement pas un int mais void.
        // Si elle retourne un int pour indiquer une erreur (ex: malloc fail),
        // alors la condition est correcte. Sinon, elle devrait être void.
        // Assumons qu'elle retourne void ou 0 en cas de succès simple.
        ft_set_env_var(&(bash->env_list), name, value);
        // Si set_env_var peut échouer et indiquer une erreur, vous devriez vérifier ici.
        // Par exemple: if (set_env_var(&(bash->env_list), name, value) != 0) { ret = 1; }
    }

    // Libère la mémoire allouée pour le nom et la valeur (peu importe le succès/échec)
    free(name);
    if (value) free(value); // Libérer 'value' seulement s'il a été alloué par parse_assignement
    return (ret);
}

int ft_export(char **argv, t_bash *bash) // Signature modifiée pour prendre t_bash *bash
{
    int i;         // Variable 1
    int exit_code; // Variable 2

    exit_code = 0;
    i = 0;

    if (!bash) // Vérification du pointeur bash
        return (1);

    // Si 'export' est appelé sans arguments (ex: `export` ou `export `)
    if (!argv || !argv[0] || !argv[1])
    {
        // Option 1 (recommandée): Si print_export_vars a été adaptée pour prendre t_bash*
        // print_export_vars(bash);

        // Option 2 (si print_export_vars DOIT prendre char **):
        char **env_array_temp = convert_env_list_to_array(bash->env_list);
        if (!env_array_temp)
            return (1); // Gérer l'erreur d'allocation

        char **sorted_env_array = sort_env_array(env_array_temp);
        if (!sorted_env_array) {
            free(env_array_temp);
            return (1);
        }

        print_export_vars(sorted_env_array);

        free(env_array_temp);
        // Important: sorted_env_array contient des pointeurs vers les mêmes strings que env_array_temp.
        // Seul le tableau de pointeurs lui-même doit être libéré.
        free(sorted_env_array);

        return (0);
    }

    // Traitement des arguments un par un, en commençant par argv[1]
    i = 1;
    while (argv[i])
    {
        // Appelle la fonction auxiliaire pour traiter l'argument.
        // Passe 'bash' pour que process_export_arg puisse accéder à bash->env_list.
        if (process_export_arg(argv[i], bash) != 0) {
            exit_code = 1; // Si un seul argument est invalide, le code de sortie est 1.
        }
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