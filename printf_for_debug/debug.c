/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:47:07 by atucci            #+#    #+#             */
/*   Updated: 2024/03/29 21:29:11 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

const char	*g_names[] =
{
	"Command",
	"Flag",
	"Builtin",
	"Parenthesis",
	"Pipes",
	"Redirection in",
	"Redirection out",
	"Redirection appender",
	"Here Documents",
	"Logical Operator",
	"Command Arguments",
	"File Name "
};

const char	*g_colors[] =
{
	BLUE,
	PURPLE,
	GRAY,
	GREEN,
	CYAN,
	YELLOW,
	RED,
	BG_GREEN,
	BG_CYAN,
	BG_YELLOW,
	BG_RED,
	RESET
};

void	print_node(t_list_of_tok *node)
{
	printf("\n|--------------------|\n");
	printf("|ADDS %p |\n", node);
	printf("|\t(%s)\n", node->token);
	printf("|  %s%s%s\n", g_colors[node->type], g_names[node->type], RESET);
	printf("|%sPRIORITY %s%d\n", RED, RESET, node->priority_lev);
	printf("|PREV %p \n", node->previous);
	printf("|NEXT %p \n", node->next);
	printf("|INDEX %d\n", node->index);
	printf("|--------------------|\n\n");
}

void	print_list_tokens(t_list_of_tok **head)
{
	t_list_of_tok	*current;

	current = *head;
	while (current != NULL)
	{
		print_node(current);
		current = current->next;
	}
}

void	print_list_tokeny(t_list_of_tok **head)
{
	t_list_of_tok	*current;

	current = *head;
	while (current != NULL)
	{
		printf("  [%s]  ", current->token);
		current = current->next;
	}
	printf("\n");
}
