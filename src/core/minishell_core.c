/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:10:00 by vpoelman          #+#    #+#             */
/*   Updated: 2025/11/04 01:27:41 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint_received;

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	setup_signals();
	shell_loop(&shell);
	cleanup_shell(&shell);
	return (shell.status);
}

void	init_shell(t_shell *shell, char **env)
{
	shell->env = copy_env(env);
	if (!shell->env)
	{
		write_error("Error: Failed to copy environment\n");
		exit(1);
	}
	shell->status = 0;
}

void	cleanup_shell(t_shell *shell)
{
	cleanup_str_array(shell->env);
	free(shell->env);
	rl_clear_history();
}

static void	process_input_line(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (has_unclosed_quotes(input))
	{
		write_error("minishell: syntax error: unclosed quotes\n");
		return ;
	}
	add_history(input);
	tokens = tokenize(input, shell);
	if (tokens)
	{
		cmds = parse_tokens(tokens);
		if (cmds)
		{
			shell->status = execute_commands(cmds, shell);
			free_cmds(cmds);
		}
		free_tokens(tokens);
	}
}

void	shell_loop(t_shell *shell)
{
	char	*input;

	g_sigint_received = 0;
	while (1)
	{
		if (g_sigint_received == SIGINT)
		{
			shell->status = 130;
			g_sigint_received = 0;
		}
		input = readline(PROMPT);
		if (!input)
		{
			write_stdout("exit\n");
			break ;
		}
		if (*input)
			process_input_line(input, shell);
		free(input);
	}
}
