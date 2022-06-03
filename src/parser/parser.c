/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:18:33 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/03 13:37:06 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command		*get_command(t_command_table **table, char ***lexer);
char	*fill_table_with_redirects(t_command_table *table,
								char ***lexer);

t_command_table	**fill_table(t_command_table **table, char ***lexer)
{
	int			first;
	t_command	*command;
	char		*file;

	first = 1;
	if (token_is_redirrect(**lexer))
		first = 2;
	file = NULL;
	while (first || (**lexer && token_is_divider(**lexer)) || file)
	{
		if (token_is_pipe(**lexer) || first == 1 || file)
		{
			command = get_command(table, lexer);
			file = NULL;
			if (!command)
				return (NULL);
		}
		else if (token_is_redirrect(**lexer) || first == 2)
		{
			file = fill_table_with_redirects(*table, lexer);
			if (!file)
				return (NULL);
		}
		first = 0;
		if (!(**lexer))
			break ;
	}
	return (table);
}

t_command_table	*parser(char **lexer)
{
	t_command_table	*table;

	if (ft_split_count(lexer) < 1)
		return (NULL);
	table = (t_command_table *)ft_calloc(1, sizeof(t_command_table));
	table->input_file = NULL;
	table->input_type = NULL;
	table->out_file = NULL;
	table->out_type = NULL;
	if (!table)
		return (NULL);
	if (!fill_table(&table, &lexer))
	{
		free_table(table);
		return (NULL);
	}
	/*
	if (*lexer && ft_strlen(*lexer) == 1 && **lexer == '|')
	{
		ft_putstr_fd("Error pipe not properly closed\n", 2);
		free_table(table);
		return (NULL);
	}*/
	return (table);
}
