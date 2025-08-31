#include "../includes/minishell.h"

int	ft_handle_empty_command(t_cluster *cluster)
{
	if (!cluster || !cluster->cmd || !cluster->cmd[0])
		return (1);
	if (cluster->cmd[0][0] == '\0')
		return (1);
	return (0);
}
