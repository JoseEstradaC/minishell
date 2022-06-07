/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:08:21 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/07 14:29:14 by jarredon         ###   ########.fr       */
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

static int	call_lexer_parser(char ***lexer, t_command_table **table)
{
	char	*line_read;

	print_terminal();
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

static void	handle_args(int ac, char **av)
{
	char			**lexer;
	t_command_table	*table;

	if (strncmp(av[1], "-c", 3))
	{
		printf("%s: cannot execute binary file\n", av[1]);
		exit(126);
	}
	if (ac == 2)
		exit(2);
	lexer = lexer_main(av[2]);
	if (lexer == NULL || ft_split_count(lexer) == 0)
	{
		ft_split_free(lexer);
		exit(-1);
	}
	table = parser(lexer, &g_envp);
	if (!table)
		exit(-1);
	execute(table);
	ft_split_free(lexer);
	free_table(table);
	ft_split_free(g_envp);
	exit(0);
}

int	main(int ac, char **av, char **envp)
{
	char			**lexer;
	t_command_table	*table;
	int				ret;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	g_envp = join_split(envp, NULL);
	if (ac > 1)
		handle_args(ac, av);
	clear_terminal();
	while (1)
	{
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
