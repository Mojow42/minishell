/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:53:29 by vpoelman          #+#    #+#             */
/*   Updated: 2025/10/27 20:47:40 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*add_redir_to_list(t_redir *redirs, t_redir_type type, char *content)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->content = ft_strdup(content);
	new_redir->next = NULL;
	if (!redirs)
		return (new_redir);
	current = redirs;
	while (current->next)
		current = current->next;
	current->next = new_redir;
	return (redirs);
}

t_cmd	*create_new_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_token	*parse_command_tokens(t_cmd *cmd, t_token *tokens)
{
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
		{
			cmd->args = add_arg_to_array(cmd->args, tokens->content);
			tokens = tokens->next;
		}
		else if (is_redir_token(tokens->type))
			tokens = handle_redir_token(cmd, tokens);
		else
			tokens = tokens->next;
	}
	return (tokens);
}
