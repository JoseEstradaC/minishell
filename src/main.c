/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:08:21 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/06 20:48:32 by jarredon         ###   ########.fr       */
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
	int				ret;

	set_handlers();
	clear_terminal();
	g_envp = join_split(environ, NULL);
	while (1)
	{
		print_terminal();
		line_read = readline("🐚 ➡ ");
		if (!line_read)
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
		ft_split_free(lexer);
		if (!table)
		{
			system("leaks -q minishell");
			continue ;
		}
		if (ft_strncmp(table->commands[0]->args[0], "exit",
				ft_getmax(ft_strlen(line_read), 4)) == 0)
		{
			if (table->commands[0]->number_of_arguments > 2)
				ft_putstr_fd("exit: too many arguments\n", 2);
			else if (table->commands[0]->args[1] == NULL)
			{
				free_table(table);
				ft_split_free(g_envp);
				return (0);
			}
			else if (!ft_str_is_numeric(table->commands[0]->args[1]))
				ft_putstr_fd("exit: numeric argument required\n", 2);
			else
			{
				ret = ft_atoi(table->commands[0]->args[1]);
				free_table(table);
				ft_split_free(g_envp);
				return (ret);
			}
		}
		else
			execute(table);
		free_table(table);
		system("leaks -q minishell");
	}
	ft_split_free(g_envp);
	system("leaks -q minishell");
	return (0);
}
