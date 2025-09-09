#include "../includes/minishell.h"

static void	ft_heredoc_helper(char *line, t_files *node)
{
    if (line == NULL)
    {
        close(node->fd_heredoc[1]);
        exit(0);
    }
    if (ft_strcmp(line, node->input) == 0)
    {
        free(line);
        close(node->fd_heredoc[1]);
        exit(0);
    }
    write(node->fd_heredoc[1], line, ft_strlen(line));
    write(node->fd_heredoc[1], "\n", 1);
    free(line);
}

static int	ft_parent_heredoc(t_files *node, int pid)
{
    int	status;

    waitpid(pid, &status, 0);
    close(node->fd_heredoc[1]);
    if (WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status);
        if (sig == SIGINT)
            return (130);
        else if (sig == SIGQUIT)
            return (131);
        else
            return (128 + sig);
    }
    else if (WIFEXITED(status))
    {
        return (WEXITSTATUS(status));
    }
    return (0);
}

static int	ft_heredoc(t_files *node)
{
    int		pid;
    char	*line;
    int		status;

    if (pipe(node->fd_heredoc) == -1)
    {
        perror("pipe");
        return (3);
    }
    pid = fork();
    if (pid == 0)
    {
        close(node->fd_heredoc[0]);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_IGN);
        while (1)
        {
            line = readline("> ");
            ft_heredoc_helper(line, node);
        }
        exit(1);
    }
    else if (pid > 0)
    {
        close(node->fd_heredoc[1]);
        status = ft_parent_heredoc(node, pid);
        if (status != 0)
            close(node->fd_heredoc[0]);
        return (status);
    }
    else
    {
        perror("fork");
        close(node->fd_heredoc[0]);
        close(node->fd_heredoc[1]);
        return (3);
    }
}

static char	*ft_read_all_heredoc(int fd)
{
    char	*result;
    char	*line;
    char	*temp;

    result = ft_strdup("");
    if (!result)
        return (NULL);
    while ((line = get_next_line(fd)) != NULL)
    {
        temp = result;
        result = ft_strjoin(temp, line);
        free(temp);
        free(line);
        if (!result)
            return (NULL);
    }
    return (result);
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
            if (node->error == 130 || node->error == 3)
            {
                if (node->error == 130)
                {
                    free(node->heredoc);
                    node->heredoc = ft_strdup("");
                }
                return;
            }
            if (node->error == 0)
            {
                free(node->heredoc);
                node->heredoc = ft_read_all_heredoc(node->fd_heredoc[0]);
                if (!node->heredoc)
                    node->heredoc = ft_strdup("");
            }
            close(node->fd_heredoc[0]);
            i++;
        }
        i++;
    }
    if (node->heredoc == NULL)
        node->heredoc = ft_strdup("");
}
