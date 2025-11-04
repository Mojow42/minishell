/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:51:02 by vpoelman          #+#    #+#             */
/*   Updated: 2025/10/22 23:35:29 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo_args(char **args, int start_idx)
{
	int	i;

	i = start_idx;
	while (args[i])
	{
		write_stdout(args[i]);
		if (args[i + 1])
			write_stdout(" ");
		i++;
	}
}

int	builtin_echo(t_cmd *cmd)
{
	int		n_flag;
	char	**args;
	int		start_idx;

	n_flag = 0;
	args = cmd->args;
	start_idx = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		n_flag = 1;
		start_idx = 2;
	}
	print_echo_args(args, start_idx);
	if (!n_flag)
		write_stdout("\n");
	return (0);
}

char	*get_cd_path(char **args, t_shell *shell)
{
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		return (get_env_value("HOME", shell->env));
	return (args[1]);
}
