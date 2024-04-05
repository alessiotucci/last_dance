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

/* segfault at line 43, and fix the free at line 66 */
/*
 *
 *
//free(old_env[i]);
//TODO: fix the segfault
//printf("key:[%s]\tnew_value:[%s]\n\n", key, new_value);
//printf("check this:  ");
//TODO; this is the DEAL!!
 */
char	**my_setenv(char **old_env, char *key, char *new_value, int append_flag)
{
	int		i;
	char	*new_entry;
	int		key_len;
	char	*old_value;

	key_len = ft_strlen(key);
	i = 0;
	while (old_env[i] != NULL)
	{
		if (new_value == NULL)
			break ;
		if (ft_strncmp(old_env[i], key, key_len) == 0
			&& old_env[i][key_len] == '=')
		{
			if (append_flag)
			{
				old_value = old_env[i] + key_len + 1;
				new_entry = malloc(ft_strlen(old_value)
						+ ft_strlen(new_value) + key_len + 3);
				my_sprintf(new_entry, key, old_value, new_value);
			}
			else
			{
				new_entry = malloc(ft_strlen(new_value) + key_len + 2);
				my_sprintf(new_entry, key, NULL, new_value);
			}
			old_env[i] = new_entry;
			return (old_env);
		}
		i++;
	}
	old_env = copy_array(old_env, 1);
	if (new_value != NULL)
		new_entry = malloc(ft_strlen(new_value) + key_len + 2);
	else
	{
		new_entry = malloc(key_len);
		new_value = "";
	}
	my_sprintf(new_entry, key, NULL, new_value);
	old_env[i] = new_entry;
	free(new_entry);
	return (old_env);
}
