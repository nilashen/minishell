#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

static void	ft_cluster_addback(t_cluster **cluster_node, t_cluster *new)
{
	t_cluster	*tmp;

	if (!cluster_node || !new)
		return ;
	if (!*cluster_node)
	{
		*cluster_node = new;
		return ;
	}
	tmp = *cluster_node;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp ->next = new;
}

void	ft_cluster(t_state *state)
{
	t_cluster	*new;
	char		***thrd_arg;
	t_cluster	*tmp_node;
	int			i;

	i = 0;
	tmp_node = NULL;
	thrd_arg = state->clean_thrd_argv;
	while (thrd_arg[i])
	{
		new = ft_new_cluster_node(thrd_arg[i]);
		if (new == NULL)
			state->error = 1;
		ft_cluster_addback(&tmp_node, new);
		i++;
	}
	state->cluster = tmp_node;
}
