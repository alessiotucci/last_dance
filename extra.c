/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:08:41 by atucci            #+#    #+#             */
/*   Updated: 2024/03/29 21:49:47 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_strchr(char *str, int cherry)
{
	size_t	count;

	count = 0;
	while (str[count])
	{
		if (str[count] == (char)cherry)
			return (&str[count]);
		count++;
	}
	return (NULL);
}

char	*my_strncpy(char *dst, const char *src, size_t len)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (len > 0)
	{
		if (src_len >= len)
			ft_memcpy(dst, src, len);
		else
		{
			ft_memcpy(dst, src, src_len);
			ft_memset(dst + src_len, '\0', len - src_len);
		}
	}
	return (dst);
}

char	*my_strndup(const char *src_str, size_t max_len)
{
	size_t	str_len;
	char	*dup_str;

	dup_str = malloc(max_len + 1);
	str_len = ft_strlen(src_str);
	if (str_len > max_len)
		str_len = max_len;
	if (!dup_str)
		return (NULL);
	ft_memcpy(dup_str, src_str, str_len);
	dup_str[str_len] = 0;
	return (dup_str);
}

int	my_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
