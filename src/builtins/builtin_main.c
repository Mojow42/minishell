/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:47:38 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:47:43 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtin_by_index(int i, t_cmd *cmd, t_shell *shell)
{
	if (i == 0)
		return (builtin_echo(cmd));
	if (i == 1)
		return (builtin_cd(cmd, shell));
	if (i == 2)
		return (builtin_pwd());
	if (i == 3)
		return (builtin_export(cmd, shell));
	if (i == 4)
		return (builtin_unset(cmd, shell));
	if (i == 5)
		return (builtin_env(shell));
	if (i == 6)
		return (builtin_exit(cmd, shell));
	return (-1);
}

int	find_builtin_index(char *args)
{
	char	*builtins[8];
	int		i;

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(args, builtins[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	int	index;

	index = find_builtin_index(cmd->args[0]);
	if (index == -1)
		return (-1);
	return (execute_builtin_by_index(index, cmd, shell));
}
