
/* ========== PARSER.C ========== */
#include "minishell.h"

int	count_pipes_in_input(char *input)
{
	int	count;
	int	i;
	int	in_quotes;
	char	quote_char;

	count = 0;
	i = 0;
	in_quotes = 0;
	while (input[i])
	{
		if (!in_quotes && (input[i] == '\'' || input[i] == '"'))
		{
			in_quotes = 1;
			quote_char = input[i];
		}
		else if (in_quotes && input[i] == quote_char)
			in_quotes = 0;
		else if (!in_quotes && input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

char	**split_pipes(char *input)
{
	char	**pipes;
	int		count;
	int		i;
	int		start;
	int		j;

	count = count_pipes_in_input(input) + 1;
	pipes = malloc(sizeof(char *) * (count + 1));
	if (!pipes)
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			pipes[j] = ft_substr(input, start, i - start);
			j++;
			start = i + 1;
		}
		i++;
	}
	pipes[j] = ft_substr(input, start, i - start);
	pipes[j + 1] = NULL;
	return (pipes);
}

t_cmd	*parse_input(char *input, t_shell *shell)
{
	char	**pipe_cmds;
	t_cmd	*first_cmd;
	t_cmd	*current_cmd;
	t_cmd	*new_cmd;
	int		i;

	if (!input || !*input)
		return (NULL);
	pipe_cmds = split_pipes(input);
	if (!pipe_cmds)
		return (NULL);
	shell->cmd_count = ft_arrlen(pipe_cmds);
	first_cmd = NULL;
	current_cmd = NULL;
	i = 0;
	while (pipe_cmds[i])
	{
		new_cmd = parse_command(pipe_cmds[i], shell);
		if (!new_cmd)
		{
			free_commands(first_cmd);
			ft_arrfree(pipe_cmds);
			return (NULL);
		}
		if (!first_cmd)
		{
			first_cmd = new_cmd;
			current_cmd = new_cmd;
		}
		else
		{
			current_cmd->next = new_cmd;
			current_cmd = new_cmd;
		}
		i++;
	}
	ft_arrfree(pipe_cmds);
	return (first_cmd);
}

/* ========== PARSE_COMMAND.C ========== */
#include "minishell.h"

static int	count_args(char **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<") != 0 && ft_strcmp(tokens[i], ">") != 0 &&
			ft_strcmp(tokens[i], ">>") != 0 && ft_strcmp(tokens[i], "<<") != 0)
		{
			if (i == 0 || (ft_strcmp(tokens[i - 1], "<") != 0 &&
				ft_strcmp(tokens[i - 1], ">") != 0 &&
				ft_strcmp(tokens[i - 1], ">>") != 0 &&
				ft_strcmp(tokens[i - 1], "<<") != 0))
				count++;
		}
		i++;
	}
	return (count);
}

static char	**extract_args(char **tokens)
{
	char	**args;
	int		count;
	int		i;
	int		j;

	count = count_args(tokens);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<") != 0 && ft_strcmp(tokens[i], ">") != 0 &&
			ft_strcmp(tokens[i], ">>") != 0 && ft_strcmp(tokens[i], "<<") != 0)
		{
			if (i == 0 || (ft_strcmp(tokens[i - 1], "<") != 0 &&
				ft_strcmp(tokens[i - 1], ">") != 0 &&
				ft_strcmp(tokens[i - 1], ">>") != 0 &&
				ft_strcmp(tokens[i - 1], "<<") != 0))
			{
				args[j] = ft_strdup(tokens[i]);
				j++;
			}
		}
		i++;
	}
	args[j] = NULL;
	return (args);
}

t_cmd	*parse_command(char *cmd_str, t_shell *shell)
{
	t_cmd	*cmd;
	char	**tokens;
	char	*expanded;

	if (!cmd_str)
		return (NULL);
	expanded = expand_variables(cmd_str, shell);
	if (!expanded)
		return (NULL);
	tokens = tokenize_command(expanded);
	free(expanded);
	if (!tokens)
		return (NULL);
	if (!handle_quotes(tokens))
	{
		ft_arrfree(tokens);
		return (NULL);
	}
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		ft_arrfree(tokens);
		return (NULL);
	}
	cmd->args = extract_args(tokens);
	cmd->redirs = parse_redirections(&tokens);
	cmd->pipe_in = -1;
	cmd->pipe_out = -1;
	cmd->pid = -1;
	cmd->next = NULL;
	ft_arrfree(tokens);
	return (cmd);
}

