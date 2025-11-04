/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:53:24 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/03 23:23:53 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_arg_to_array(char **args, const char *new_arg)
{
	int		count;
	int		i;
	char	**new_array;

	count = 0;
	if (args)
	{
		while (args[count])
			count++;
	}
	new_array = malloc((count + 2) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_array[i] = args[i];
		i++;
	}
	new_array[count] = ft_strdup(new_arg);
	new_array[count + 1] = NULL;
	free(args);
	return (new_array);
}
