/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_parsing_tree.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:44 by atucci            #+#    #+#             */
/*   Updated: 2024/03/29 21:37:19 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_tree_node	*create_tree_node(t_list_of_tok *token)
{
	t_tree_node	*new_node;

	new_node = (t_tree_node *)malloc(sizeof(t_tree_node));
	new_node->priority_lev = token->priority_lev;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

/* Helper function to create a sublist from start to end */
t_list_of_tok	*create_sublist(t_list_of_tok *start, t_list_of_tok *end)
{
	t_list_of_tok	*head;
	t_list_of_tok	*new_node;

	head = NULL;
	while (start != end)
	{
		new_node = create_node(start->priority_lev, start->token);
		new_node->next = head;
		head = new_node;
		start = start->next;
	}
	return (head);
}

static t_tree_node	*create_tree(t_list_of_tok *head)
{
	t_list_of_tok	*high_priority;
	t_list_of_tok	*curr_node;
	t_tree_node		*root;
	t_list_of_tok	*head1;
	t_list_of_tok	*head2;

	if (head == NULL)
		return (NULL);
	high_priority = head;
	curr_node = head;
	while (curr_node != NULL)
	{
		if (curr_node->priority_lev > high_priority->priority_lev)
			high_priority = curr_node;
		curr_node = curr_node->next;
	}
	root = create_tree_node(high_priority);
	head1 = create_sublist(head, high_priority);
	head2 = create_sublist(high_priority->next, NULL);
	root->left = create_tree(head1);
	root->right = create_tree(head2);
	return (root);
}

t_list_of_tok	**recursive_tree_builder(t_list_of_tok **head)
{
	t_tree_node	*root;

	printf("%s**Starting with the tree**%s\n\n", GREEN, RESET);
	root = create_tree(*head);
	(void)root;
	printf("\n");
	tree_maker2();
	tree_maker3();
	printf("%s**Finish with the tree**%s\n\n", GREEN, RESET);
	return (head);
}
