/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg_handlers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:47:45 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/19 02:47:47 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exported_vars(t_shell *shell, int j)
{
	while (shell->env[j])
	{
		write_stdout("declare -x ");
		write_stdout(shell->env[j]);
		write_stdout("\n");
		j++;
	}
}

static void	print_invalid_identifier_error(const char *key)
{
	write_error("minishell: export: `");
	write_error(key);
	write_error("': not a valid identifier\n");
}

int	process_export_arg(char *arg, t_shell *shell)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		return (handle_export_with_value(arg, eq, shell));
	return (handle_export_without_value(arg));
}

int	handle_export_with_value(char *arg, char *eq, t_shell *shell)
{
	char	*key;
	char	*value;

	key = ft_strndup(arg, eq - arg);
	if (!key)
		return (1);
	value = ft_strdup(eq + 1);
	if (!value)
	{
		free(key);
		return (1);
	}
	if (!is_valid_identifier(key))
	{
		print_invalid_identifier_error(key);
		free(key);
		free(value);
		return (1);
	}
	set_env_var(shell, key, value);
	free(key);
	free(value);
	return (0);
}

int	handle_export_without_value(char *arg)
{
	if (!is_valid_identifier(arg))
	{
		print_invalid_identifier_error(arg);
		return (1);
	}
	return (0);
}
