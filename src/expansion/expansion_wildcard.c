/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:25:00 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/03 23:23:36 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**field_split(char *str)
{
	if (!str || !*str || !ft_strchr(str, ' '))
		return (NULL);
	return (ft_split(str, ' '));
}
