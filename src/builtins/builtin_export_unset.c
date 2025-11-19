/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:47:31 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:47:31 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	char	**args;
	int		i;

	args = cmd->args;
	if (!args[1])
	{
		print_exported_vars(shell, 0);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i], shell) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_identifier(const char *key)
{
	int	i;

	if (!(ft_isalnum(key[0]) || key[0] == '_'))
		return (0);
	if (key[0] >= '0' && key[0] <= '9')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	char	**args;
	int		i;

	args = cmd->args;
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			write_error("minishell: unset: `");
			write_error(args[i]);
			write_error("': not a valid identifier\n");
			return (1);
		}
		unset_env_var(shell, args[i]);
		i++;
	}
	return (0);
}
