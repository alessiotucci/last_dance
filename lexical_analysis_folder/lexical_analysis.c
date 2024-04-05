/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:09 by atucci            #+#    #+#             */
/*   Updated: 2024/04/04 22:32:01 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_number(int total, int count_single, int count_double)
{
	if (total % 2 != 0)
		return (ERROR_QUOTE);
	else if (total > 2)
		return (SEVERAL_QUOTES);
	else if (count_single == 0 && count_double == 0)
		return (NO_QUOTE);
	else if (count_single != 0 && count_double == 0)
		return (SINGLE_QUOTE);
	else if (count_single == 0 && count_double != 0)
		return (DOUBLE_QUOTE);
	else
		return (NO_QUOTE);
}

int	handling_quotes(char *input)
{
	int	count_single;
	int	count_double;
	int	i;
	int	total_quotes;

	i = 0;
	count_double = 0;
	count_single = 0;
	while (input[i])
	{
		if (input[i] == '"' )
			count_double++;
		if (input[i] == 39)
			count_single++;
		i++;
	}
	total_quotes = count_single + count_double;
	return (process_number(total_quotes, count_single, count_double));
}

/* Function to handle quotes 
 * it returns ZERO in ok case*/
int	handle_quotes(char *string)
{
	if (handling_quotes(string) == ERROR_QUOTE)
		return (set_g_exit(GENERAL_ERROR),
			printf("Not interpret unclosed quotes\n"));
	return (0);
}

/* Function to check parentheses
 * it returns ZERO in ok case*/
int	first_check_parent(char *string)
{
	if (check_parentheses(string))
		return (set_g_exit(GENERAL_ERROR),
			printf("syntax error near unexpected token\n"));
	return (0);
}

/*2 Function to create list of tokens */
void	create_tokens(char **commands, t_list_of_tok **head, char **env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (commands[i])
	{
		commands[i] = replace_me(commands[i], '"', ' ', '\t');
		commands[i] = replace_me(commands[i], 39, ' ', '\t');
		flag = handling_quotes(commands[i]);
		create_list(head, commands[i], env, flag);
		i++;
	}
	free_string_array(commands);
}
/* there is something still reachable */

/*1 The main function of the lexer, we use split and get the command line*/
//int	lexer(char *string, char **env)
/*TODO: in the return statement there was a needed free. but  I changed*/
t_list_of_tok	*lexer(char *string, char **env)
{
	char			**line_of_commands;
	t_list_of_tok	*token_head;
	char			*new_string;

	token_head = NULL;
	if (handle_quotes(string) || first_check_parent(string))
		return (NULL);
	new_string = replace_chars(string);
	new_string = replace_me(new_string, '"', '\t', ' ');
	new_string = replace_me(new_string, 39, '\t', ' ');
	line_of_commands = ft_split(new_string, ' ');
	my_free(new_string, "LEXER");
	create_tokens(line_of_commands, &token_head, env);
	update_token_types(&token_head);
	return (token_head);
}

//lexer = una sorta di main di questa patte di codice, 
