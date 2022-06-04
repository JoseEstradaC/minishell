/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:18:33 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/04 17:59:58 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command		*get_command(t_command_table **table, char ***lexer);
char	*fill_table_with_redirects(t_command_table *table,
								char ***lexer);

void	set_vars_fill_table(int *first, char **file, char *lexer)
{
	*first = 1;
	if (token_is_redirrect(lexer))
		*first = 2;
	*file = NULL;
}

t_command_table	**fill_table(t_command_table **table, char ***lexer)
{
	int		first;
	char	*file;

	set_vars_fill_table(&first, &file, **lexer);
	while (first || (**lexer && token_is_divider(**lexer)) || file)
	{
		if (token_is_divider(**lexer) && token_is_divider(*(*lexer + 1)))
			return (NULL);
		if (token_is_pipe(**lexer) || first == 1 || file)
		{
			file = NULL;
			if (!get_command(table, lexer))
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

t_command_table	*parser(char **lexer, char ***env)
{
	t_command_table	*table;

	if (ft_split_count(lexer) < 1)
		return (NULL);
	table = (t_command_table *)ft_calloc(1, sizeof(t_command_table));
	if (!table)
		return (NULL);
	table->input_file = NULL;
	table->input_type = NULL;
	table->out_file = NULL;
	table->out_type = NULL;
	table->env = env;
	if (!fill_table(&table, &lexer))
	{
		ft_putstr_fd("Error parsing command\n", 2);
		free_table(table);
		return (NULL);
	}
	return (table);
}
