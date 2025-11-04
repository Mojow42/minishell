/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:00:00 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/03 23:24:34 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(const char *message)
{
	if (message)
		write(STDERR_FILENO, message, ft_strlen(message));
}

void	write_stdout(const char *message)
{
	if (message)
		write(STDOUT_FILENO, message, ft_strlen(message));
}
