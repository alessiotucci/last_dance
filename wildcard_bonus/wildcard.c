/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:53:12 by atucci            #+#    #+#             */
/*   Updated: 2024/04/03 04:34:31 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*this function actively look for matches with the wildcards*/
static char	*get_prefix(char *copy)
{
	char	*prefix;
	char	*asterix;

	if (copy[0] == '*')
		prefix = NULL;
	else
	{
		asterix = my_strchr(copy, '*');
		if (asterix != NULL)
		{
			*asterix = '\0';
			prefix = copy;
		}
		else
			prefix = copy;
	}
	return (prefix);
}

static char	*get_suffix(char *copy)
{
	char	*suffix;
	char	*asterix;

	if (copy[0] == '*')
		suffix = &copy[1];
	else
	{
		asterix = my_strchr(copy, '*');
		if (asterix != NULL)
			suffix = asterix + 1;
		else
			suffix = "";
	}
	return (suffix);
}

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

/*static int	find_matches(char *wildcard, char *nam)
{
	char	*prefix;
	char	*sufx;
	char	*asterix;
	char	*copy;

	copy = ft_strdup(wildcard);
	if (copy[0] == '*')
	{
		prefix = NULL;
		sufx = &copy[1];
	}
	else
	{
		asterix = my_strchr(copy, '*');
		if (asterix != NULL)
		{
			*asterix = '\0';
			prefix = copy;
			sufx = asterix + 1;
		}
		else
		{
			prefix = copy;
			sufx = "";
		}
	}
	if (prefix != NULL && ft_strncmp(nam, prefix, ft_strlen(prefix)) != 0)
		return (free(copy), 1);
	if (sufx != NULL && my_strcmp(nam + ft_strlen(nam) - ft_strlen(sufx), sufx) != 0)
		return (free(copy), 1);
	return (free(copy),0);
}*/

/* function to know how many match we find,
 * wildcard = *.txt | ft_* | ft_*.txt */
static int	count_matches(char *wildcard)
{
	DIR				*directory;
	struct dirent	*entry;
	int				count;

	directory = opendir(".");
	if (directory == NULL)
		return (perror("Error opening directory"), -1);
	count = 0;
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (find_matches(wildcard, entry->d_name) == 0)
			count++;
		entry = readdir(directory);
	}
	if (closedir(directory) == -1)
		return (perror("Error closing directory"), -1);
	return (count);
}

/*/Helper function to expland wildcard and create a node for each
char	**expansion_wildcard(char *wildcard)
{
	DIR				*directory;
	struct dirent	*entry;
	char			**matrix;
	int				max_matrix;
	int				count;

	count = 0;
	max_matrix = count_matches(wildcard);
	if (max_matrix < 1)
		return (perror("no match wildcards"), NULL);
	matrix = malloc(sizeof(char *) * max_matrix + 1);
	directory = opendir(".");
	if (directory == NULL)
		return (perror("Error opening directory"), NULL);
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (find_matches(wildcard, entry->d_name) == 0)
		{
			matrix[count] = ft_strdup(entry->d_name);
			count++;
		}
		entry = readdir(directory);
	}
	matrix[count] = NULL;
	if (closedir(directory) == -1)
		return (perror("Error closing directory"), NULL);
	return (sort_string_array(matrix));
}
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

static char	**fill_matrix(DIR *directory, char *wildcard, int max_matrix)
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
}

//preticamente qui riwmpiamo la matrice e chiamiamo allocate... dove allochiamo la memoria 
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

static char **fill_matrix(DIR *directory, char *wildcard, int max_matrix)
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
			matrix[count++] = ft_strdup (entry->d_name);
			if (matrix[] == NULL)
			{
				perror("Memory allocation failed");
				free_string_array(matrix);
				return NULL;
			}
		}
	}

    matrix[count] = NULL;
    return matrix;
}*/
//--------------------------------------------------------------------------------------
char	**expansion_wildcard(char *wildcard)
{
	DIR		*directory;
	char	**matrix;
	int		max_matrix;

	max_matrix = count_matches(wildcard);
	if (max_matrix < 1)
		return (perror("No wildcard matches"), NULL);
	directory = opendir(".");
	if (directory == NULL)
		return (perror("Error opening directory"), NULL);
	matrix = fill_matrix(directory, wildcard, max_matrix);
	if (matrix == NULL)
		return (NULL);
	if (closedir(directory) == -1)
	{
		perror("Error closing directory");
		free_string_array(matrix);
		return (NULL);
	}
	return (sort_string_array(matrix));
}

/* this function check wheter a wildcard is valid or not */
int	valid_wildcard(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}
