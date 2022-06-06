/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:08:21 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/06 21:16:09 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**g_envp;

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
			continue ;
		if (ft_strncmp(table->commands[0]->args[0], "exit",
				ft_getmax(ft_strlen(line_read), 4)) == 0)
		{
			ret = ft_exit(table);
			if (ret >= 0)
			{
				ft_split_free(g_envp);
				clear_history();
				system("leaks -q minishell");
				return (ret);
			}
		}
		else
			execute(table);
		free_table(table);
	}
	clear_history();
	ft_split_free(g_envp);
	return (0);
}
