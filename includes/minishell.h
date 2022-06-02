/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:52:30 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/03 01:10:59 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

// Describes a simple command and arguments
typedef struct s_command
{
	int			number_of_arguments;
	char		**args;
}				t_command;

// Describes a complete command with the multiple pipes if any
// and input/output redirection if any.
typedef struct s_command_table
{
	int			number_of_commands;
	t_command	**commands;
	char		*input_type;
	char		*input_file;
	char		*out_type;
	char		*out_file;
}				t_command_table;

typedef struct s_env
{
	char			*entry;
	struct s_env	*next;
}					t_env;

char			**lexer_main(char *line);
t_command_table	*parser(char **lexer);
void			free_table(t_command_table *table);
char			**join_tables(char **a, char **b);
char			*get_path(char *cmd);
int				execute(t_command_table *tab);

t_env			*envp_to_list(char **envp);
void			free_env(t_env **env);
char			**list_to_envp(t_env *env);
char			*get_env_value(char *key, t_env *env);
int				add_to_env(char *entry, t_env **env);
int				del_from_env(char *key, t_env **env);

#endif
