/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:18:33 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/01 12:59:22 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				token_is_divider(char *token, int all_dividers);
t_command		*create_command(char **start, int number);

void	free_table(t_command_table *table)
{
	int	index;

	index = table->number_of_commands;
	while (index > 0)
	{
		index--;
		ft_split_free(table->commands[index]->args);
		free(table->commands[index]);
	}
	free(table->commands);
	free(table);
}

void	join_to_command_array(t_command_table *table, t_command *command_new)
{
	t_command	**temp;
	int			index;

	temp = (t_command **)ft_calloc(sizeof(t_command *),
									table->number_of_commands + 1);
	index = 0;
	while (table->number_of_commands != index)
	{
		temp[index] = table->commands[index];
		index++;
	}
	temp[index] = command_new;
	free(table->commands);
	table->commands = temp;
	table->number_of_commands++;
}

t_command_table	*parser(char **lexer)
{
	t_command_table	*table;
	char			**start;
	int				args_count;

	if (ft_split_count(lexer) < 1)
		return (NULL);
	table = (t_command_table *)ft_calloc(1, sizeof(t_command_table));
	while (*lexer && !token_is_divider(*lexer, 0))
	{
		start = lexer;
		args_count = 1;
		lexer++;
		while (*lexer && !token_is_divider(*lexer, 1))
		{
			args_count++;
			lexer++;
		}
		join_to_command_array(table, create_command(start, args_count));
		if (!(*lexer))
			break ;
		lexer++;
	}
	/*
	lexer--;
	if (ft_strlen(*lexer) == 1 && **lexer == '|')
	{
		ft_putstr_fd("Error pipe not properly closed\n", 2);
		free_table(table);
		return (NULL);
	}*/
	return (table);
}
