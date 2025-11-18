/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_process_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 22:40:00 by vpoelman          #+#    #+#             */
/*   Updated: 2025/10/27 22:40:00 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_signal(int status, int *sigint_received)
{
	if (WTERMSIG(status) == SIGINT && !(*sigint_received))
	{
		write_stdout("\n");
		*sigint_received = 1;
	}
	else if (WTERMSIG(status) == SIGPIPE)
		write_error("minishell: write error: Broken pipe\n");
}

int	wait_for_children(pid_t *pids, int count)
{
	int	status;
	int	last_status;
	int	i;
	int	sigint_received;

	last_status = 0;
	sigint_received = 0;
	i = 0;
	while (i < count)
	{
		if (waitpid(pids[i], &status, 0) > 0)
		{
			if (WIFSIGNALED(status))
				handle_child_signal(status, &sigint_received);
			if (i == count - 1)
				last_status = get_process_exit_code(status);
		}
		i++;
	}
	return (last_status);
}

int	count_commands(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds && ++count)
		cmds = cmds->next;
	return (count);
}

int	has_input_redir(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == R_IN || redirs->type == R_HEREDOC)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}

int	has_output_redir(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == R_OUT || redirs->type == R_APP)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}
