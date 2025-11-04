/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:50:59 by vpoelman          #+#    #+#             */
/*   Updated: 2025/09/09 17:50:59 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**args;

	args = cmd->args;
	if (args[2])
	{
		print_cmd_error("cd", "too many arguments");
		return (1);
	}
	path = get_cd_path(args, shell);
	if (!path)
	{
		write_error("minishell: cd: HOME not set\n");
		return (1);
	}
	return (handle_cd_execution(path, shell));
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
