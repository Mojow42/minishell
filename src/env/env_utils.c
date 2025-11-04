/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:54:06 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/02 19:52:38 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *name, char **env)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	**copy_env(char **env)
{
	char	**new_env;
	int		count;
	int		i;

	if (!env)
		return (NULL);
	count = count_env_vars(env);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = copy_env_entries(new_env, env);
	if (i == 0)
		return (NULL);
	new_env[i] = NULL;
	return (new_env);
}

int	unset_env_var(t_shell *shell, const char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& shell->env[i][key_len] == '=')
		{
			free(shell->env[i]);
			compact_env_array(shell->env, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	update_existing_env_var(t_shell *shell, const char *key,
		const char *value)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& shell->env[i][key_len] == '=')
			return (replace_env_value(&shell->env[i], key, value));
		i++;
	}
	return (-1);
}

int	set_env_var(t_shell *shell, const char *key, const char *value)
{
	char	**new_env;
	int		result;

	result = update_existing_env_var(shell, key, value);
	if (result != -1)
		return (result);
	new_env = create_expanded_env(shell, key, value);
	if (!new_env)
		return (1);
	cleanup_str_array(shell->env);
	free(shell->env);
	shell->env = new_env;
	return (0);
}
