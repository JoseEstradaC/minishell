/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:52:30 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/02 07:00:31 by jarredon         ###   ########.fr       */
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

char			**lexer_main(char *line);
t_command_table	*parser(char **lexer);
void			free_table(t_command_table *table);
char			**join_tables(char **a, char **b);
char			*get_path(char *cmd);
int				execute(t_command_table *tab);

#endif
