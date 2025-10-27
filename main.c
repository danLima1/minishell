/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:18:07 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/26 22:15:56 by ldos-sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_received = 0;

static void	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*commands;

	tokens = lexer_tokenize(input);
	if (tokens && validate_tokens(tokens))
	{
		commands = parse_tokens(tokens, shell);
		if (commands)
		{
			shell->exit_status = execute_command(commands, shell);
			free_cmd_list(commands);
		}
	}
	free_nodelist(tokens);
}

static void	shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		g_signal_received = 0;
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		process_input(input, shell);
		free(input);
		if (shell->should_exit)
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.env = init_env(envp);
	shell.exit_status = 0;
	shell.should_exit = 0;
	signals_init();
	shell_loop(&shell);
	rl_clear_history();
	free_env(shell.env);
	return (shell.exit_status);
}
