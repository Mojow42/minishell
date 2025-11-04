/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_execve_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:00:00 by vpoelman          #+#    #+#             */
/*   Updated: 2025/10/15 00:00:00 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**build_sh_argv(char *path, char **args)
{
	char	**argv_sh;
	int		argc;
	int		i;

	argc = 0;
	while (args[argc])
		argc++;
	argv_sh = malloc(sizeof(char *) * (argc + 2));
	if (!argv_sh)
		return (NULL);
	argv_sh[0] = "/bin/sh";
	argv_sh[1] = path;
	i = 1;
	while (i < argc)
	{
		argv_sh[i + 1] = args[i];
		i++;
	}
	argv_sh[argc + 1] = NULL;
	return (argv_sh);
}

static int	handle_sh_exec_error(void)
{
	if (errno == ENOENT)
	{
		print_cmd_error("/bin/sh", "command not found");
		return (127);
	}
	print_cmd_errno("/bin/sh");
	return (126);
}

int	handle_enoexec_error(char *path, char **args, char **env)
{
	char	**argv_sh;

	argv_sh = build_sh_argv(path, args);
	if (!argv_sh)
		return (126);
	execve("/bin/sh", argv_sh, env);
	free(argv_sh);
	return (handle_sh_exec_error());
}
