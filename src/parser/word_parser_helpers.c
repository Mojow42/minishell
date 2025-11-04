/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:03:13 by vpoelman          #+#    #+#             */
/*   Updated: 2025/10/18 00:02:59 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quote_start(char *word, int *i, int *in_quote,
		char *quote_char)
{
	*quote_char = word[*i];
	*in_quote = 1;
	(*i)++;
}

static void	handle_quote_end(int *i, int *in_quote, char *quote_char)
{
	*in_quote = 0;
	*quote_char = 0;
	(*i)++;
}

static void	process_quotes(char *word, char *result)
{
	int		i;
	int		j;
	int		in_quote;
	char	quote_char;

	i = 0;
	j = 0;
	in_quote = 0;
	quote_char = 0;
	while (word[i])
	{
		if (!in_quote && (word[i] == '\'' || word[i] == '"'))
			handle_quote_start(word, &i, &in_quote, &quote_char);
		else if (in_quote && word[i] == quote_char)
			handle_quote_end(&i, &in_quote, &quote_char);
		else
			result[j++] = word[i++];
	}
	result[j] = '\0';
}

char	*remove_quotes(char *word)
{
	int		len;
	char	*result;

	len = ft_strlen(word);
	if (len < 2)
		return (ft_strdup(word));
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	process_quotes(word, result);
	return (result);
}

int	should_expand_variable(char *word)
{
	int	i;
	int	in_single_quotes;

	i = 0;
	in_single_quotes = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (word[i] == '$' && !in_single_quotes)
			return (1);
		i++;
	}
	return (0);
}
