#include "minishell.h"

int	ft_export(char *entry, t_env **env)
{
	t_env	*new_node;
	t_env	*ptr;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (-1);
	new_node->entry = ft_strdup(entry);
	new_node->next = NULL;
	if (*env == NULL)
	{
		*env = new_node;
		return (0);
	}
	ptr = *env;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new_node;
	return (0);
}

void	ft_unset(char *key, t_env **env)
{
	int		len_key;
	t_env	*prev;
	t_env	*p;

	len_key = ft_strlen(key);
	prev = *env;
	if (*env && !ft_strncmp((*env)->entry, key, len_key)
		&& (*env)->entry[len_key] == '=')
	{
		*env = (*env)->next;
		free(prev->entry);
		free(prev);
	}
	p = (*env)->next;
	while (p)
	{
		if (!ft_strncmp(p->entry, key, len_key) && p->entry[len_key] == '=')
		{
			prev->next = p->next;
			free(p->entry);
			free(p);
		}
		prev = p;
		p = p->next;
	}
}

void	ft_env(t_env *env)
{
	while (env)
	{
		printf("%s\n", env->entry);
		env = env->next;
	}
}
