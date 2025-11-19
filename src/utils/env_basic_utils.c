/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_basic_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:49:47 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:49:47 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_vars(char **env)
{
	int	count;

	count = 0;
	while (env && env[count])
		count++;
	return (count);
}
