/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 06:26:19 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/06 06:26:20 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_command *cmd, char ***envp)
{
	int	built;

	built = 1;
	if (!ft_strncmp("echo", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_echo(cmd->number_of_arguments, cmd->args);
	else if (!ft_strncmp("cd", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_cd(cmd->args[1], envp);
	else if (!ft_strncmp("pwd", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_pwd();
	else if (!ft_strncmp("export", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_export(cmd->args[1], envp);
	else if (!ft_strncmp("unset", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_unset(cmd->args[1], envp);
	else if (!ft_strncmp("env", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_env(*envp);
	else
		built = 0;
	return (built);
}

int	input_delim(t_command_table *tab)
{
	int		fdpipe[2];
	char	*line;

	if (pipe(fdpipe) < 0)
		return (-1);
	line = readline("> ");
	while (ft_strncmp(line, tab->input_file, ft_strlen(line) + 1))
	{
		ft_putstr_fd(line, fdpipe[1]);
		ft_putstr_fd("\n", fdpipe[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fdpipe[1]);
	return (fdpipe[0]);
}
