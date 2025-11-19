/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable_handlers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:48:52 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:48:54 by vpoelman         ###   ########.fr       */
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

static void	process_char_in_expansion(char *word, t_expand_ctx *ctx,
		t_shell *shell)
{
	while (word[ctx->i])
	{
		if (word[ctx->i] == '"')
			ctx->i++;
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

char	*expand_variables_with_quotes(char *word, t_shell *shell)
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
