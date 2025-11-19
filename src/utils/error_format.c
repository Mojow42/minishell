/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:49:50 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:49:50 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_errno(const char *prefix, const char *name)
{
	write_error(prefix);
	write_error(": ");
	write_error(name);
	write_error(": ");
	write_error(strerror(errno));
	write_error("\n");
}

void	print_cmd_error(const char *cmd, const char *message)
{
	write_error("minishell: ");
	write_error(cmd);
	write_error(": ");
	write_error(message);
	write_error("\n");
}

void	print_cmd_errno(const char *cmd)
{
	write_error("minishell: ");
	write_error(cmd);
	write_error(": ");
	write_error(strerror(errno));
	write_error("\n");
}
