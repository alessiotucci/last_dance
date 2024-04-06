/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:01:33 by ftroise           #+#    #+#             */
/*   Updated: 2024/04/06 17:15:24 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**allocate_matrix(int max_matrix)
{
	char	**matrix;

	matrix = malloc(sizeof(char *) * (max_matrix + 1));
	if (matrix == NULL)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	return (matrix);
}
//-----------------------------fill matrix la divido in 2
/*static char	**fill_matrix(DIR *directory, char *wildcard, int max_matrix)
{
	struct dirent		*entry;
	char				**matrix;
	int					count;

	matrix = allocate_matrix(max_matrix);
	if (matrix == NULL)
		return (NULL);
	count = 0;
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (find_matches(wildcard, entry->d_name) == 0)
		{
			matrix[count++] = ft_strdup(entry->d_name);
			if (matrix[count] == NULL)
			{
				perror("Memory allocation failed");
				free_string_array(matrix);
				return (NULL);
			}
		}
		entry = readdir(directory);
	}
	matrix[count] = NULL;
	return (matrix);
}*/

static char	**allocate_and_check_wildcards(DIR *directory,
	char *wildcard, int max_matrix)
{
	char			**matrix;
	struct dirent	*entry;

	matrix = allocate_matrix(max_matrix);
	if (matrix == NULL)
		return (NULL);
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (find_matches(wildcard, entry->d_name) == 0)
			break ;
		entry = readdir(directory);
	}
	return (matrix);
}

char	**fill_matrix(DIR *directory, char *wildcard, int max_matrix)
{
	char			**matrix;
	struct dirent	*entry;
	int				i;

	matrix = allocate_and_check_wildcards(directory, wildcard, max_matrix);
	if (matrix == NULL)
		return (NULL);
	i = 0;
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (find_matches (wildcard, entry->d_name) == 0)
		{
			matrix[i++] = ft_strdup (entry->d_name);
			if (matrix[i] == NULL)
			{
				perror("Memory allocation failed");
				free_string_array(matrix);
				return (NULL);
			}
		}
	}
	matrix[i] = NULL;
	return (matrix);
}
//qui riwmpiamo la matrice e chiamiamo allocate... dove allochiamo la memoria 

int	find_matches(char *wildcard, char *nam)
{
	char	*prefix;
	char	*suffix;
	char	*copy;

	copy = ft_strdup(wildcard);
	prefix = get_prefix(copy);
	suffix = get_suffix(copy);
	if (prefix != NULL && ft_strncmp(nam, prefix, ft_strlen(prefix)) != 0)
		return (free(copy), 1);
	if (suffix != NULL && my_strcmp(nam + ft_strlen(nam)
			- ft_strlen(suffix), suffix) != 0)
		return (free(copy), 1);
	free(copy);
	return (0);
}
