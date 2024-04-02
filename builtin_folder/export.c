/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:42:59 by atucci            #+#    #+#             */
/*   Updated: 2024/03/29 22:05:41 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define MAX_ENV_VARIABLES 100

char **update_env_var(char **env, char *key, char *value)
{
	int	j = 0;
	int	found = 0;

	while (env[j] != NULL)
	{
		if (strncmp(env[j], key, strlen(key)) == 0 && env[j][strlen(key)] == '=')
		{
			found = 1;
			break;
		}
		j++;
	}
	env = my_setenv(env, key, value, found);
	return (env);
}


/* 4 */
/* Extracted logic for case when VAR=123 for example */
char **handle_equals(char *arg, char **env)
{
	char	*equal_sign;
	char	*value;

	printf("%sHANDLE EQUALS%s\n", YELLOW,    RESET);
	equal_sign = ft_strchr(arg, '=');
	value = equal_sign + 1;
	/*if (!is_valid_identifier(arg))
		printf("export: not an identifier: '%s'\n", arg);
	else*/
	env = update_env_var(env, arg, value);
	*equal_sign = '=';
	return (env);
}

/* 3 */
/* Extracted logic for handling case when var does not contain a value */
char	**empty_var(char *arg, char **env)
{
	char	*existing_value;

	if (!is_valid_identifier(arg))
		printf("export: not an identifier: '%s'\n", arg);
	else
	{
		existing_value = getenv(arg);
		if (existing_value == NULL)
			env = my_setenv(env, arg, NULL, 0);
	}
	return (env);
}

/* 2 */
/* Modified to use the new handle_value_case
 * and handle_empty_value_case functions */
//void	handle_non_null_arg(char *args[], char ***env)
/* 2 HERE WE SHOULD HAVE A SLOT TO INSERT THE STRING
 Modified to use the new handle_value_case
 and handle_empty_value_case functions */
char	**export_variable(char *args[], char **env)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') != NULL)
			env = handle_equals(args[i], env);
		else
			env = empty_var(args[i], env); // here it was env
		i++;
	}
	return env;
}
/* 1 */
/* Modified to pass a pointer to the env array to handle_non_null_arg */


//void	my_export(char *args[], char *env[])
/* 1 */
/* Modified to pass a pointer to the env array to handle_non_null_arg */
char	**my_export(char *args[], char *env[])
{

	if (args[1] == NULL)
		without_arguments(env);// arguments are null
	else
		env = export_variable(args, env);
	return (env);
}
