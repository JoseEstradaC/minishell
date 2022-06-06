/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:52:30 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/06 16:34:33 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

// Describes a simple command and arguments
typedef struct s_command
{
	int				number_of_arguments;
	char			**args;
}					t_command;

// Describes a complete command with the multiple pipes if any
// and input/output redirection if any.
typedef struct s_command_table
{
	int				number_of_commands;
	t_command		**commands;
	char			***env;
	char			*input_type;
	char			*input_file;
	char			*out_type;
	char			*out_file;
}					t_command_table;

typedef struct s_env
{
	char			*entry;
	struct s_env	*next;
}					t_env;

char				**lexer_main(char *line);
t_command_table		*parser(char **lexer, char ***env);
void				free_table(t_command_table *table);
int					token_is_pipe(char *token);
int					token_is_input(char *token);
int					token_is_input_append(char *token);
int					token_is_output(char *token);
int					token_is_output_append(char *token);
int					token_is_divider(char *token);
int					token_is_redirrect(char *token);
int					execute(t_command_table *tab);

// Utils
char				*strrange(char *str, int start, int end);
int					len_table(char **table);
char				**join_split(char **a, char **b);
int					del_str_split(char *str, char ***table);
char				*get_env_value(char *key, char **envp);
void				set_env_value(char *key, char *value, char ***envp);
char				*get_path(char *cmd, char **envp);

// Builtins
void				ft_echo(int ac, char **args);
int					ft_cd(char *path, char ***envp);
void				ft_pwd(void);
void				ft_export(char *entry, char ***envp);
void				ft_unset(char *key, char ***envp);
void				ft_env(char **envp);

#endif
