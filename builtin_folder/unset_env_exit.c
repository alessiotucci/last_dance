/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:13:21 by atucci            #+#    #+#             */
/*   Updated: 2024/04/06 18:11:24 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "built_ins.h"

/* Function to implement the 'unset' built-in*/
// Function to implement the 'unset' built-in
/*
void	minishell_unset(char *var_name, char *envp[])
{
	char	**env;
	int		found;
	char	**p;

	found = 0;
	env = envp;
	if (var_name == NULL || envp[1] == NULL)
		return ;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, var_name, ft_strlen(var_name)) == 0
			&& (*env)[ft_strlen(var_name)] == '=')
		{
			found = 1;
			break ;
		}
		env++;
	}
	if (found)
	{
		p = env;
		while (*p != NULL)
		{
			*p = *(p + 1);
			p++;
		}
	}
}*/
static char	**find_variable(char *var_name, char *envp[])
{
	char	**env;

	env = envp;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, var_name, ft_strlen(var_name)) == 0
			&& (*env)[ft_strlen(var_name)] == '=')
			return (env);
		env++;
	}
	return (NULL);
}

void	minishell_unset(char *var_name, char *envp[])
{
	char	**env;
	int		found;
	char	**p;
	char	**variable_location;

	if (var_name == NULL || envp[0] == NULL || envp[0] == NULL)
		return ;
	env = envp;
	found = 0;
	variable_location = find_variable(var_name, envp);
	if (variable_location != NULL)
	{
		found = 1;
		p = variable_location;
		while (*p != NULL)
		{
			*p = *(p + 1);
			p++;
		}
	}
}
//------------------------------------------

/* If no arguments provided, print the current environment variables
 * we need to double check this case
 * THIS IS SOME KIND OF BULLSHIT!! */
void	minishell_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s \n", env[i]);
		i++;
	}
}

void	handle_signal(int signal)
{
	printf("signal receive%d\n", signal);
	exit(1);
}

/*TODO: we CANT USE EXIT! */
void	minishell_exit(char **arg)
{
	int		exit_code;

	if (arg[1])
		exit_code = ft_atoi(arg[1]);
	else
		exit_code = g_exit_status;
	printf("exit with code %d\n", exit_code);
	exit(exit_code);
}
