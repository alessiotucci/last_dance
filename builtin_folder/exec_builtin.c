/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:51:40 by atucci            #+#    #+#             */
/*   Updated: 2024/03/29 21:30:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* check for NULLS */
char	**which_built_in(t_list_of_tok *node, char **args, char **env)
{
	if (node == NULL)
		return (NULL);
	if (my_strcmp(node->token, "echo") == 0)
		minishell_echo(args);
	else if (my_strcmp(node->token, "cd") == 0)
		minishell_cd(args[1], env);
	else if (my_strcmp(node->token, "pwd") == 0)
		minishell_pwd();
	else if (my_strcmp(node->token, "export") == 0)
		return (my_export(args, env));
	else if (my_strcmp(node->token, "unset") == 0)
		minishell_unset(args[1], env);
	else if (my_strcmp(node->token, "env") == 0)
		minishell_env(env);
	else if (my_strcmp(node->token, "exit") == 0)
		minishell_exit(args);
	return (env);
}
