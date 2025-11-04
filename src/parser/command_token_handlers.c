/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_token_handlers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:53:48 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/03 23:23:56 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(int token_type)
{
	return (token_type == TOKEN_REDIR_IN || token_type == TOKEN_REDIR_OUT
		|| token_type == TOKEN_APPEND || token_type == TOKEN_HEREDOC);
}

static t_redir_type	get_redir_type(int token_type)
{
	if (token_type == TOKEN_REDIR_OUT)
		return (R_OUT);
	if (token_type == TOKEN_APPEND)
		return (R_APP);
	if (token_type == TOKEN_HEREDOC)
		return (R_HEREDOC);
	return (R_IN);
}

t_token	*handle_redir_token(t_cmd *cmd, t_token *tokens)
{
	t_redir_type	type;

	type = get_redir_type(tokens->type);
	tokens = tokens->next;
	if (tokens)
	{
		cmd->redirs = add_redir_to_list(cmd->redirs, type, tokens->content);
		tokens = tokens->next;
	}
	return (tokens);
}
