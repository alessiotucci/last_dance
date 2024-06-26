/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:25:22 by atucci            #+#    #+#             */
/*   Updated: 2024/04/04 21:56:23 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "../minishell.h"

int	g_exit_status;

/* 5 function in this file 
 * This function goes throught he list and look for commands,
 * it return the first it finds !
 * */
t_list_of_tok	*find_command_in_list(t_list_of_tok **head)
{
	t_list_of_tok	*cmd_nod;

	cmd_nod = *head;
	while (cmd_nod != NULL)
	{
		if (cmd_nod->type == T_COMMAND || cmd_nod->type == T_BUILTIN)
			return (cmd_nod);
		cmd_nod = cmd_nod->next;
	}
	return (NULL);
}

/* 4) this functinon needs to be written entirely 
 * it has being copy and paste from bingAi again
*/
t_list_of_tok	*open_file(t_list_of_tok *nod)
{
	int	fd;

	if (nod->type == T_REDIR_OUT)
		fd = open(nod->next->token, OVERWRITE_FLAGS, 0666);
	else
		fd = open(nod->next->token, APPEND_FLAGS, 0666);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (nod);
}

/* function to find the last redirection, if there is more, open empty file */
int	find_redirect(t_list_of_tok *cmd_node)
{
	t_list_of_tok	*iterator;
	t_list_of_tok	*last_redirect;

	last_redirect = NULL;
	iterator = cmd_node;
	while (iterator != NULL)
	{
		if (iterator->type == T_REDIR_OUT || iterator->type == T_REDIR_APP
			|| iterator->type == T_REDIR_IN || iterator->type == T_HERE_DOC)
		{
			if (iterator->next == NULL)
				return (print_and_update("zsh: parse error near '\\n\'\n",
						GENERAL_ERROR, 1), 1);
			if (iterator->next->type == T_FILE_NAME)
				last_redirect = open_file(iterator);
		}
		iterator = iterator->next;
	}
	if (last_redirect != NULL)
	{
		cmd_node->file_name = ft_strdup(last_redirect->next->token);
		cmd_node->redirect_type = last_redirect->type;
		return (0);
	}
	return (0);
}

/* 2)
 * first handle the redirection
 * then check for builtins, after perform built in, restore fd (?)
 * otherwise fork and go on with execve, after that restore fd (?)
 * // this seems to work at line 178
	//TODO: need to fix the case with the cat to close the stdin etc
*/
char	**exec_cmd(char *cmd, char **args, char **envp, t_list_of_tok *cmd_nod)
{
	pid_t	fix_pid;
	int		stdout_copy;
	int		stdin_copy;
	char	**updated;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	piping_process(cmd_nod);
	if (cmd_nod->file_name != NULL)
		if (redirection_process(cmd_nod->file_name, cmd_nod->redirect_type))
			return (NULL);
	if (cmd_nod->type == T_BUILTIN)
		updated = which_built_in(cmd_nod, args, envp);
	else
	{
		updated = envp;
		fix_pid = fork();
		if (fix_pid == 0)
		{
			if (my_strcmp(cmd_nod->token, "cat") == 0 && cmd_nod->next != NULL
				&& cmd_nod->next->type != T_HERE_DOC
				&& cmd_nod->next->type != T_REDIR_IN)
				close(cmd_nod->next->next->in_file);
			execve(cmd, args, envp);
			printf_fd(cmd, stdout_copy);
			print_and_update(": command not found\n", COMMAND_NOT_FOUND,
				stdout_copy);
			return (NULL);
		}
	}
	restore_original_stdout(stdout_copy, cmd_nod);
	restore_original_stdin(stdin_copy, cmd_nod);
	if (cmd_nod->type != T_BUILTIN)
		my_free(cmd, "execute_command");
	return (updated);
}

/*
 * 1) Main function to execute the program
 * I go find the first command in the list
 * Inside the node of the command I update the filename
 * if there is a redirection, the command string take the
 * token of the node 
 * 
 */
void	wait_exit_status(void)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

/*TODO: check for the strdup at line 172, it can fix some issues
 *TODO: try to free before the cmd_node the command, it can fix leaks */
/*TODO: we need to fix the env copy or free it if necessary at line 186*/
char	**executor(t_list_of_tok **head, char **envp)
{
	char			*command;
	char			**argoums;
	t_list_of_tok	*cmd_node;
	char			**updated;
	t_list_of_tok	**truth;

	truth = head;
	cmd_node = find_command_in_list(head);
	while (cmd_node != NULL)
	{
		if (find_redirect(cmd_node) == 1)
			break ;
		if (find_pipes(cmd_node) == 1)
			break ;
		command = cmd_node->token;
		if (cmd_node->type != T_BUILTIN)
		{
			command = find_path_command(cmd_node->token, envp);
			if (command == NULL)
				command = cmd_node->token;
		}
		argoums = array_from_list(&cmd_node);
		updated = exec_cmd(command, argoums, envp, cmd_node);
		free_string_array(argoums);
		cmd_node = find_command_in_list(&cmd_node->next);
	}
	wait_exit_status();
	free_list(truth);
	return (updated);
}
