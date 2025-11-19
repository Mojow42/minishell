/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:49:58 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:50:00 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_in_paths(char *cmd, char **paths)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*handle_absolute_path(char *cmd)
{
	struct stat	st;

	if (access(cmd, F_OK) == 0)
	{
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		{
			errno = EISDIR;
			return (NULL);
		}
		return (ft_strdup(cmd));
	}
	return (NULL);
}

char	*find_executable(char *cmd, char **env)
{
	char	*path_env;
	char	**paths;
	char	*result;

	if (!cmd || !env)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (handle_absolute_path(cmd));
	path_env = get_env_value("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(cmd, paths);
	cleanup_str_array(paths);
	free(paths);
	return (result);
}
