/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:08:41 by atucci            #+#    #+#             */
/*   Updated: 2024/04/04 22:30:24 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* helper function to check for null string arrays */
int	check_null_array(char **array)
{
	if (array == NULL)
	{
		printf("%s NULL, SOMETHING IS WRONG%s\n", RED, RESET);
		return (1);
	}
	return (0);
}

void	print_string_array(char **array)
{
	int	i;

	i = 0;
	if (check_null_array(array))
		return ;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

int	free_string_array(char **array)
{
	int	count;

	count = 0;
	if (check_null_array(array))
		return (1);
	while (array[count])
	{
		//my_free(array[count], "free string array");
		free(array[count]);
		count++;
	}
	free(array);
	return (0);
}

/* test */
int	lenght_string_array(char **array)
{
	int	count;

	count = 0;
	if (check_null_array(array))
		return (-1);
	while (array[count] != NULL)
		count++;
	return (count);
}

char	**sort_string_array(char **array)
{
	int		count;
	int		mount;
	int		lenght;
	char	*temp;

	if (check_null_array(array))
		return (NULL);
	count = 0;
	lenght = lenght_string_array(array);
	while (count < lenght - 1)
	{
		mount = 0;
		while (mount < lenght - count - 1)
		{
			if (my_strcmp(array[mount], array[mount + 1]) > 0)
			{
				temp = array[mount];
				array[mount] = array[mount + 1];
				array[mount + 1] = temp;
			}
			mount++;
		}
		count++;
	}
	return (array);
}