/* ========== TOKENIZER.C ========== */
#include "minishell.h"

static int	count_tokens(char *cmd)
{
	int	count;
	int	i;
	int	in_quotes;
	char	quote_char;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		if (cmd[i])
		{
			count++;
			in_quotes = 0;
			while (cmd[i] && (!ft_isspace(cmd[i]) || in_quotes))
			{
				if (!in_quotes && (cmd[i] == '\'' || cmd[i] == '"'))
				{
					in_quotes = 1;
					quote_char = cmd[i];
				}
				else if (in_quotes && cmd[i] == quote_char)
					in_quotes = 0;
				i++;
			}
		}
	}
	return (count);
}

static char	*extract_token(char *cmd, int *pos)
{
	int		start;
	int		in_quotes;
	char	quote_char;

	start = *pos;
	in_quotes = 0;
	while (cmd[*pos] && (!ft_isspace(cmd[*pos]) || in_quotes))
	{
		if (!in_quotes && (cmd[*pos] == '\'' || cmd[*pos] == '"'))
		{
			in_quotes = 1;
			quote_char = cmd[*pos];
		}
		else if (in_quotes && cmd[*pos] == quote_char)
			in_quotes = 0;
		(*pos)++;
	}
	return (ft_substr(cmd, start, *pos - start));
}

char	**tokenize_command(char *cmd)
{
	char	**tokens;
	int		count;
	int		i;
	int		pos;

	if (!cmd || !*cmd)
		return (NULL);
	count = count_tokens(cmd);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	pos = 0;
	while (cmd[pos] && i < count)
	{
		while (cmd[pos] && ft_isspace(cmd[pos]))
			pos++;
		if (cmd[pos])
		{
			tokens[i] = extract_token(cmd, &pos);
			i++;
		}
	}
	tokens[i] = NULL;
	return (tokens);
}

int	handle_quotes(char **tokens)
{
	int		i;
	char	*new_token;
	int		len;
	int		j;
	int		k;

	i = 0;
	while (tokens[i])
	{
		len = ft_strlen(tokens[i]);
		if (len >= 2 && ((tokens[i][0] == '\'' && tokens[i][len - 1] == '\'') ||
			(tokens[i][0] == '"' && tokens[i][len - 1] == '"')))
		{
			new_token = malloc(len - 1);
			if (!new_token)
				return (0);
			j = 1;
			k = 0;
			while (j < len - 1)
				new_token[k++] = tokens[i][j++];
			new_token[k] = '\0';
			free(tokens[i]);
			tokens[i] = new_token;
		}
		i++;
	}
	return (1);
}

/* ========== EXPAND.C ========== */
#include "minishell.h"

static char	*get_var_name(char *str, int *pos)
{
	int	start;
	int	len;

	if (str[*pos] != '$')
		return (NULL);
	(*pos)++;
	if (str[*pos] == '?')
	{
		(*pos)++;
		return (ft_strdup("?"));
	}
	if (!ft_isalpha(str[*pos]) && str[*pos] != '_')
	{
		(*pos)--;
		return (NULL);
	}
	start = *pos;
	len = 0;
	while (str[*pos] && (ft_isalnum(str[*pos]) || str[*pos] == '_'))
	{
		(*pos)++;
		len++;
	}
	if (len == 0)
		return (NULL);
	return (ft_substr(str, start, len));
}

