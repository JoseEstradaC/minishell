/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:08:21 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/06 05:45:10 by jarredon         ###   ########.fr       */
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
		printf("─");
		index++;
	}
	printf("\n");
	getcwd(working_dir, 150);
	printf("\e[1;35m%s\n\e[0;37m", working_dir);
}

static void	handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	set_handlers(void)
{
	struct sigaction	act;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	main(void)
{
	char			*line_read;
	char			**lexer;
	t_command_table	*table;
	extern char		**environ;
	char			**envp;

	set_handlers();
	clear_terminal();
	envp = join_split(environ, NULL);
	while (1)
	{
		print_terminal();
		line_read = readline("🐚 ➡ ");
		// line_read == NULL -> Ctrl-D (EOF)
		if (!line_read || ft_strncmp(line_read, "exit",
				ft_getmax(ft_strlen(line_read), 4)) == 0)
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
		table = parser(lexer, &envp);
		if (!table)
		{
			ft_split_free(lexer);
			system("leaks -q minishell");
			continue ;
		}
		execute(table);
		ft_split_free(lexer);
		free_table(table);
		system("leaks -q minishell");
	}
	ft_split_free(envp);
	system("leaks -q minishell");
	return (0);
}
