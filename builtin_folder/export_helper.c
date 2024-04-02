/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:08:41 by atucci            #+#    #+#             */
/*   Updated: 2024/03/29 22:08:28 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/* 8 */
void	export_format(char *var, char *value)
{
	printf("declare -x %s=\"%s\"\n", var, value);
}

/* 7 */
int	is_valid_identifier(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* 6 
void	without_arguments(char *env[])
{
	int		i;
	char	*equal_sign;
	char	*value;

	i = 0;
	sort_string_array(env);
	while (env[i] != NULL)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign != NULL)
		{
			value = equal_sign + 1;
			export_format(env[i], value);
		}
		i++;
	}
}*/
/* 2: export is being called without arguments */
void	without_arguments(char *env[])
{
	int		i;
	char	*equal_sign;
	char	*value;

	i = 0;
	sort_string_array(env);
	while (env[i] != NULL)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign != NULL)
		{
			value = equal_sign + 1;
			export_format(env[i], value);
		}
		i++;
	}
}
