/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:43:52 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/06 13:56:30 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_command(char const *s, char c);

int	lexer_is_quote_pair(char *line)
{
	char	type;

	type = '\0';
	while (*line)
	{
		if (type == *line)
			type = '\0';
		else if (ft_isset(*line, "\"\'") && type == '\0')
			type = *line;
		line++;
	}
	if (type)
		return (1);
	return (0);
}

char	**lexer_main(char *line)
{
	char	**split;

	if (lexer_is_quote_pair(line))
	{
		ft_putstr_fd("Error, quotes not closed correctly\n", 2);
		return (NULL);
	}
	split = split_command(line, ' ');
	if (!split)
		return (NULL);
	return (split);
}
