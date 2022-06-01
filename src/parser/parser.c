/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:18:33 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/01 19:22:14 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*fill_table_with_commands(t_command_table **table,
									char ***lexer);
char	*fill_table_with_redirects(t_command_table *table,
								char ***lexer);

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
	/*free(table->input_file);
	free(table->input_type);
	free(table->out_file);
	free(table->out_type);*/
	free(table->commands);
	free(table);
}

t_command_table	*parser(char **lexer)
{
	t_command_table	*table;

	if (ft_split_count(lexer) < 1)
		return (NULL);
	table = (t_command_table *)ft_calloc(1, sizeof(t_command_table));
	if (!table)
		return (NULL);
	if (!fill_table_with_commands(&table, &lexer))
	{
		free_table(table);
		return (NULL);
	}
	if (*lexer && ft_strlen(*lexer) == 1 && **lexer == '|')
	{
		ft_putstr_fd("Error pipe not properly closed\n", 2);
		free_table(table);
		return (NULL);
	}
	if (!fill_table_with_redirects(table, &lexer))
		return (NULL);
	return (table);
}
