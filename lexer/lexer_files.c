#include "../includes/minishell.h"

static	t_files	*ft_files_init(t_files *node)
{
	node = (t_files *) malloc(sizeof(t_files));
	node->error = 0;
	node->output = ft_strdup("");
	node->input = ft_strdup("");
	node->fd_input = 0;
	node->fd_output = 1;
	return (node);
}

static	t_files	*ft_files_init_input(t_files *node, char *arg)
{
	free(node->input);
	node->input = ft_strdup(arg);
	if (node->fd_input > 2)
		close(node->fd_input);
	node->fd_input = ft_open_input(node->input);
	if (node->fd_input == -1)
	{
		if (node->fd_output > 2)
			close(node->fd_output);
		node->error = 1;
	}
	return (node);
}

static	t_files	*ft_files_init_output(t_files *node, char *arg, int *i)
{
	free(node->output);
	node->output = ft_strdup(arg);
	if (node->fd_output > 2)
		close(node->fd_output);
	node->fd_output = ft_open_output(node->output);
	if (node->fd_output == -1)
	{
		if (node->fd_input > 2)
			close(node->fd_input);
		node->error = 2;
	}
	(*i)++;
	return (node);
}

static t_files	*ft_files_init_append(t_files *node, char *arg, int *i)
{
	free(node->output);
	node->output = ft_strdup(arg);
	if (node->fd_output > 2)
		close(node->fd_output);
	node->fd_output = ft_open_append(node->output);
	if (node->fd_output == -1)
	{
		if (node->fd_input > 2)
			close(node->fd_input);
		node->error = 2;
	}
	(*i)++;
	return (node);
}

t_files	*ft_new_files_node(char **arg, int i)
{
	t_files	*node;

	node = ft_files_init(NULL);
	ft_heredoc_check(node, arg);
	while (arg[++i] && node->error == 0)
	{
		if (ft_strcmp(arg[i], "<") == 0)
		{
			node = ft_files_init_input(node, arg[i + 1]);
			if (node->error == 1)
				return (node);
			i++;
		}
		else if (arg[i][0] == '>')
		{
			if (arg[i][1] && arg[i][1] == '>')
				node = ft_files_init_append(node, arg[i + 1], &i);
			else if (ft_strcmp(arg[i], ">") == 0)
				node = ft_files_init_output(node, arg[i + 1], &i);
			if (node->error == 2)
				return (node);
		}
	}
	return (node);
}
