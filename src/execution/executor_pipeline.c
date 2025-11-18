/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 00:00:00 by vpoelman          #+#    #+#             */
/*   Updated: 2025/10/27 22:35:00 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_child_pipes(t_cmd *cmd, t_exec_ctx *ctx, int pfd[2])
{
	if (ctx->prev_pipe != -1)
	{
		if (!has_input_redir(cmd->redirs))
			dup2(ctx->prev_pipe, STDIN_FILENO);
		close(ctx->prev_pipe);
	}
	if (cmd->next)
	{
		if (!has_output_redir(cmd->redirs))
		{
			dup2(pfd[1], STDOUT_FILENO);
			close(pfd[1]);
		}
		else
			close(pfd[1]);
		close(pfd[0]);
	}
}

static void	handle_child(t_cmd *cmd, t_shell *shell, t_exec_ctx *ctx,
		int pipefd[2])
{
	setup_child_signals();
	setup_child_pipes(cmd, ctx, pipefd);
	if (cmd->redirs && process_redirections(cmd, NULL, 1) != 0)
		exit(1);
	exit(execute_cmd(cmd, shell));
}

static int	fork_and_execute(t_cmd *current, t_shell *shell, t_exec_ctx *ctx,
		int pfd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		handle_child(current, shell, ctx, pfd);
	if (pid < 0)
	{
		write_error("minishell: fork failed\n");
		if (ctx->prev_pipe != -1)
			close(ctx->prev_pipe);
		if (current->next)
			(close(pfd[0]), close(pfd[1]));
		return (free(ctx->pids), 1);
	}
	ctx->pids[ctx->pid_count++] = pid;
	if (ctx->prev_pipe != -1)
		close(ctx->prev_pipe);
	if (current->next)
	{
		ctx->prev_pipe = pfd[0];
		close(pfd[1]);
	}
	return (0);
}

static int	init_pipeline_ctx(t_cmd *cmds, t_exec_ctx *ctx)
{
	int	count;

	count = count_commands(cmds);
	ctx->pids = malloc(sizeof(pid_t) * count);
	if (!ctx->pids)
		return (-1);
	ctx->pid_count = 0;
	ctx->prev_pipe = -1;
	return (0);
}

int	execute_pipeline_loop(t_cmd *cmds, t_shell *shell)
{
	t_exec_ctx	ctx;
	int			pipefd[2];
	t_cmd		*current;
	int			count;

	if (init_pipeline_ctx(cmds, &ctx) != 0)
		return (-1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	current = cmds;
	while (current)
	{
		if (current->next && pipe(pipefd) == -1)
		{
			write_error("minishell: pipe failed\n");
			return (free(ctx.pids), setup_signals(), 1);
		}
		if (fork_and_execute(current, shell, &ctx, pipefd) != 0)
			return (free(ctx.pids), setup_signals(), 1);
		current = current->next;
	}
	count = wait_for_children(ctx.pids, ctx.pid_count);
	setup_signals();
	return (free(ctx.pids), count);
}
