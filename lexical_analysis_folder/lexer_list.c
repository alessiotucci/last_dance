/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:55:46 by atucci            #+#    #+#             */
/*   Updated: 2024/04/04 22:31:32 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*5) helper function for this case */
static char	*expansion_dollar(char *dollar, char **env)
{
	char	*key;
	int		i;
	int		key_len;

	if (dollar[0] == '$')
	{
		if (dollar[1] == '{')
			key = my_strndup(dollar + 2, ft_strlen(dollar) - 3);
		else
			key = ft_strdup(dollar + 1);
	}
	else
		key = ft_strdup(dollar);
	i = 0;
	key_len = ft_strlen(key);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (free(key), ft_strdup(env[i] + key_len + 1));
		i++;
	}
	return (free(key), NULL);
}

/*4) 
 * This function takes a node and a strings, performs several check 
 * then create the node with the fields initialized if needed, we will go 
 * from there with further implementation
 *
	//printf("spitted: %s\n", spitted);
	//printf("$ strchr: %s\n", dollar_pos);
	//printf("I need to handle better these cases\n");
	//printf("I need to handle better these cases\n");
*/
t_list_of_tok	*node_for_dollar(int lvl, char *spitted, char **env)
{
	char	*expanded;
	char	*dollar_pos;
	char	*new_str;
	char	*before_dollar;

	dollar_pos = ft_strchr(spitted, '$');
	if (dollar_pos != NULL && dollar_pos != spitted)
	{
		before_dollar = my_strndup(spitted, dollar_pos - spitted);
		expanded = expansion_dollar(dollar_pos, env);
		if (expanded == NULL)
			new_str = ft_strdup(before_dollar);
		else
		{
			new_str = malloc(strlen(before_dollar) + ft_strlen(expanded) + 1);
			strcpy(new_str, before_dollar);
			strcat(new_str, expanded);
		}
		my_free(before_dollar, "before dollar");
	}
	else
	{
		expanded = expansion_dollar(spitted, env);
		if (expanded == NULL)
			new_str = ft_strdup("");
		else
			new_str = ft_strdup(expanded);
	}
	if (expanded != NULL)
		my_free(expanded, "expanded");
	return (create_node(lvl, new_str));
}

/* FUCK CHECK THE FUNCTION YOU USE!!! */
/*3) Helper function to expand the wildcard  */
static t_list_of_tok	*node_for_wildcard(int level, char *spitted_cmd)
{
	char			**expanded;
	int				i;
	t_list_of_tok	*current;
	t_list_of_tok	*new_node;
	t_list_of_tok	*head;

	head = NULL;
	i = 0;
	expanded = expansion_wildcard(spitted_cmd);
	if (expanded == NULL)
	{
		printf("I need to handle better these cases\n");
		return (create_node(level, "failure"));
	}
	while (expanded[i])
	{
		new_node = create_node(level, expanded[i]);
		if (head == NULL)
			head = new_node;
		else
		{
			current = head;
			while (current->next != NULL)
				current = current->next;
			current->next = new_node;
			new_node->previous = current;
			new_node->index = current->index + 1;
		}
		i++;
	}
	return (head);
}

char	*extract_content(char *str)
{
	char	*start_quote;
	char	*end_quote;
	char	*content;
	char	quote_char;

	if (ft_strchr(str, '\"'))
		quote_char = '\"';
	else if (ft_strchr(str, '\''))
		quote_char = '\'';
	else
		return (str);
	start_quote = ft_strchr(str, quote_char);
	if (start_quote)
	{
		end_quote = ft_strchr(start_quote + 1, quote_char);
		if (end_quote)
		{
			content = malloc(end_quote - start_quote);
			if (content == NULL)
				return (perror("Error: malloc"), NULL);
			my_strncpy(content, start_quote + 1, end_quote - start_quote - 1);
			content[end_quote - start_quote - 1] = '\0';
			return (my_free(str, "extract_content"), content);
		}
	}
	return (str);
}

/*TODO: exit is forbidden */
/*TODO: THIS WAS A QUICK FIX (using the ft_strdup) */
/*2)  Helper function to create a new node */
t_list_of_tok	*create_node(int level, char *spitted_cmd)
{
	t_list_of_tok	*new_node;

	new_node = (t_list_of_tok *)malloc(sizeof(t_list_of_tok));
	if (new_node == NULL)
	{
		printf("Error with malloc");
		exit(1);
	}
	new_node->token = ft_strdup(spitted_cmd);
	new_node->type = type_of_token(spitted_cmd);
	new_node->priority_lev = level;
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->index = 0;
	new_node->file_name = NULL;
	new_node->in_file = STDIN_FILENO;
	new_node->out_file = STDOUT_FILENO;
	return ((new_node));
}

/* there is still something still reachable */
/*TODO: finish up the debugging
 *check free something
 //VARS2 PERCHE@ line 201 there is a issue
//printf("string for node_for_dollar: (%s)\n", new_cmd);
//printf("string after the work: (%s)\n", new_cmd);
*1) Function to create a list of tokens, char cmd is a part of split! */
t_list_of_tok	*create_list(t_list_of_tok **head, char *cmd, char **en, int f)
{
	t_list_of_tok	*new_node;
	t_list_of_tok	*current;
	char			*new_cmd;
	char			*dollar_cmd;

	(void)f;
	(void)en;
	new_cmd = extract_content(cmd);
	if (valid_wildcard(cmd))
		new_node = node_for_wildcard(0, cmd);
	else if ((ft_strchr(new_cmd, '$') != NULL) && (f != SINGLE_QUOTE))
	{
		dollar_cmd = find_and_expand_vars2(new_cmd, en);
		new_node = create_node(0, dollar_cmd);
	}
	else
		new_node = create_node(0, new_cmd);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->previous = current;
		new_node->index = current->index + 1;
	}
	return (new_node);
}
