/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:49:08 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:49:08 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(char *input, int *i)
{
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
}

static int	was_fully_quoted(char *word)
{
	int	len;

	if (!word || !word[0])
		return (0);
	len = ft_strlen(word);
	return (len >= 2 && ((word[0] == '"' && word[len - 1] == '"')
			|| (word[0] == '\'' && word[len - 1] == '\'')));
}

static char	*process_word_expansion(char *word, t_token_context *ctx,
		int keep_quotes)
{
	char	*expanded_word;

	if (keep_quotes)
		return (word);
	if (should_expand_variable(word))
		expanded_word = expand_and_process_quotes(word, ctx->shell);
	else
		expanded_word = remove_quotes(word);
	free(word);
	return (expanded_word);
}

static void	process_expanded_word(char *expanded_word, char *original_word,
		t_token_context *ctx)
{
	if (expanded_word && *expanded_word)
	{
		if (ft_strchr(expanded_word, ' ') && !was_fully_quoted(original_word)
			&& !ft_strchr(expanded_word, '='))
			handle_field_splitting_main(expanded_word, &ctx->head,
				&ctx->current);
		else
			add_token_to_list(&ctx->head, &ctx->current, expanded_word,
				TOKEN_WORD);
	}
}

int	handle_word_token_main(char *input, int *i, t_token_context *ctx)
{
	char	*word;
	char	*expanded_word;
	char	*original_word;
	int		keep_quotes;

	keep_quotes = (ctx->current && ctx->current->type == TOKEN_HEREDOC);
	word = parse_word(input, i);
	if (!word)
		return (0);
	original_word = ft_strdup(word);
	if (!original_word)
	{
		free(word);
		return (0);
	}
	expanded_word = process_word_expansion(word, ctx, keep_quotes);
	if (!expanded_word)
	{
		free(original_word);
		return (0);
	}
	process_expanded_word(expanded_word, original_word, ctx);
	free(expanded_word);
	free(original_word);
	return (1);
}
