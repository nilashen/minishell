#include "../includes/minishell.h"

void	ft_cd(t_state **state)
{
	t_cluster	*tmp;
	char		pwd[1024];
	int			argc;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("getcwd");
		(*state)->error = 1;
		return ;
	}
	tmp = (*state)->cluster;
	argc = 0;
	while (tmp->cmd[argc])
		argc++;
	if (argc > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		(*state)->error = 1;
		return ;
	}
	ft_cd_execute_cmd(state, tmp);
	ft_cd_finalize(state, pwd);
}
