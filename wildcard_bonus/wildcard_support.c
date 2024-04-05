/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:55:56 by marvin            #+#    #+#             */
/*   Updated: 2024/04/05 22:55:56 by marvin           ###   ########.fr       */
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
//----------------------------------------------------- fill matrix la divido in 2
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
static char **allocate_and_check_wildcards(DIR *directory, char *wildcard, int max_matrix)
{
	char	**matrix = allocate_matrix(max_matrix);
	if (matrix == NULL)
		return NULL;
	struct dirent	*entry = readdir(directory);
	while (entry != NULL) {
		if (find_matches(wildcard, entry->d_name) == 0)
		{
			break;
		}
	entry = readdir(directory);
	}
	return matrix;
}

char **fill_matrix(DIR *directory, char *wildcard, int max_matrix)
{
	char	**matrix = allocate_and_check_wildcards(directory, wildcard, max_matrix);
	if (matrix == NULL)
		return NULL;
	struct	dirent *entry;
	int	i;

	i = 0;
	
	while ((entry = readdir (directory)) != NULL)
	{
		if (find_matches (wildcard, entry->d_name) == 0)
		{
			matrix[i++] = ft_strdup (entry->d_name);
			if (matrix[i] == NULL)
			{
				perror("Memory allocation failed");
				free_string_array(matrix);
				return NULL;
			}
		}
	}

    matrix[i] = NULL;
    return matrix;
}
//preticamente qui riwmpiamo la matrice e chiamiamo allocate... dove allochiamo la memoria 

