/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 09:14:57 by atucci            #+#    #+#             */
/*   Updated: 2024/01/20 16:10:51 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*3) Function to get the size of the list */
int	get_size(t_list_of_tok *head)
{
	int	size;

	size = 0;
	while (head != NULL)
	{
		size++;
		head = head->next;
	}
	return (size);
}

/*3)
 this fuction handle the redirection process
 redirection_process(current, current->next->type);
 */
int	redirection_process(char *file_name, t_type_of_tok type)
{
	if (type == T_REDIR_IN)
		if (redirect_input(file_name))
			return (1);
	if (type == T_REDIR_OUT || type == T_REDIR_APP)
		redirect_output(file_name, type);
	if (type == T_HERE_DOC)
	{
		printf("here doc \n");
		here_document(file_name);
	}
	return (0);
}

/* this function is suppose to handle the piping if
 * the fd are differente than the standards
*/
void	piping_process(t_list_of_tok *cmd_nod)
{
	if (cmd_nod->index != 0)
	{
		dup2(cmd_nod->in_file, STDIN_FILENO);
		close(cmd_nod->in_file);
	}
	if (cmd_nod->out_file != 1)
	{
		dup2(cmd_nod->out_file, STDOUT_FILENO);
		close(cmd_nod->out_file);
	}
}

/* last change */
void	restore_original_stdout(int copy, t_list_of_tok *cmd_nod)
{
	(void)cmd_nod;
	dup2(copy, STDOUT_FILENO);
	close(copy);
}

void	restore_original_stdin(int copy, t_list_of_tok *cmd_nod)
{
	(void)cmd_nod;
	dup2(copy, STDIN_FILENO);
	close(copy);
}
