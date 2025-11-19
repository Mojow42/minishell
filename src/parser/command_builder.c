/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:49:01 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:49:02 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_arg_to_array(char **args, const char *new_arg)
{
	int		count;
	int		i;
	char	**new_array;

	count = 0;
	if (args)
	{
		while (args[count])
			count++;
	}
	new_array = malloc((count + 2) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_array[i] = args[i];
		i++;
	}
	new_array[count] = ft_strdup(new_arg);
	new_array[count + 1] = NULL;
	free(args);
	return (new_array);
}

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
	}
	return (tokens);
}
