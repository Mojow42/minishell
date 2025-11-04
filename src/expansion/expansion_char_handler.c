/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_char_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:54:44 by vpoelman          #+#    #+#             */
/*   Updated: 2025/10/18 01:06:47 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar_expansion(char *clean_word, t_expand_ctx *ctx,
		t_shell *shell)
{
	char	*val;
	size_t	len;

	ctx->i++;
	if (clean_word[ctx->i] == '?')
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
	else if (ft_isalnum(clean_word[ctx->i]) || clean_word[ctx->i] == '_')
		expand_var(clean_word, ctx, shell);
	else
	{
		while (ctx->j + 1 >= ctx->buf_size)
			resize_buffer(ctx, ctx->j);
		ctx->result[ctx->j++] = '$';
	}
}
