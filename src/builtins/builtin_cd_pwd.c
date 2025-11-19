/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:47:12 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:47:12 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		set_env_var(shell, "PWD", pwd);
	free(pwd);
}

static char	*get_cd_path(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
		return (get_env_value("HOME", shell->env));
	return (cmd->args[1]);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (cmd->args[2])
	{
		print_cmd_error("cd", "too many arguments");
		return (1);
	}
	path = get_cd_path(cmd, shell);
	if (!path)
	{
		write_error("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(path) == -1)
	{
		print_cmd_errno("cd");
		return (1);
	}
	update_pwd(shell);
	return (0);
}

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		write_error("minishell: pwd: getcwd failed\n");
		return (1);
	}
	write_stdout(pwd);
	write_stdout("\n");
	free(pwd);
	return (0);
}
