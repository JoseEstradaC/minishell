/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:43:52 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/28 17:44:47 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_split(char *line)
{
	char	**ret;

	ret = NULL;
	line = NULL;
}

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

void	lexer_main(char *line)
{
	char	**asd;

	if (lexer_is_quote_pair(line))
		ft_putstr_fd("Error, quotes not closed correctly\n", 2);
	asd = split_command(line, ' ');
	while (*asd)
	{
		printf("%s\n", *asd);
		asd++;
	}
}
