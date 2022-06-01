#include <stdlib.h>
#include "minishell.h"

int	len_table(char **table)
{
	int	len;

	len = 0;
	while (table[len])
		len++;
	return (len);
}

// Join a + b (pointers to a null-terminated array of strings)
char	**join_tables(char **a, char **b)
{
	int		size;
	char	**ret;
	int		i;
	int		j;

	size = len_table(a) + len_table(b) + 1;
	ret = (char **)malloc(size * sizeof(char *));
	i = -1;
	while (a[++i])
		ret[i] = a[i];
	j = 0;
	while (b[j])
		ret[i++] = b[j++];
	ret[i] = NULL;

/*printf("i: %d, j: %d, b[1]: %s\n", i, j, b[1]);*/
/*for (int j=0; j < i; j++)*/
	/*printf("ret[%d]: %s\n", j, ret[j]);*/

	return (ret);
}
