/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:15:03 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/06 21:15:05 by jarredon         ###   ########.fr       */
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
	char			working_dir[150];

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	index = 0;
	while (w.ws_col != index)
	{
		write(1, "─", 3);
		index++;
	}
	write(1, "\n", 1);
	getcwd(working_dir, 150);
	ft_putstr_fd("\e[1;35m", 1);
	ft_putstr_fd(working_dir, 1);
	ft_putstr_fd("\n\e[0;37m", 1);
}
