#include "../includes/minishell.h"

static void	ft_heradoc_helper(char *line, t_files *node)
{
	if (line == NULL)
	{
		close(node->fd_heredoc[1]);
		exit(0);
	}
	if (ft_strcmp(line, node->input) == 0)
	{
		free(line);
		exit(0);
	}
	write(node->fd_heredoc[1], line, ft_strlen(line));
	write(node->fd_heredoc[1], "\n", 1);
	free(line);
}

static	int	ft_parent_heredoc(t_files *node, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	close(node->fd_heredoc[1]);
	if (status != 0)
		return (3);
	else
		return (0);
}

static int	ft_heredoc(t_files *node)
{
	int		pid;
	char	*line;
	int		status;

	status = 0;
	pipe(node->fd_heredoc);
	pid = fork();
	
	if (pid == 0)
	{
		g_sig_status = IN_HERADOC;
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline(">");
			ft_heradoc_helper(line, node);
		}
	}
	else
	{
		g_sig_status = IN_PARENT;
		status = ft_parent_heredoc(node, pid);
		g_sig_status = 0;
	}
	return (status);
}

void	ft_heredoc_check(t_files *node, char **arg)
{
	int		i;

	i = 0;
	node->heredoc = ft_strdup("");
	while (arg[i])
	{
		if (ft_strcmp(arg[i], "<<") == 0)
		{
			free(node->input);
			node->input = ft_strdup(arg[i + 1]);
			node->error = ft_heredoc(node);
			if (node->error == 3)
				return ;
			free(node->heredoc);
			node->heredoc = get_next_line(node->fd_heredoc[0]);
			close(node->fd_heredoc[0]);
			i++;
		}
		i++;
	}
	if (node->heredoc == NULL)
		node->heredoc = ft_strdup(" ");
}
