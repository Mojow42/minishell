/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:51:09 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/04 02:10:00 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_str_numeric(const char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	return (str[i] == '\0');
}

static void	print_numeric_error(char *arg)
{
	write_error("minishell: exit: ");
	write_error(arg);
	write_error(": numeric argument required\n");
}

int	validate_exit_arg(char *arg)
{
	if (!is_str_numeric(arg))
	{
		print_numeric_error(arg);
		return (0);
	}
	return (1);
}

static int	parse_exit_value(char *arg, long long *exit_val, int *i)
{
	while (arg[*i] >= '0' && arg[*i] <= '9')
	{
		*exit_val = *exit_val * 10 + (arg[*i] - '0');
		if (*exit_val > 9223372036854775807LL)
			return (0);
		(*i)++;
	}
	return (1);
}

int	get_exit_code(char *arg, int status)
{
	long long	exit_val;
	int			i;
	int			is_neg;

	if (!arg)
		return (status);
	exit_val = 0;
	i = 0;
	is_neg = 0;
	if (arg[i] == '+' || arg[i] == '-')
	{
		is_neg = (arg[i] == '-');
		i++;
	}
	if (!parse_exit_value(arg, &exit_val, &i))
	{
		print_numeric_error(arg);
		return (2);
	}
	if (is_neg)
		exit_val = -exit_val;
	return ((int)(exit_val & 0xFF));
}
