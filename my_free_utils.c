/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:01:42 by atucci            #+#    #+#             */
/*   Updated: 2024/04/04 22:30:42 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

/*printf("%s: address_pointer: %p, %s[%s]%s\n",
 * log, ptr, YELLOW, (char *)ptr, RESET); */
void	my_free(void *ptr, char *log)
{
	if (ptr == NULL)
		printf(PURPLE"%s: The pointer is already NULL.\n"RESET, log);
	else
	{
		free(ptr);
	}
}
