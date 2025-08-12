
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
 * Split input into array of words (now handles quotes and variables)
 */
char	**split_input(char *input)
{
	char	**args;
	int		word_count;
	int		i;
	int		word_len;
	char	*current;
	char	*processed_word;

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
		processed_word = malloc(sizeof(char) * (word_len + 1));
		if (!processed_word)
		{
			// Free previously allocated memory
			while (--i >= 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
		strncpy(processed_word, current, word_len);
		processed_word[word_len] = '\0';
		
		// Handle quotes and variable expansion
		args[i] = handle_quotes(processed_word);
		free(processed_word);
		
		if (!args[i])
		{
			// Free previously allocated memory
			while (--i >= 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
		
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
 * Find closing quote matching the opening quote
 */
int	find_closing_quote(char *str, char quote_char)
{
	int	i;

	i = 1; // Start after opening quote
	while (str[i])
	{
		if (str[i] == quote_char)
			return (i);
		i++;
	}
	return (-1); // No closing quote found
}

/**
 * Expand environment variables in a string
 * Handles $VAR and $?
 */
char	*expand_variables(char *str)
{
	char	*result;
	char	*temp;
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;
	int		var_len;
	int		result_len;

	if (!str)
		return (NULL);

	// Calculate needed size (rough estimate)
	result_len = strlen(str) * 2; // Overestimate for safety
	result = malloc(result_len);
	if (!result)
		return (NULL);

	i = 0;
	j = 0;
	while (str[i] && j < result_len - 1)
	{
		if (str[i] == ')
		{
			i++; // Skip $
			if (str[i] == '?')
			{
				// Handle $? - exit status
				temp = malloc(12); // Enough for int
				sprintf(temp, "%d", g_last_exit_status);
				strcpy(result + j, temp);
				j += strlen(temp);
				free(temp);
				i++;
			}
			else if (str[i] && (isalnum(str[i]) || str[i] == '_'))
			{
				// Handle $VAR
				var_len = 0;
				while (str[i + var_len] && (isalnum(str[i + var_len]) || str[i + var_len] == '_'))
					var_len++;
				
				var_name = malloc(var_len + 1);
				strncpy(var_name, str + i, var_len);
				var_name[var_len] = '\0';
				
				var_value = getenv(var_name);
				if (var_value)
				{
					strcpy(result + j, var_value);
					j += strlen(var_value);
				}
				
				free(var_name);
				i += var_len;
			}
			else
			{
				// Just a lone $ - copy it
				result[j++] = ';
			}
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
	return (result);
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

/**
 * Handle quotes and variable expansion
 * Single quotes: no expansion
 * Double quotes: allow variable expansion
 * No quotes: allow variable expansion
 */
char	*handle_quotes(char *str)
{
	char	*result;
	char	*temp;
	int		i;
	int		j;
	int		len;
	int		closing_quote;

	if (!str)
		return (NULL);

	len = strlen(str);
	result = malloc(len * 2); // Overestimate
	if (!result)
		return (NULL);

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			// Single quotes - no expansion
			closing_quote = find_closing_quote(str + i, '\'');
			if (closing_quote == -1)
			{
				// Unclosed quote - copy as is for now
				result[j++] = str[i++];
			}
			else
			{
				// Copy content between quotes without quotes
				i++; // Skip opening quote
				while (i < i + closing_quote - 1)
					result[j++] = str[i++];
				i++; // Skip closing quote
			}
		}
		else if (str[i] == '"')
		{
			// Double quotes - allow variable expansion
			closing_quote = find_closing_quote(str + i, '"');
			if (closing_quote == -1)
			{
				// Unclosed quote - copy as is for now
				result[j++] = str[i++];
			}
			else
			{
				// Extract content and expand variables
				temp = malloc(closing_quote);
				strncpy(temp, str + i + 1, closing_quote - 1);
				temp[closing_quote - 1] = '\0';
				
				char *expanded = expand_variables(temp);
				if (expanded)
				{
					strcpy(result + j, expanded);
					j += strlen(expanded);
					free(expanded);
				}
				free(temp);
				i += closing_quote + 1; // Skip past closing quote
			}
		}
		else
		{
			// No quotes - copy char but check for variables
			if (str[i] == ')
			{
				// Handle variable expansion
				temp = malloc(strlen(str + i) + 1);
				strcpy(temp, str + i);
				char *expanded = expand_variables(temp);
				if (expanded)
				{
					strcpy(result + j, expanded);
					j += strlen(expanded);
					// Skip past the variable in original string
					i++; // Skip $
					if (str[i] == '?')
						i++;
					else
						while (str[i] && (isalnum(str[i]) || str[i] == '_'))
							i++;
					free(expanded);
				}
				free(temp);
			}
			else
			{
				result[j++] = str[i++];
			}
		}
	}
	result[j] = '\0';
	return (result);
}