static char	*expand_single_var(char *var_name, t_shell *shell)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->exit_code));
	value = env_get(shell->env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*expand_variables(char *str, t_shell *shell)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*temp;
	int		pos;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '$' && str[pos + 1])
		{
			var_name = get_var_name(str, &pos);
			if (var_name)
			{
				var_value = expand_single_var(var_name, shell);
				temp = ft_strjoin(result, var_value);
				free(result);
				free(var_name);
				free(var_value);
				result = temp;
			}
			else
			{
				temp = malloc(ft_strlen(result) + 2);
				ft_strcpy(temp, result);
				temp[ft_strlen(result)] = str[pos];
				temp[ft_strlen(result) + 1] = '\0';
				free(result);
				result = temp;
				pos++;
			}
		}
		else
		{
			temp = malloc(ft_strlen(result) + 2);
			ft_strcpy(temp, result);
			temp[ft_strlen(result)] = str[pos];
			temp[ft_strlen(result) + 1] = '\0';
			free(result);
			result = temp;
			pos++;
		}
	}
	return (result);
}

/* ========== REDIRECTIONS.C ========== */
#include "minishell.h"

static t_redir	*new_redir(int type, char *file, char *delimiter)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = file ? ft_strdup(file) : NULL;
	redir->delimiter = delimiter ? ft_strdup(delimiter) : NULL;
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

static void	add_redir(t_redir **head, t_redir *new)
{
	t_redir	*current;

	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

t_redir	*parse_redirections(char ***tokens)
{
	t_redir	*redirs;
	int		i;
	int		type;

	redirs = NULL;
	i = 0;
	while ((*tokens)[i])
	{
		type = 0;
		if (ft_strcmp((*tokens)[i], "<") == 0)
			type = REDIR_IN;
		else if (ft_strcmp((*tokens)[i], ">") == 0)
			type = REDIR_OUT;
		else if (ft_strcmp((*tokens)[i], ">>") == 0)
			type = REDIR_APPEND;
		else if (ft_strcmp((*tokens)[i], "<<") == 0)
			type = REDIR_HEREDOC;
		if (type && (*tokens)[i + 1])
		{
			if (type == REDIR_HEREDOC)
				add_redir(&redirs, new_redir(type, NULL, (*tokens)[i + 1]));
			else
				add_redir(&redirs, new_redir(type, (*tokens)[i + 1], NULL));
			i += 2;
		}
		else
			i++;
	}
	return (redirs);
}

int	handle_heredoc(t_redir *redir)
{
	int		pipefd[2];
	char	*line;
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, redir->delimiter) == 0)
			{
				if (line)
					free(line);
				break ;
			}
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	return (pipefd[0]);
}

int	handle_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1)
			{
				perror(redir->file);
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(redir->file);
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror(redir->file);
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			fd = handle_heredoc(redir);
			if (fd == -1)
				return (-1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}

/* ========== EXECUTOR.C ========== */
#include "minishell.h"

void	setup_pipes(t_shell *shell)
{
	int	i;

	if (shell->cmd_count <= 1)
		return ;
	shell->pipes = malloc(sizeof(int *) * (shell->cmd_count - 1));
	i = 0;
	while (i < shell->cmd_count - 1)
	{
		shell->pipes[i] = malloc(sizeof(int) * 2);
		pipe(shell->pipes[i]);
		i++;
	}
}

void	close_pipes(t_shell *shell)
{
	int	i;

	if (!shell->pipes)
		return ;
	i = 0;
	while (i < shell->cmd_count - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		free(shell->pipes[i]);
		i++;
	}
	free(shell->pipes);
	shell->pipes = NULL;
}

static void	setup_pipe_fds(t_shell *shell, t_cmd *cmd, int cmd_index)
{
	if (cmd_index > 0)
	{
		dup2(shell->pipes[cmd_index - 1][0], STDIN_FILENO);
	}
	if (cmd_index < shell->cmd_count - 1)
	{
		dup2(shell->pipes[cmd_index][1], STDOUT_FILENO);
	}
	close_pipes(shell);
}

static void	execute_child(t_shell *shell, t_cmd *cmd, int cmd_index)
{
	char	*executable;
	char	**envp;

	if (shell->cmd_count > 1)
		setup_pipe_fds(shell, cmd, cmd_index);
	handle_redirections(cmd);
	if (is_builtin(cmd->args[0]))
	{
		shell->exit_code = execute_builtin(cmd->args[0], cmd->args, shell);
		exit(shell->exit_code);
	}
	executable = find_executable(cmd->args[0], shell->paths);
	if (!executable)
	{
		print_error(cmd->args[0], NULL, "command not found");
		exit(127);
	}
	envp = env_to_array(shell->env);
	execve(executable, cmd->args, envp);
	perror("execve");
	exit(1);
}

int	execute_commands(t_shell *shell)
{
	t_cmd	*cmd;
	int		status;
	int		cmd_index;

	if (!shell->cmds)
		return (0);
	if (shell->cmd_count == 1 && is_builtin(shell->cmds->args[0]))
	{
		handle_redirections(shell->cmds);
		shell->exit_code = execute_builtin(shell->cmds->args[0], 
			shell->cmds->args, shell);
		return (shell->exit_code);
	}
	setup_pipes(shell);
	cmd = shell->cmds;
	cmd_index = 0;
	while (cmd)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
			execute_child(shell, cmd, cmd_index);
		cmd = cmd->next;
		cmd_index++;
	}
	close_pipes(shell);
	cmd = shell->cmds;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
		cmd = cmd->next;
	}
	return (shell->exit_code);
}

