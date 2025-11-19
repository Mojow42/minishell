/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:49:41 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:49:42 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free_single_cmd(tmp);
	}
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_single_cmd(t_cmd *cmd)
{
	if (cmd->args)
	{
		cleanup_str_array(cmd->args);
		free(cmd->args);
	}
	if (cmd->redirs)
		free_redirs(cmd->redirs);
	free(cmd);
}
