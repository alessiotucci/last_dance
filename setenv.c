/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:30:20 by atucci            #+#    #+#             */
/*   Updated: 2024/03/29 21:44:16 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

/*
void	my_sprintf(char *buffer, char *key, char *old_value, char *new_value)
{
	int	bufflen;

	bufflen = ft_strlen(buffer);
	ft_strlcpy(buffer, key, ft_strlen(key) + 1);
	ft_strlcat(buffer, "=", bufflen + 2);
	if (old_value != NULL)
		ft_strlcat(buffer, old_value, ft_strlen(old_value) + bufflen + 1);
	ft_strlcat(buffer, new_value, ft_strlen(new_value) + bufflen + 1);
}

char	**my_setenv(char **old_copy, char *key, char *new_vue, int append_flag)
{
	int		i;
	char	*new_entry;
	int		key_len;
	char	*old_vue;

	key_len = ft_strlen(key);
	i = 0;
	while (old_copy[i] != NULL)
	{
		if (ft_strncmp(old_copy[i], key, key_len) == 0
			&& old_copy[i][key_len] == '=')
		{
			if (append_flag)
			{
				old_vue = old_copy[i] + key_len + 1;
				new_entry = malloc(ft_strlen(old_vue) + ft_strlen(new_vue) + key_len + 3);
				my_sprintf(new_entry, key, old_vue, new_vue);
			}
			else
			{
				new_entry = malloc(ft_strlen(new_vue) + key_len + 2);
				my_sprintf(new_entry, key, NULL, new_vue);
			}
			free(old_copy[i]);
			old_copy[i] = new_entry;
			return (old_copy);
		}
		i++;
	}
	old_copy = copy_array(old_copy, 1);
	new_entry = malloc(ft_strlen(new_vue) + key_len + 2);
	my_sprintf(new_entry, key, NULL, new_vue);
	old_copy[i] = new_entry;
	return (old_copy);
}


void	my_sprintf(char *buffer, char *key, char *old_value, char *new_value)
{
	int	bufflen;

	bufflen = ft_strlen(buffer);
	ft_strlcpy(buffer, key, ft_strlen(key) + 1);
	ft_strlcat(buffer, "=", bufflen + 2);
	if (old_value != NULL)
		ft_strlcat(buffer, old_value, ft_strlen(old_value) + bufflen + 1);
	ft_strlcat(buffer, new_value, ft_strlen(new_value) + bufflen + 1);
}
*/

void	my_sprintf(char *buffer, char *key, char *old_value, char *new_value)
{
	int	bufflen;

	bufflen = ft_strlen(buffer);
	ft_strlcpy(buffer, key, ft_strlen(key) + 1);
	ft_strlcat(buffer, "=", bufflen + 2);
	if (old_value != NULL)
		ft_strlcat(buffer, old_value, ft_strlen(old_value) + bufflen + 1);
	ft_strlcat(buffer, new_value, ft_strlen(new_value) + bufflen + 1);
}

char **my_setenv(char **old_env, char *key, char *new_value, int append_flag)
{
	int		i;
	char	*new_entry;
	int		key_len;
	char	*old_value;

	//printf("check this:  ");
	//printf("key:[%s]\tnew_value:[%s]\n\n", key, new_value);
	key_len = ft_strlen(key);
	i = 0;
	while (old_env[i] != NULL)
	{
		if (new_value == NULL) //TODO: fix the segfault
			break ;
		if (ft_strncmp(old_env[i], key, key_len) == 0
			&& old_env[i][key_len] == '=')
		{
			if (append_flag)
			{
				old_value = old_env[i] + key_len + 1;
				new_entry = malloc(ft_strlen(old_value) + ft_strlen(new_value) + key_len + 3);
				my_sprintf(new_entry, key, old_value, new_value);
			}
			else
			{
				new_entry = malloc(ft_strlen(new_value) + key_len + 2);
				my_sprintf(new_entry, key, NULL, new_value);
			}
			free(old_env[i]);
			old_env[i] = new_entry;
			return (old_env);
		}
		i++;
	}
	old_env = copy_array(old_env, 1); //TODO; this is the DEAL!!
	if (new_value != NULL)
		new_entry = malloc(ft_strlen(new_value) + key_len + 2);
	else
	{
		new_entry = malloc(key_len);
		//printf("new_value is null, ELSE\n");
		new_value = "";
	}
	//printf("new_entry: [%s] key:[%s] new_value:[%s]\n", new_entry, key, new_value);
	my_sprintf(new_entry, key, NULL, new_value);
	old_env[i] = new_entry;
	//printf("'%s', old_env[%d]\n", old_env[i], i);
	//print_string_array(sort_string_array(old_env));
	//printf("the lenght: [%s%d%s]\n", RED, lenght_string_array(old_env), RESET);
	//printf("%sold_env  is\n%p%s\n", RED, old_env, RESET);
	return (old_env);
}
