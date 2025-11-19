/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:49:36 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:49:36 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_and_dup(char *file, int flags, int target_fd, int mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd < 0)
	{
		print_errno("minishell", file);
		return (-1);
	}
	if (dup2(fd, target_fd) < 0)
	{
		print_errno("minishell", "dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static void	handle_redir_error(t_shell *shell, int child_mode)
{
	if (child_mode)
	{
		if (g_sigint_received == SIGINT)
			exit(130);
		exit(1);
	}
	if (g_sigint_received == SIGINT && shell)
		shell->status = 130;
	else if (shell)
		shell->status = 1;
}

static int	handle_heredoc_redir(t_redir *redir, t_shell *shell, int child_mode)
{
	int	fd;

	fd = handle_heredoc(redir->content, shell);
	if (fd == -1)
		return (handle_redir_error(shell, child_mode), 1);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		print_errno("minishell", "dup2");
		close(fd);
		return (handle_redir_error(shell, child_mode), 1);
	}
	close(fd);
	return (0);
}

static int	process_single_redir(t_redir *redir, t_shell *shell, int child_mode)
{
	int	result;
	int	flags;

	result = 0;
	if (redir->type == R_IN)
		result = open_and_dup(redir->content, O_RDONLY, STDIN_FILENO, 0);
	else if (redir->type == R_OUT || redir->type == R_APP)
	{
		flags = O_WRONLY | O_CREAT;
		if (redir->type == R_OUT)
			flags |= O_TRUNC;
		else
			flags |= O_APPEND;
		result = open_and_dup(redir->content, flags, STDOUT_FILENO, 0644);
	}
	else if (redir->type == R_HEREDOC)
		return (handle_heredoc_redir(redir, shell, child_mode));
	if (result != 0)
		return (handle_redir_error(shell, child_mode), 1);
	return (0);
}

int	process_redirections(t_cmd *cmd, t_shell *shell, int child_mode)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (process_single_redir(redir, shell, child_mode) != 0)
			return (1);
		redir = redir->next;
	}
	return (0);
}
