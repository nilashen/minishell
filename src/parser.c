#include "minishell.h"

/**
 * Count the number of words in input (simple space-separated)
 */
int	count_words(char *input)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if ((input[i] == ' ' || input[i] == '\t') && in_word)
			in_word = 0;
		i++;
	}
	return (count);
}

/**
 * Skip whitespace characters
 */
char	*skip_whitespace(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

/**
 * Get the length of the next word
 */
int	get_word_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t')
		len++;
	return (len);
}

/**
 * Split input into array of words (simple version - no quotes yet)
 */
char	**split_input(char *input)
{
	char	**args;
	int		word_count;
	int		i;
	int		word_len;
	char	*current;

	word_count = count_words(input);
	if (word_count == 0)
		return (NULL);

	args = malloc(sizeof(char *) * (word_count + 1));
	if (!args)
		return (NULL);

	current = skip_whitespace(input);
	i = 0;
	while (i < word_count)
	{
		word_len = get_word_len(current);
		args[i] = malloc(sizeof(char) * (word_len + 1));
		if (!args[i])
		{
			// Free previously allocated memory
			while (--i >= 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
		strncpy(args[i], current, word_len);
		args[i][word_len] = '\0';
		current += word_len;
		current = skip_whitespace(current);
		i++;
	}
	args[word_count] = NULL;
	return (args);
}

/**
 * Parse command string into command structure
 */
t_cmd	*parse_command(char *input)
{
	t_cmd	*cmd;

	if (!input || !*input)
		return (NULL);

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);

	cmd->args = split_input(input);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}

	cmd->argc = count_words(input);
	return (cmd);
}

/**
 * Free command structure and its contents
 */
void	free_command(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free(cmd);
}