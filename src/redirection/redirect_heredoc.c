/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:15:00 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/04 02:10:00 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*clean_delimiter(char *delimiter, int *quoted)
{
	size_t	len;

	len = ft_strlen(delimiter);
	*quoted = ((delimiter[0] == '\'' && delimiter[len - 1] == '\'')
			|| (delimiter[0] == '"' && delimiter[len - 1] == '"'));
	if (*quoted)
		return (ft_strndup(delimiter + 1, len - 2));
	return (ft_strdup(delimiter));
}

void	process_heredoc_line(char *line, int fd, int quoted, t_shell *shell)
{
	char	*expanded;
	char	*tmp;

	if (!quoted)
	{
		expanded = expand_variables(line, shell);
		free(line);
		line = expanded;
	}
	tmp = ft_strjoin(line, "\n");
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
	free(line);
}

static int	handle_sigint_in_heredoc(t_shell *shell)
{
	if (g_sigint_received == SIGINT)
	{
		if (shell)
			shell->status = 130;
		g_sigint_received = 0;
		return (-1);
	}
	return (0);
}

int	read_heredoc_loop(int fd, char *delim, int quoted, t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (handle_sigint_in_heredoc(shell) == -1)
				return (-1);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(line, fd, quoted, shell);
	}
	return (0);
}

int	handle_heredoc(char *delimiter, t_shell *shell)
{
	int		fd[2];
	char	*delim;
	int		quoted;
	int		result;

	if (pipe(fd) == -1)
		return (-1);
	delim = clean_delimiter(delimiter, &quoted);
	result = read_heredoc_loop(fd[1], delim, quoted, shell);
	close(fd[1]);
	free(delim);
	if (result == -1)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}
