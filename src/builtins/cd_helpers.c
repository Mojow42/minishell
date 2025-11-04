/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:53:19 by vpoelman          #+#    #+#             */
/*   Updated: 2025/09/22 23:17:02 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd_env(t_shell *shell, char *oldpwd, char *pwd)
{
	if (oldpwd)
		set_env_var(shell, "OLDPWD", oldpwd);
	if (pwd)
		set_env_var(shell, "PWD", pwd);
}

int	handle_cd_execution(char *path, t_shell *shell)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		print_cmd_errno("cd");
		free(oldpwd);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	update_pwd_env(shell, oldpwd, pwd);
	free(oldpwd);
	free(pwd);
	return (0);
}
