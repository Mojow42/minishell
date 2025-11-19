/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:49:54 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:49:56 by vpoelman         ###   ########.fr       */
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
