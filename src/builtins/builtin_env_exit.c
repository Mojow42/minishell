/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:51:05 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/04 01:05:51 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_shell *shell)
{
	int	i;

	if (!shell->env)
		return (0);
	i = 0;
	while (shell->env[i])
	{
		write_stdout(shell->env[i]);
		write_stdout("\n");
		i++;
	}
	return (0);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	int		exit_code;
	char	**args;

	args = cmd->args;
	write_stdout("exit\n");
	if (args[1])
	{
		if (args[2])
		{
			print_cmd_error("exit", "too many arguments");
			return (1);
		}
		if (!validate_exit_arg(args[1]))
		{
			cleanup_shell(shell);
			exit(2);
		}
	}
	exit_code = get_exit_code(args[1], shell->status);
	cleanup_shell(shell);
	exit(exit_code);
}
