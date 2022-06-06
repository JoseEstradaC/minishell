/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:08:21 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/06 20:19:20 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**g_envp;

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

	//printf("\n");
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	index = 0;
	while (w.ws_col != index)
	{
		write(1,"─", 3);
		index++;
	}
	write(1, "\n", 1);
	getcwd(working_dir, 150);
	ft_putstr_fd("\e[1;35m", 1);
	ft_putstr_fd(working_dir, 1);
	ft_putstr_fd("\n\e[0;37m", 1);
}

static void	handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		print_terminal();
		rl_redisplay();
		set_env_value("?", "1", &g_envp);
		set_env_value("_", "1", &g_envp);
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

	set_handlers();
	clear_terminal();
	g_envp = join_split(environ, NULL);
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
			continue ;
		if (ft_split_count(lexer) == 0)
		{
			ft_split_free(lexer);
			continue ;
		}
		table = parser(lexer, &g_envp);
		if (!table)
		{
			ft_split_free(lexer);
			/*system("leaks -q minishell");*/
			continue ;
		}
		execute(table);
		ft_split_free(lexer);
		free_table(table);
		/*system("leaks -q minishell");*/
	}
	ft_split_free(g_envp);
	system("leaks -q minishell");
	return (0);
}
