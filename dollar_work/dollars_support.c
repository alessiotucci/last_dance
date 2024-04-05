#include "../minishell.h"

static  char *expansion_dollary_helper(char *key, char **env)
{
	int		i;
	int		key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i] != NULL)
	{
		if (strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (free(key), ft_strdup(env[i] + key_len + 1));
		i++;
	}
	return (free(key), NULL);
}

char	*expansion_dollary(char *dollar, char **env)
{
	char	*key;
	char	*new_dollar;

	new_dollar = extract_content_parenthes(dollar);
	if (ft_strlen(dollar) == 1 && dollar[0] == '?' )
		return (ft_itoa(g_exit_status));
	if (dollar[0] == '$')
	{
		if (dollar[1] == '{')
			key = my_strndup(dollar + 2, ft_strlen(dollar) - 3);
		else
			key = ft_strdup(dollar + 1);
	}
	else
		key = ft_strdup(new_dollar);
	
	return expansion_dollary_helper(key, env);
}

/*qua facciamo la sostituzione effettiva ma infondo non è tanto doversa da quella tutta intera */
static void replace_all(char *result, char *str, char *substr, char *replacement)
{
	char *ins;
	int len_front;
	size_t len_substr = ft_strlen(substr);
	size_t len_replacement = ft_strlen(replacement);

	while (*str)
	{
		ins = strstr(str, substr);
		if (ins == NULL)
		{
			strcpy(result, str);
			return;
		}
		len_front = ins - str;
		strncpy(result, str, len_front);
		result += len_front;
		strcpy(result, replacement);
		result += len_replacement;
		str += len_front + len_substr;
	}
	*result = '\0';
}

static int	count_occurrences(char *str, char *substr)
{
	int count = 0;
	char *tmp = strstr(str, substr);
	size_t len_substr = ft_strlen(substr);
	while (tmp != NULL)
	{
		count++;
		str = tmp + len_substr;
		tmp = strstr(str, substr);
	}
	return count;
}
/*funzione iniziale ho lasciato lo stesso nome  fa i check richiama il conto delle occorrenze chiama replace all  e il return*/
char	*replace_substr(char *str, char *substr, char *replacement)
{
	char	*result;
	int		count;

	if (!str || !substr || ft_strlen(substr) == 0)
		return (NULL);

	count = count_occurrences(str, substr);
	result = malloc((strlen(str) + (strlen(replacement) - strlen(substr)) * count + 1) * sizeof(char));

	if (!result)
		return (NULL);

	replace_all(result, str, substr, replacement);

	return (result);
}

