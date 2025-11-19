/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:48:23 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:48:23 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_env_var(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	**add_new_env_var(char **env, const char *key, const char *value)
{
	char	**new_env;
	char	*new_var;
	int		count;
	int		i;

	count = count_env_vars(env);
	new_var = ft_format_env(key, value);
	if (!new_var)
		return (NULL);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (free(new_var), NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	return (new_env);
}

int	set_env_var(t_shell *shell, const char *key, const char *value)
{
	char	**new_env;
	char	*new_val;
	int		idx;

	idx = find_env_var(shell->env, key);
	if (idx != -1)
	{
		new_val = ft_format_env(key, value);
		if (!new_val)
			return (1);
		free(shell->env[idx]);
		shell->env[idx] = new_val;
		return (0);
	}
	new_env = add_new_env_var(shell->env, key, value);
	if (!new_env)
		return (1);
	free(shell->env);
	shell->env = new_env;
	return (0);
}