/* ========== BUILT_INS.C ========== */
#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(char *cmd, char **args, t_shell *shell)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (builtin_echo(args, shell));
	if (ft_strcmp(cmd, "cd") == 0)
		return (builtin_cd(args, shell));
	if (ft_strcmp(cmd, "pwd") == 0)
		return (builtin_pwd(args, shell));
	if (ft_strcmp(cmd, "export") == 0)
		return (builtin_export(args, shell));
	if (ft_strcmp(cmd, "unset") == 0)
		return (builtin_unset(args, shell));
	if (ft_strcmp(cmd, "env") == 0)
		return (builtin_env(args, shell));
	if (ft_strcmp(cmd, "exit") == 0)
		return (builtin_exit(args, shell));
	return (1);
}

int	builtin_echo(char **args, t_shell *shell)
{
	int	i;
	int	newline;

	(void)shell;
	i = 1;
	newline = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	builtin_pwd(char **args, t_shell *shell)
{
	char	cwd[1024];

	(void)args;
	(void)shell;
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	perror("pwd");
	return (1);
}

int	builtin_cd(char **args, t_shell *shell)
{
	char	*path;
	char	*home;
	char	old_pwd[1024];
	char	*oldpwd_str;

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		ft_strcpy(old_pwd, "");
	if (!args[1])
	{
		home = env_get(shell->env, "HOME");
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (1);
		}
		path = home;
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		print_error("cd", path, strerror(errno));
		return (1);
	}
	env_remove(&shell->env, "OLDPWD");
	oldpwd_str = ft_strjoin("OLDPWD=", old_pwd);
	env_add(&shell->env, env_new("OLDPWD", old_pwd));
	free(oldpwd_str);
	return (0);
}

/* ========== ENVIRONMENT.C ========== */
#include "minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = ft_strdup(key);
	new_env->value = value ? ft_strdup(value) : NULL;
	new_env->next = NULL;
	return (new_env);
}

void	env_add(t_env **env, t_env *new_env)
{
	t_env	*temp;

	if (!env || !new_env)
		return ;
	if (!*env)
	{
		*env = new_env;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = new_env;
}

char	*env_get(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	env_remove(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !*env)
		return ;
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	env_free(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

char	**env_to_array(t_env *env)
{
	char	**array;
	int		count;
	int		i;
	char	*temp;
	t_env	*current;

	count = 0;
	current = env;
	while (current)
	{
		if (current->value)
			count++;
		current = current->next;
	}
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		if (current->value)
		{
			temp = ft_strjoin(current->key, "=");
			array[i] = ft_strjoin(temp, current->value);
			free(temp);
			i++;
		}
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}

/* ========== BUILTIN_ENV.C ========== */
#include "minishell.h"

int	builtin_env(char **args, t_shell *shell)
{
	t_env	*env;

	(void)args;
	env = shell->env;
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(env->value, 1);
		}
		env = env->next;
	}
	return (0);
}

static void	print_export_var(t_env *env)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env->key, 1);
	if (env->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env->value, 1);
		ft_putchar_fd('"', 1);
	}
	ft_putchar_fd('\n', 1);
}

