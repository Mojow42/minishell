/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:48:27 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:48:29 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_format_env(const char *key, const char *value)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

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
	i = -1;
	while (env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (cleanup_str_array(new_env), free(new_env), NULL);
	}
	new_env[i] = NULL;
	return (new_env);
}

static void	compact_env_array(char **env, int remove_idx)
{
	while (env[remove_idx])
	{
		env[remove_idx] = env[remove_idx + 1];
		remove_idx++;
	}
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
