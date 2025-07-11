/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                         :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:21:19 by chrrodri          #+#    #+#             */
/*   Updated: 2025/05/20 16:35:24 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "struct.h"

/* ************************************************************************** */
/*                             FORWARD DECLARATIONS                           */
/* ************************************************************************** */

typedef struct s_bash t_bash;

typedef enum e_builtin_type
{
    NO_BUILTIN = 0,
    BUILTIN_CD,
    BUILTIN_PWD,
    BUILTIN_ECHO,
    BUILTIN_ENV,
    BUILTIN_EXIT,
    BUILTIN_EXPORT,
    BUILTIN_UNSET
}   t_builtin_type;

/* ************************************************************************** */
/*                             BUILTIN FUNCTIONS                              */
/* ************************************************************************** */


int run_builtin(char **argv, t_bash *bash);
int	is_builtin(const char *cmd);

// cd
char *get_cd_target_path(char **args, t_list *env_list);
int update_pwd_vars(t_bash *minishell, char *old_pwd_buf);
int ft_cd(char **args, t_bash *minishell);

// echo
int ft_echo(char **argv);

// exit
long long ft_atoll(const char *str);
 int is_valid_num(char *str);
int ft_exit(char **argv, t_bash *shell);

// env
int ft_env(t_bash *minishell);

// export
int ft_export(char **argv, t_bash *bash);
char **sort_env_array(char **envp);
void print_export_vars(char **envp);
int process_export_arg(char *arg, t_bash *bash);

// pwd
int ft_pwd(void);

// unset
int ft_unset(char **args, t_bash *bash);

// utils
int is_valid_identifier(const char *name);
int parse_assignement(const char *arg, char **name, char **value);

//env
int count_env_vars(char **envp);
char *get_var_name(const char *env_line);
char **copy_env_array(char **envp, int count);
char	*ft_getenv(char **envp, char *key);
void remove_env_var(t_bash *bash, const char *name);
char *create_env_entry(char *key, char *value);
int update_existing_env_var(t_list *node, char *key, char *value);
int add_new_env_var(t_list **env_list, char *key, char *value);
void ft_set_env_var(t_list **env_list, char *key, char *value);
void print_single_env_entry(char *env_entry);
char **convert_env_list_to_array(t_list *env_list);

#endif /* BUILTIN_H */