/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_advanced.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:50:02 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:50:04 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	if (n == 0)
		return (dst);
	d = dst;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;

	if (!s)
		return (NULL);
	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, n);
	dup[n] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2 + 1);
	return (result);
}

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len + 1);
	return (result);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
