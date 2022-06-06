/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:31:24 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/06 11:39:18 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_pipes
{
	int	tmpin;
	int	tmpout;
	int	fdin;
	int	fdout;
}		t_pipes;

int	exec_builtin(t_command *cmd, char ***envp);
int	input_delim(t_command_table *tab);

static void	execute_command(t_command *cmd, char ***envp)
{
	int		pid;
	int		wstatus;
	char	*n_status;

	if (exec_builtin(cmd, envp))
	{
		set_env_value("?", "0", envp);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(get_path(cmd->args[0]), cmd->args, NULL);
		perror("execvp");
		exit(-1);
	}
	else if (pid < 0)
	{
		perror("fork");
		return ;
	}
	wait(&wstatus);
	n_status = ft_itoa(wstatus);
	set_env_value("?", n_status, envp);
}

static int	redirect_io(t_command_table *tab, int i, t_pipes *pipes)
{
	int	fdpipe[2];

	if (i == tab->number_of_commands - 1)
	{
		if (tab->out_file && ft_strlen(tab->out_type) == 1)
			pipes->fdout = open(tab->out_file,
					O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (tab->out_file && ft_strlen(tab->out_type) == 2)
			pipes->fdout = open(tab->out_file, O_WRONLY | O_APPEND);
		else
			pipes->fdout = dup(pipes->tmpout);
		if (pipes->fdout < 0)
		{
			perror(tab->out_file);
			return (-1);
		}
	}
	else
	{
		if (pipe(fdpipe) < 0)
			return (-1);
		pipes->fdout = fdpipe[1];
		pipes->fdin = fdpipe[0];
	}
	return (0);
}

static int	pipe_commands(t_command_table *tab, t_pipes *pipes)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < tab->number_of_commands)
	{
		dup2(pipes->fdin, 0);
		close(pipes->fdin);
		ret = redirect_io(tab, i, pipes);
		if (ret < 0)
			return (-1);
		dup2(pipes->fdout, 1);
		close(pipes->fdout);
		execute_command(tab->commands[i], tab->env);
	}
	return (0);
}

int	execute(t_command_table *tab)
{
	t_pipes	pipes;
	int		ret;

	pipes.tmpin = dup(0);
	pipes.tmpout = dup(1);
	if (tab->input_file && ft_strlen(tab->input_type) == 1)
		pipes.fdin = open(tab->input_file, O_RDONLY);
	else if (tab->input_file && ft_strlen(tab->input_type) == 2)
		pipes.fdin = input_delim(tab);
	else
		pipes.fdin = dup(pipes.tmpin);
	if (pipes.fdin < 0)
	{
		perror(tab->input_file);
		close(pipes.tmpin);
		close(pipes.tmpout);
		return (-1);
	}
	ret = 0;
	ret = pipe_commands(tab, &pipes);
	dup2(pipes.tmpin, 0);
	dup2(pipes.tmpout, 1);
	close(pipes.tmpin);
	close(pipes.tmpout);
	return (ret);
}