static void	print_export_list(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		print_export_var(env);
		env = env->next;
	}
}

int	builtin_export(char **args, t_shell *shell)
{
	int		i;
	char	*equals;
	char	*key;
	char	*value;

	if (!args[1])
	{
		print_export_list(shell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		equals = ft_strchr(args[i], '=');
		if (equals)
		{
			key = ft_substr(args[i], 0, equals - args[i]);
			value = ft_strdup(equals + 1);
			env_remove(&shell->env, key);
			env_add(&shell->env, env_new(key, value));
			free(key);
			free(value);
		}
		else
		{
			if (!env_get(shell->env, args[i]))
				env_add(&shell->env, env_new(args[i], NULL));
		}
		i++;
	}
	return (0);
}

int	builtin_unset(char **args, t_shell *shell)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		env_remove(&shell->env, args[i]);
		i++;
	}
	return (0);
}

int	builtin_exit(char **args, t_shell *shell)
{
	int	exit_code;
	int	i;

	exit_code = shell->exit_code;
	if (args[1])
	{
		if (args[2])
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return (1);
		}
		i = 0;
		if (args[1][0] == '-' || args[1][0] == '+')
			i = 1;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(args[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				cleanup_shell(shell);
				exit(255);
			}
			i++;
		}
		exit_code = ft_atoi(args[1]);
	}
	ft_putendl_fd("exit", 2);
	cleanup_shell(shell);
	exit(exit_code);
}

/* ========== FIND_EXECUTABLE.C ========== */
#include "minishell.h"

char	*find_executable(char *cmd, char **paths)
{
	char	*full_path;
	char	*temp;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

/* ========== SIGNALS.C ========== */
#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/* ========== UTILS.C ========== */
#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	int		i;
	char	*equals;
	char	*key;
	char	*value;
	char	*path_value;

	ft_memset(shell, 0, sizeof(t_shell));
	i = 0;
	while (envp[i])
	{
		equals = ft_strchr(envp[i], '=');
		if (equals)
		{
			key = ft_substr(envp[i], 0, equals - envp[i]);
			value = ft_strdup(equals + 1);
			env_add(&shell->env, env_new(key, value));
			free(key);
			free(value);
		}
		i++;
	}
	path_value = env_get(shell->env, "PATH");
	if (path_value)
		shell->paths = ft_split(path_value, ':');
}

void	cleanup_shell(t_shell *shell)
{
	env_free(shell->env);
	env_free(shell->export_env);
	if (shell->paths)
		ft_arrfree(shell->paths);
	if (shell->pipes)
		close_pipes(shell);
	free_commands(shell->cmds);
}

void	print_error(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (s1 == s2 ? 0 : (s1 ? 1 : -1));
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* ========== ARRAY_UTILS.C ========== */
#include "minishell.h"

char	**ft_arrdup(char **arr)
{
	char	**new_arr;
	int		len;
	int		i;

	if (!arr)
		return (NULL);
	len = ft_arrlen(arr);
	new_arr = malloc(sizeof(char *) * (len + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

void	ft_arrfree(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_arrlen(char **arr)
{
	int	len;

	len = 0;
	while (arr && arr[len])
		len++;
	return (len);
}

/* ========== FREE.C ========== */
#include "minishell.h"

static void	free_redirections(t_redir *redirs)
{
	t_redir	*temp;

	while (redirs)
	{
		temp = redirs;
		redirs = redirs->next;
		if (temp->file)
			free(temp->file);
		if (temp->delimiter)
			free(temp->delimiter);
		free(temp);
	}
}

void	free_commands(t_cmd *cmds)
{
	t_cmd	*temp;

	while (cmds)
	{
		temp = cmds;
		cmds = cmds->next;
		if (temp->args)
			ft_arrfree(temp->args);
		if (temp->redirs)
			free_redirections(temp->redirs);
		free(temp);
	}
}

/* ========== MAKEFILE ========== */
/*
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c parser.c parse_command.c tokenizer.c expand.c \
       redirections.c executor.c built_ins.c environment.c \
       builtin_env.c find_executable.c signals.c utils.c \
       array_utils.c free.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
*/