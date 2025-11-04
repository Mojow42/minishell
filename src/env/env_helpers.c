/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:50:00 by vpoelman          #+#    #+#             */
/*   Updated: 2025/09/26 13:50:00 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env_entries(char **new_env, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			cleanup_str_array(new_env);
			free(new_env);
			return (0);
		}
		i++;
	}
	return (i);
}

char	**create_expanded_env(t_shell *shell, const char *key,
		const char *value)
{
	char	**new_env;
	int		count;
	int		i;

	count = count_env_vars(shell->env);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = copy_env_entries(new_env, shell->env);
	if (i == 0)
		return (NULL);
	new_env[i] = ft_format_env(key, value);
	if (!new_env[i])
	{
		cleanup_str_array(new_env);
		free(new_env);
		return (NULL);
	}
	new_env[i + 1] = NULL;
	return (new_env);
}

int	replace_env_value(char **env_var, const char *key, const char *value)
{
	char	*old_value;

	old_value = *env_var;
	*env_var = ft_format_env(key, value);
	if (!*env_var)
	{
		*env_var = old_value;
		return (1);
	}
	free(old_value);
	return (0);
}

void	compact_env_array(char **env, int remove_idx)
{
	while (env[remove_idx])
	{
		env[remove_idx] = env[remove_idx + 1];
		remove_idx++;
	}
}
