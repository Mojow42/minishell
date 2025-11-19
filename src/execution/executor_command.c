/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:48:31 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:48:31 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_process_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	is_permission_error(int err)
{
	return (err == EISDIR || err == EACCES || err == ENOTDIR || err == ELOOP
		|| err == ETXTBSY);
}

static int	print_exec_error(char *cmd, char *path)
{
	int	saved_errno;

	saved_errno = errno;
	if (saved_errno == EISDIR)
		print_cmd_error(cmd, "Is a directory");
	else
		print_cmd_errno(path);
	free(path);
	if (saved_errno == ENOENT)
		return (127);
	return (126);
}

int	exec_external_command(char **args, char **env)
{
	char	*path;
	int		saved_errno;

	path = find_executable(args[0], env);
	if (!path)
	{
		saved_errno = errno;
		if (ft_strchr(args[0], '/'))
			print_cmd_errno(args[0]);
		else
			print_cmd_error(args[0], "command not found");
		if (is_permission_error(saved_errno))
			return (126);
		return (127);
	}
	execve(path, args, env);
	if (errno == ENOEXEC)
		return (handle_enoexec_error(path, args, env));
	return (print_exec_error(args[0], path));
}

int	execute_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (find_builtin_index(cmd->args[0]) != -1)
		return (execute_builtin(cmd, shell));
	return (exec_external_command(cmd->args, shell->env));
}
