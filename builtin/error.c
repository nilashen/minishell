#include "../includes/minishell.h"

void	ft_notdefine_dir(char *s, t_state *state)
{
	state->error = 1;
	write(2, "cd: ", 4);
	write(2, s, ft_strlen(s));
	write(2, " ", 1);
	write(2, "not set\n", ft_strlen("not set\n"));
}

void	ft_cd_error(char *dir, t_state *state)
{
	state->error = 1;
	write(2, "cd: ", ft_strlen("cd: "));
	perror(dir);
}

void	ft_cd_chdir_error(char *dir, t_state **state)
{
	write(2, "cd: ", 4);
	write(2, dir, ft_strlen(dir));
	if (errno == ENOTDIR)
		write(2, ": Not a directory\n", 18);
	else if (errno == EACCES)
		write(2, ": Permission denied\n", 20);
	else if (errno == ENOENT)
		write(2, ": No such file or directory\n", 28);
	else
		write(2, ": Operation not permitted\n", 26);
	(*state)->error = 1;
}

void	ft_key_error(char *s, char *cmd, t_state *state)
{
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		write (2, "export: ", ft_strlen("export: "));
	else
		write (2, "unset: ", ft_strlen("unset: "));
	write (2, s, ft_strlen(s));
	write (2, ": not a valid identifier\n",
		ft_strlen(": not a valid identifier\n"));
	state->error = 1;
}