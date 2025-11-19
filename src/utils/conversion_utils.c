/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:49:44 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:49:45 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	fill_number(char *str, int n, int len)
{
	while (n > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		is_neg;

	len = num_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	is_neg = (n < 0);
	if (n == 0)
		str[0] = '0';
	if (n == -2147483648)
	{
		ft_memcpy(str, "-2147483648", 12);
		return (str);
	}
	if (is_neg)
	{
		str[0] = '-';
		n = -n;
	}
	fill_number(str, n, len);
	return (str);
}
