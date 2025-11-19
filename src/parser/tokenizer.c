/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:49:18 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:49:20 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *word, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_strdup(word);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token_to_list(t_token **head, t_token **current, char *word,
		int type)
{
	if (!*head)
	{
		*head = create_token(word, type);
		*current = *head;
	}
	else
	{
		(*current)->next = create_token(word, type);
		*current = (*current)->next;
	}
}

void	handle_input_redir(char *input, int *i, t_token **head,
		t_token **current)
{
	if (input[*i + 1] == '<')
	{
		add_token_to_list(head, current, "<<", TOKEN_HEREDOC);
		*i += 2;
	}
	else
	{
		add_token_to_list(head, current, "<", TOKEN_REDIR_IN);
		(*i)++;
	}
}

void	handle_output_redir(char *input, int *i, t_token **head,
		t_token **current)
{
	if (input[*i + 1] == '>')
	{
		add_token_to_list(head, current, ">>", TOKEN_APPEND);
		*i += 2;
	}
	else
	{
		add_token_to_list(head, current, ">", TOKEN_REDIR_OUT);
		(*i)++;
	}
}
