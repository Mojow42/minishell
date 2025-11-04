/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable_handlers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:55:09 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/03 23:23:34 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_quote_char(char *word, t_expand_ctx *ctx,
		int *in_single, int *in_double)
{
	if (word[ctx->i] == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (word[ctx->i] == '"' && !(*in_single))
		*in_double = !(*in_double);
	ctx->i++;
}

static void	process_char_in_expansion(char *word, t_expand_ctx *ctx,
		t_quote_state *state, t_shell *shell)
{
	if ((word[ctx->i] == '\'' || word[ctx->i] == '"'))
		process_quote_char(word, ctx, &state->in_single, &state->in_double);
	else if (word[ctx->i] == '$' && word[ctx->i + 1] && !state->in_single)
		handle_dollar_expansion(word, ctx, shell);
	else
	{
		while (ctx->j + 1 >= ctx->buf_size)
			resize_buffer(ctx, ctx->j);
		ctx->result[ctx->j++] = word[ctx->i++];
	}
}

char	*expand_variables_with_quotes(char *word, t_shell *shell)
{
	t_expand_ctx	ctx;
	t_quote_state	state;

	ctx.result = malloc(256);
	if (!ctx.result)
		return (NULL);
	ctx.j = 0;
	ctx.buf_size = 256;
	ctx.i = 0;
	state.in_single = 0;
	state.in_double = 0;
	while (word[ctx.i])
		process_char_in_expansion(word, &ctx, &state, shell);
	ctx.result[ctx.j] = '\0';
	return (ctx.result);
}
