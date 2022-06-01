#include "minishell.h"

char	**join_tables(char **a, char **b);

char	**little_trick(char **args)
{
	char	*sh[20];

	sh[0] = "/bin/sh";
	sh[1] = "-c";
	sh[2] = NULL;
	return (join_tables(sh, args));
}

void	execute(t_command_table *tab)
{
	int		pid;
	int		i;
	char	**args;

	i = -1;
	while (++i < tab->number_of_commands)
	{
		pid = fork();
		if (pid == 0)
		{
			args = little_trick(tab->commands[i]->args);
for (int j=0; args[j]; j++)
	puts(args[j]);
			execve(args[0], args, NULL);
			perror("execvp");
			exit(-1);
		}
		else if (pid < 0)
		{
			perror("fork");
			return ;
		}
	}
	wait(NULL);
}
