#include "../includes/minishell.h"

void	ft_cd_dir_check(t_state **state, char *dir)
{
	struct stat	file_info;

	if (stat(dir, &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
		{
			if (access(dir, X_OK) == 0)
			{
				if (chdir(dir) == 0)
					(*state)->error = 0;
				else
					ft_cd_chdir_error(dir, state);
			}
			else
				ft_cd_chdir_error(dir, state);
		}
		else
		{
			errno = ENOTDIR;
			ft_cd_chdir_error(dir, state);
		}
	}
	else
		ft_cd_error(dir, *state);
}

void	ft_cd_up_dir(t_state **state)
{
	char		cwd[1024];
	char		*dir;
	size_t		len;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		(*state)->error = 1;
		return ;
	}
	len = ft_strlen(ft_strrchr(cwd, '/'));
	dir = ft_substr(cwd, 0, ft_strlen(cwd) - len);
	if (ft_strlen(dir) == 0)
	{
		free(dir);
		dir = ft_strdup("/");
	}
	ft_cd_dir_check(state, dir);
	free(dir);
}

void	ft_cd_select_dir(t_state **state, char *type)
{
	t_env	*tmp_env;
	char	*dir;

	tmp_env = (*state)->env;
	if (ft_strcmp(type, "HOME") == 0)
		while (tmp_env && ft_strcmp(tmp_env->key, "HOME"))
			tmp_env = tmp_env->next;
	else if (ft_strcmp(type, "OLDPWD") == 0)
		while (tmp_env && ft_strcmp(tmp_env->key, "OLDPWD"))
			tmp_env = tmp_env->next;
	if (tmp_env == NULL)
		return (ft_notdefine_dir(type, *state));
	dir = tmp_env->value;
	ft_cd_dir_check(state, dir);
	if (ft_strcmp("OLDPWD", type) == 0)
	{
		write((*state)->cluster->files->fd_output, dir, ft_strlen(dir));
		write((*state)->cluster->files->fd_output, "\n", 1);
	}
}

void	ft_cd_execute_cmd(t_state **state, t_cluster *tmp)
{
	if (tmp->cmd == NULL || tmp->cmd[1] == NULL)
		ft_cd_select_dir(state, "HOME");
	else if (ft_strcmp(tmp->cmd[1], "-") == 0)
		ft_cd_select_dir(state, "OLDPWD");
	else if (ft_strcmp(tmp->cmd[1], "..") == 0)
		ft_cd_up_dir(state);
	else if (ft_strcmp(tmp->cmd[1], ".") != 0)
		ft_cd_dir_check(state, tmp->cmd[1]);
}

void	ft_cd_finalize(t_state **state, char *pwd)
{
	char	*oldpwd;
	char	current_pwd[1024];

	if ((*state)->error == 0)
	{
		if (getcwd(current_pwd, sizeof(current_pwd)) != NULL)
		{
			oldpwd = ft_strjoin("OLDPWD=", pwd);
			ft_add_exp(state, oldpwd);
			ft_add_env(state, oldpwd);
			free(oldpwd);
			oldpwd = ft_strjoin("PWD=", current_pwd);
			ft_add_exp(state, oldpwd);
			ft_add_env(state, oldpwd);
			free(oldpwd);
		}
	}
}
