/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:48:56 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:48:58 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	resize_buffer(t_expand_ctx *ctx, size_t j)
{
	size_t	new_size;
	char	*new_res;

	new_size = ctx->buf_size * 2;
	new_res = malloc(new_size);
	if (!new_res)
	{
		write_error("Error: malloc failed in resize_buffer\n");
		exit(1);
	}
	ft_memcpy(new_res, ctx->result, j);
	free(ctx->result);
	ctx->result = new_res;
	ctx->buf_size = new_size;
}

void	expand_var(char *word, t_expand_ctx *ctx, t_shell *shell)
{
	char	*var_name;
	char	*val;
	size_t	start;
	size_t	len;

	start = ctx->i;
	while (word[ctx->i] && (ft_isalnum(word[ctx->i]) || word[ctx->i] == '_'))
		ctx->i++;
	len = ctx->i - start;
	if (len == 0)
		return ;
	var_name = ft_strndup(word + start, len);
	if (!var_name)
		return ;
	val = get_env_value(var_name, shell->env);
	if (val)
	{
		len = ft_strlen(val);
		while (ctx->j + len + 1 >= ctx->buf_size)
			resize_buffer(ctx, ctx->j);
		ft_strlcpy(ctx->result + ctx->j, val, len + 1);
		ctx->j += len;
	}
	free(var_name);
}

char	*expand_variables(char *word, t_shell *shell)
{
	t_expand_ctx	ctx;

	ctx.result = malloc(256);
	if (!ctx.result)
		return (NULL);
	ctx.j = 0;
	ctx.buf_size = 256;
	ctx.i = 0;
	while (word[ctx.i])
	{
		if (word[ctx.i] == '$' && word[ctx.i + 1])
			handle_dollar_expansion(word, &ctx, shell);
		else
		{
			while (ctx.j + 1 >= ctx.buf_size)
				resize_buffer(&ctx, ctx.j);
			ctx.result[ctx.j++] = word[ctx.i++];
		}
	}
	ctx.result[ctx.j] = '\0';
	return (ctx.result);
}
