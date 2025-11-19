/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:48:47 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:48:47 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child_process(t_cmd *cmd, t_shell *shell)
{
	setup_child_signals();
	if (cmd->redirs && process_redirections(cmd, shell, 1) != 0)
	{
		if (g_sigint_received == SIGINT)
			exit(130);
		exit(1);
	}
	exit(execute_cmd(cmd, shell));
}

static int	wait_for_child(pid_t pid, t_shell *shell)
{
	int	status;

	if (pid < 0)
	{
		write_error("minishell: fork failed\n");
		shell->status = 1;
		return (1);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (1);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write_stdout("\n");
		else if (WTERMSIG(status) == SIGPIPE)
			write_error("minishell: write error: Broken pipe\n");
	}
	return (shell->status = get_process_exit_code(status));
}

int	execute_single_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		result;

	if (!cmd->args || !cmd->args[0])
		return (0);
	if (find_builtin_index(cmd->args[0]) != -1 && !cmd->redirs)
		return (shell->status = execute_builtin(cmd, shell));
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		execute_child_process(cmd, shell);
	result = wait_for_child(pid, shell);
	setup_signals();
	return (result);
}

int	execute_commands(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return (1);
	if (!cmds->next)
		return (execute_single_command(cmds, shell));
	return (execute_pipeline_loop(cmds, shell));
}
