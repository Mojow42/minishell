/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:03:16 by vpoelman          #+#    #+#             */
/*   Updated: 2025/10/17 23:40:27 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_special_char(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

char	*parse_word(char *input, int *i)
{
	int		start;
	int		len;
	int		in_quote;
	char	quote_char;

	start = *i;
	in_quote = 0;
	quote_char = 0;
	while (input[*i] && (in_quote || !is_special_char(input[*i])))
	{
		if (!in_quote && (input[*i] == '\'' || input[*i] == '"'))
		{
			quote_char = input[*i];
			in_quote = 1;
		}
		else if (in_quote && input[*i] == quote_char)
		{
			in_quote = 0;
			quote_char = 0;
		}
		(*i)++;
	}
	len = *i - start;
	return (ft_strndup(input + start, len));
}

void	handle_field_splitting_main(char *expanded_word, t_token **head,
		t_token **current)
{
	char	**fields;
	int		i;

	fields = field_split(expanded_word);
	if (fields && fields[0])
	{
		i = 0;
		while (fields[i])
		{
			if (fields[i] && *fields[i])
				add_token_to_list(head, current, fields[i], TOKEN_WORD);
			free(fields[i]);
			i++;
		}
		free(fields);
	}
	else
	{
		if (expanded_word && *expanded_word)
			add_token_to_list(head, current, expanded_word, TOKEN_WORD);
		if (fields)
			free(fields);
	}
}
