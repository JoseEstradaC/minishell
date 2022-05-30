/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:08:21 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/30 19:22:32 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_terminal(void)
{
	int				index;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	index = 0;
	while (w.ws_row != index)
	{
		printf("\n");
		index++;
	}
}

void	print_terminal(void)
{
	int				index;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	index = 0;
	while (w.ws_col != index)
	{
		printf("─");
		index++;
	}
	printf("\n");
	printf("\e[1;35m/asd/asd\n\e[0;37m");
}

int	main(void)
{
	char			*line_read;
	char			**lexer;
	int				index;
	t_command_table	*table;

	index = 0;
	clear_terminal();
	while (1)
	{
		print_terminal();
		line_read = readline("🐚 ➡ ");
		if (ft_strncmp(line_read, "exit", ft_getmax(ft_strlen(line_read),
					4)) == 0)
		{
			free(line_read);
			break ;
		}
		if (line_read && *line_read)
			add_history(line_read);
		lexer = lexer_main(line_read);
		free(line_read);
		if (!lexer)
			ft_putstr_fd("An error has occurred durring lexer executing", 2);
		if (ft_split_count(lexer) == 0)
		{
			ft_split_free(lexer);
			continue ;
		}
		table = parser(lexer);
		free_table(table);
		ft_split_free(lexer);
		system("leaks -q minishell");
	}
	return (0);
}
