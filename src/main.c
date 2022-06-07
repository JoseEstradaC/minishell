/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:08:21 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/07 08:14:32 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**g_envp;

void	handler(int signal)
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

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = handler;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

static int	call_lexer_parser(char ***lexer, t_command_table **table)
{
	char	*line_read;

	line_read = readline("🐚 ➡ ");
	if (!line_read)
	{
		free(line_read);
		exit (0);
	}
	if (line_read && *line_read && ft_str_isspace(line_read) == 0)
		add_history(line_read);
	*lexer = lexer_main(line_read);
	free(line_read);
	if (*lexer == NULL || ft_split_count(*lexer) == 0)
	{
		ft_split_free(*lexer);
		return (-1);
	}
	*table = parser(*lexer, &g_envp);
	if (!*table)
	{
		ft_split_free(*lexer);
		return (-1);
	}
	return (0);
}

static int	check_exit(t_command_table *table, char **lexer)
{
	int	ret;

	if (!ft_strncmp(table->commands[0]->args[0], "exit", 5))
	{
		ret = ft_exit(table);
		if (ret >= 0)
		{
			ft_split_free(lexer);
			ft_split_free(g_envp);
			clear_history();
			system("leaks -q minishell");
			return (ret);
		}
	}
	return (-1);
}

int	main(void)
{
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
		if (call_lexer_parser(&lexer, &table))
			continue ;
		ret = check_exit(table, lexer);
		if (ret >= 0)
			return (ret);
		else
			execute(table);
		ft_split_free(lexer);
		free_table(table);
	}
	clear_history();
	ft_split_free(g_envp);
	return (0);
}
