/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:49:11 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:49:13 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(char *input, t_shell *shell)
{
	t_token_context	ctx;
	int				i;

	ctx.head = NULL;
	ctx.current = NULL;
	ctx.shell = shell;
	i = 0;
	while (input[i])
	{
		skip_whitespace(input, &i);
		if (!input[i])
			break ;
		if (input[i] == '|')
		{
			add_token_to_list(&ctx.head, &ctx.current, "|", TOKEN_PIPE);
			i++;
		}
		else if (input[i] == '<')
			handle_input_redir(input, &i, &ctx.head, &ctx.current);
		else if (input[i] == '>')
			handle_output_redir(input, &i, &ctx.head, &ctx.current);
		else
			handle_word_token_main(input, &i, &ctx);
	}
	return (ctx.head);
}

t_cmd	*parse_commands(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new_cmd;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		new_cmd = create_new_command();
		if (!new_cmd)
			return (NULL);
		if (!head)
			head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
		tokens = parse_command_tokens(new_cmd, tokens);
		if (!tokens)
			break ;
		if (tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (head);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	if (!validate_syntax(tokens))
		return (NULL);
	return (parse_commands(tokens));
}
