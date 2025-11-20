/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable_handlers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:48:52 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/20 00:58:11 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar_expansion(char *word, t_expand_ctx *ctx, t_shell *shell)
{
	char	*val;
	size_t	len;

	ctx->i++;
	if (word[ctx->i] == '?')
	{
		val = ft_itoa(shell->status);
		len = ft_strlen(val);
		while (ctx->j + len >= ctx->buf_size)
			resize_buffer(ctx, ctx->j);
		ft_strlcpy(ctx->result + ctx->j, val, len + 1);
		ctx->j += len;
		free(val);
		ctx->i++;
	}
	else if (ft_isalnum(word[ctx->i]) || word[ctx->i] == '_')
		expand_var(word, ctx, shell);
	else
	{
		while (ctx->j + 1 >= ctx->buf_size)
			resize_buffer(ctx, ctx->j);
		ctx->result[ctx->j++] = '$';
	}
}

static void	handle_single_quotes(char *word, t_expand_ctx *ctx)
{
	ctx->i++;
	while (word[ctx->i] && word[ctx->i] != '\'')
	{
		while (ctx->j + 1 >= ctx->buf_size)
			resize_buffer(ctx, ctx->j);
		ctx->result[ctx->j++] = word[ctx->i++];
	}
	if (word[ctx->i] == '\'')
		ctx->i++;
}

static void	process_char_in_expansion(char *word, t_expand_ctx *ctx,
		t_shell *shell)
{
	int	in_dquote;

	in_dquote = 0;
	while (word[ctx->i])
	{
		if (word[ctx->i] == '\'' && !in_dquote)
			handle_single_quotes(word, ctx);
		else if (word[ctx->i] == '"')
		{
			in_dquote = !in_dquote;
			ctx->i++;
		}
		else if (word[ctx->i] == '$' && word[ctx->i + 1])
			handle_dollar_expansion(word, ctx, shell);
		else
		{
			while (ctx->j + 1 >= ctx->buf_size)
				resize_buffer(ctx, ctx->j);
			ctx->result[ctx->j++] = word[ctx->i++];
		}
	}
}

char	*expand_and_process_quotes(char *word, t_shell *shell)
{
	t_expand_ctx	ctx;

	ctx.result = malloc(256);
	if (!ctx.result)
		return (NULL);
	ctx.j = 0;
	ctx.buf_size = 256;
	ctx.i = 0;
	process_char_in_expansion(word, &ctx, shell);
	ctx.result[ctx.j] = '\0';
	return (ctx.result);
}
