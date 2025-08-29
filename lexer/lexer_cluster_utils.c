#include "../includes/minishell.h"

static char	**ft_clean_cmd(char **str)
{
	int		i;
	int		j;
	char	**dest;

	dest = malloc(sizeof(char *) * (ft_double_str_len(str) +1));
	if (!dest)
		return (NULL);
	dest[ft_double_str_len(str)] = NULL;
	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((ft_strchr(str[i], '>') || ft_strchr(str[i], '<'))
			&& (ft_strchr(str[i], '"') || ft_strchr(str[i], '\'')))
			dest[j++] = ft_substr(str[i], 1, ft_strlen(str[i]) - 2);
		else
			dest[j++] = ft_strdup(str[i]);
	}
	ft_free_double_str(str);
	return (dest);
}

static t_cluster	*ft_init_cluster(void)
{
	t_cluster	*new;

	new = (t_cluster *)malloc(sizeof(t_cluster));
	if (!new)
		return (NULL);
	new->pid = -1;
	new->next = NULL;
	return (new);
}

static void	ft_setup_heredoc(t_cluster *new)
{
	if (new->files->heredoc && new->files->heredoc[0] != '\0' 
		&& new->files->fd_input < 2)
		new->files->fd_input = -2;
}

static t_cluster	*ft_handle_errors(t_cluster *new)
{
	if (new->files->error == 2)
		return (ft_file_open_error(new, new->files->output));
	if (new->files->error == 1)
		return (ft_file_open_error(new, new->files->input));
	if (new->files->error == 3)
	{
		ft_cluster_free(new);
		return (NULL);
	}
	return (new);
}

t_cluster	*ft_new_cluster_node(char **arg)
{
	t_cluster	*new;

	new = ft_init_cluster();
	if (!new)
		return (NULL);
	new->cmd = ft_clean_cmd(ft_fill_cmd(arg));
	new->files = ft_new_files_node(arg, -1);
	if (!new->cmd || !new->files)
	{
		ft_cluster_free(new);
		return (NULL);
	}
	ft_setup_heredoc(new);
	return (ft_handle_errors(new));
}