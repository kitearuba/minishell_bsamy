/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:21:19 by chrrodri          #+#    #+#             */
/*   Updated: 2025/05/20 16:35:24 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                               DEPENDENCIES                                 */
/* ************************************************************************** */
// --- Standard Libraries ---
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

// --- Readline Libraries ---
# include <readline/readline.h>
# include <readline/history.h>

// --- Libft Custom Library ---
# include "../libft/include/libft.h"
# include "builtin.h"
# include "struct.h"

/* ************************************************************************** */
/*                               Macros                                       */
/* ************************************************************************** */
# define BUILTIN_CMDS ":echo:cd:pwd:export:unset:env:exit"

/* ************************************************************************** */
/*                               Structures                                   */
/* ************************************************************************** */
typedef struct	s_bash
{
    char	**env;
    int		exit_status;
} t_bash;

/* ************************************************************************** */
/*                              FUNCTION PROTOTYPES                           */
/* ************************************************************************** */

// --- Tokenizer ---
t_token		*tokenize_input(const char *input);
t_token		*new_token(t_token_type type, const char *start, size_t len);
void		add_token(t_token **head, t_token *new);
size_t		handle_word(const char *input, t_token **tokens, size_t i);
char		*extract_quoted_token(const char *line, size_t *index);
void		print_tokens(t_token *list);

// --- Parser ---
t_command	*parse_tokens(t_token *tokens);

// --- Command Execution ---
int			execute_command(char **argv, t_bash *bash);
int			exec_external(char **args, t_bash *bash);
int			is_builtin(const char *cmd);
int			run_builtin(char **argv, t_bash *bash);

// --- Command Path Resolution ---
char		*get_cmd_path(char *cmd, char **envp);

// --- Environment Variable Handling ---
char		*ft_getenv(char **envp, char *key);

// --- Utilities ---
void	    free_2d_array(char **arr);
void	    free_tokens(t_token *tokens);

#endif /* MINISHELL_H */
