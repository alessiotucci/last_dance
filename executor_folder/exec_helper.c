/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:38:22 by atucci            #+#    #+#             */
/*   Updated: 2024/04/04 21:46:45 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 4) */
char	*find_path_command(char *token, char **envp)//
{
	int		i;
	int		y;
	char	*possible_command;
	char	**directs;

	directs = find_path_env(envp);
	if (directs == NULL)
		return (NULL);
	i = 0;
	while (directs[i] != NULL)
	{
		y = ft_strlen(directs[i]) + ft_strlen(token) + 2;
		possible_command = malloc(y);
		ft_strlcpy(possible_command, directs[i], y);
		ft_strlcat(possible_command, "/", y);
		ft_strlcat(possible_command, token, y);
		if (access(possible_command, X_OK) == 0)
			return (free_string_array(directs), possible_command);
		my_free(possible_command, "FIND_PATH_COMMAND");
		i++;
	}
	return (free_string_array(directs), NULL);
}

/*2) helper function to find the path in the ev */
char	**find_path_env(char **env)
{
	int		i;
	char	*nully;

	nully = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			nully = env[i] + 5;
			break ;
		}
		i++;
	}
	if (nully != NULL)
		return (ft_split(nully, ':'));
	return (NULL);
}

int	valid_for_list(t_list_of_tok *node)
{
	if (node->type == T_COMMAND
		|| node->type == T_BUILTIN
		|| node->type == T_COMMAND_ARGS
		|| node->type == T_FLAG)
		return (1);
	return (0);
}

int	break_loop(t_list_of_tok *node)
{
	if (node->type == T_PIPES
		|| node->type == T_REDIR_IN
		|| node->type == T_REDIR_OUT
		|| node->type == T_REDIR_APP
		|| node->type == T_HERE_DOC)
		return (1);
	return (0);
}

/*1) Function to create argv for execve */
char	**array_from_list(t_list_of_tok **head)
{
	int				size;
	char			**argv;
	t_list_of_tok	*current;
	int				i;

	size = get_size(*head);
	argv = malloc((size + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	current = *head;
	i = 0;
	while (current != NULL)
	{
		if (valid_for_list(current))
		{
			argv[i] = ft_strdup(current->token);
			if (!argv[i])
				return (NULL);
			i++;
		}
		else if (break_loop(current))
			break ;
		current = current->next;
	}
	argv[i] = (NULL);
	return (argv);
}
