/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:49:15 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:51:25 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_pipe_syntax(t_token *tokens, t_token *check)
{
	if (check->type == TOKEN_PIPE)
	{
		if (check == tokens || !check->next || check->next->type == TOKEN_PIPE)
		{
			write_error("minishell: syntax error near unexpected token `|'\n");
			return (0);
		}
	}
	return (1);
}

static int	validate_redirect_syntax(t_token *check)
{
	if (check->type == TOKEN_REDIR_IN || check->type == TOKEN_REDIR_OUT
		|| check->type == TOKEN_APPEND || check->type == TOKEN_HEREDOC)
	{
		if (!check->next || check->next->type != TOKEN_WORD)
		{
			write_error("minishell: syntax error near unexpected token "
				"`newline'\n");
			return (0);
		}
	}
	return (1);
}

int	has_unclosed_quotes(const char *input)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (input[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*check;

	check = tokens;
	while (check)
	{
		if (!validate_pipe_syntax(tokens, check))
			return (0);
		if (!validate_redirect_syntax(check))
			return (0);
		check = check->next;
	}
	return (1);
}
