/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:23:09 by atucci            #+#    #+#             */
/*   Updated: 2024/04/04 22:23:43 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_content_parenthes(char *str)
{
	char	*start_brace;
	char	*end_brace;
	char	*content;

	if (ft_strchr(str, '{'))
		start_brace = ft_strchr(str, '{');
	else
		return (str);
	if (start_brace)
	{
		end_brace = ft_strchr(start_brace + 1, '}');
		if (end_brace)
		{
			content = malloc(end_brace - start_brace);//qui vediamo qunati char da allocare.
			if (content == NULL)
				return (perror("Error: malloc"), NULL);
			my_strncpy(content, start_brace + 1, end_brace - start_brace - 1);
			content[end_brace - start_brace - 1] = '\0';
			return (free(str), content);
		}
	}
	return (str);
}

char	*expansion_dollary(char *dollar, char **env)
{
	char	*key;
	int		i;
	int		key_len;
	char	*new_dollar;

	new_dollar = extract_content_parenthes(dollar);
	//printf("%sdollar:%s (%s)\n", GREEN, RESET, dollar);
	//printf("strlen of dollar is [%s%zu%s]\n", YELLOW, strlen(dollar), RESET);
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
	i = 0;
	key_len = ft_strlen(key);
	while (env[i] != NULL)
	{
		if (strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
		{
			//printf("%sthe env[%d]: is %s%s\n", YELLOW, i, env[i], RESET);
			free(key);
			return (ft_strdup(env[i] + key_len + 1));
		}
		i++;
	}
	return (free(key), NULL);
}

// Function to replace a substring with another string
char	*replace_substr(char *str, char *substr, char *replacement)
{
	char	*result;
	char	*ins;
	char	*tmp;
	int		len_sub;
	int		len_rep;
	int		len_front;
	int		count;

	count = 0;
	len_sub = ft_strlen(substr);
	if (!str || !substr || len_sub == 0) // this can be HELPER FUNCTION 
		return (NULL);
	if (!replacement)
		replacement = "";
	len_rep = strlen(replacement);
	ins = str;
	tmp = strstr(ins, substr);
	while (tmp != NULL) // THIS can be simply HELPER FUNCTION
	{
		count++;
		ins = tmp + len_sub;
		tmp = strstr(ins, substr);
	}
	result = malloc(strlen(str) + (len_rep - len_sub) * count + 1);
	tmp = result;
	if (!result)
		return (NULL);
	while (count--) // THIS CAN BE simply HELPER FUNCTON
	{
		ins = strstr(str, substr);
		len_front = ins - str;
		tmp = strncpy(tmp, str, len_front) + len_front;
		tmp = strcpy(tmp, replacement) + len_rep;
		str += len_front + len_sub;
	}
	strcpy(tmp, str);
	return (result);
}
/*
char	*find_and_expand_vars(char *str, char **env)
{
	int		i;
	char	*var_start;
	char	*var_end;
	char	*var_name;
	char	*var_value;
	char	*var_name_with_dollar;
	char	*new_str;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$') // found a "$"!
		{
			var_start = str + i + 1; // use HELPER FUNCTION
			var_end = var_start;
			// while doing this ! USE HELPER FUNCTION!!
			while (*var_end != '\0' && *var_end != ' ' && *var_end != '$')
				var_end++;
			var_name = strndup(var_start, var_end - var_start);
			var_value = expansion_dollary(var_name, env);
			if (var_value != NULL) // if the value != EXEC HELPER FUNCITON
			{
				var_name_with_dollar = malloc(strlen(var_name) + 2);
				var_name_with_dollar[0] = '$';
				strcpy(var_name_with_dollar + 1, var_name);
				new_str = replace_substr(str, var_name_with_dollar, var_value);//new_str sarebbe la sostituzione del nome della variabile con il suo valore str = da "a/z"
				my_free(var_name_with_dollar, "var_name_with_dollar");
				str = ft_strdup(new_str);
				my_free(new_str, "new_str");
			}
			my_free(var_value, "var_value");
			my_free(var_name, "var_name");
		}
		i++;
	}
	//printf("returning this: [%s]\n", str);
	return (str);
}
*/
/*
 *
 *                                _                      _
                              | |                    (_)
  ___  ___  ___ ___  _ __   __| | __   _____ _ __ ___ _  ___  _ __
 / __|/ _ \/ __/ _ \| '_ \ / _` | \ \ / / _ \ '__/ __| |/ _ \| '_ \
 \__ \  __/ (_| (_) | | | | (_| |  \ V /  __/ |  \__ \ | (_) | | | |
 |___/\___|\___\___/|_| |_|\__,_|   \_/ \___|_|  |___/_|\___/|_| |_|
 *
 *
 * */
char	*extract_var_name(char *str, int start_index, int *end_index)
{
	char	*var_start;
	char	*var_end;

	var_start = str + start_index + 1;
	var_end = var_start;
	while (*var_end != '\0' && *var_end != ' ' && *var_end != '$')
		var_end++;
	*end_index = var_end - str;
	return strndup(var_start, var_end - var_start);
}

char	*replace_substring(char *str, char *var_name, char *var_value)
{
	char	*var_name_with_dollar;
	char	*new_str;

	var_name_with_dollar = malloc(strlen(var_name) + 2);
	var_name_with_dollar[0] = '$';
	strcpy(var_name_with_dollar + 1, var_name);
	new_str = replace_substr(str, var_name_with_dollar, var_value);
	free(var_name_with_dollar);
	return (new_str);
}

void	free_memory(char *var_name, char *var_value)
{
	free(var_name);
	free(var_value);
}

char	*find_and_expand_vars2(char *str, char **env)
{
	int		i;
	int		end_index;
	char	*var_name;
	char	*var_value;
	char	*new_str;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			var_name = extract_var_name(str, i, &end_index);
			var_value = expansion_dollary(var_name, env);
			if (var_value != NULL)
			{
				new_str = replace_substring(str, var_name, var_value);
				str = ft_strdup(new_str);
				free(new_str);
			}
			free_memory(var_name, var_value);
		}
		i++;
	}
	return str;
}

