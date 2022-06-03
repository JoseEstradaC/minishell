#include "minishell.h"

void	ft_echo(int ac, char **args)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	if (ac > 1 && !ft_strncmp("-n", args[i], 3))
	{
		n = 1;
		i++;
	}
	while (i < ac)
	{
		printf("%s", args[i]);
		if (i < ac - 1)
			printf(" ");
	}
	if (!n)
		printf("\n");
}

//TODO change variables pwd and oldpwd
int	ft_cd(char *path)
{
	return (chdir(path));
}

void	ft_pwd(void)
{
	char	buffer[200];

	getcwd(buffer, 200);
	printf("%s\n", buffer);
}
