/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:50:00 by atucci            #+#    #+#             */
/*   Updated: 2024/04/04 18:33:17 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "stdbool.h"

/* check carefully what need to be freed */
void	free_list(t_list_of_tok **head)
{
	t_list_of_tok	*current;
	t_list_of_tok	*next_node;

	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
		my_free(current->token, "FREE LIST");
		free(current);
		current = next_node;
	}
	*head = NULL;
}

char	*replace_me(char *str, char quote, char replacement, char me)
{
	int		i;
	bool	inside_quote;

	i = 0;
	inside_quote = false;
	while (str[i])
	{
		if (str[i] == quote)
		{
			inside_quote = !inside_quote;
			i++;
		}
		if (inside_quote && str[i] == me)
			str[i] = replacement;
		i++;
	}
	return (str);
}

int	is_logical_op(char *str)
{
	if ((my_strcmp(str, "&&") == 0) || (my_strcmp(str, "||") == 0))
		return (1);
	else
		return (0);
}

int	is_builtin(char *str)
{
	if (my_strcmp(str, "echo") == 0
		|| my_strcmp(str, "cd") == 0
		|| my_strcmp(str, "pwd") == 0
		|| my_strcmp(str, "export") == 0
		|| my_strcmp(str, "unset") == 0
		|| my_strcmp(str, "env") == 0
		|| my_strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}

/* Function to replace characters in string */
/* HERE THERE MIGHT BE SOME FIX OR LEAKS TO FIND!!! */
char	*replace_chars(char *string)
{
	char	*new_string;

	new_string = add_spaces_around_symbols(string);
	return (new_string);
}
