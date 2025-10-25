/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:18:07 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/25 14:32:10 by ldos_sa2         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)argc;
	(void)argv;
	shell.env = init_env(envp);
	shell.exit_status = 0;
	signals_init();
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
		process_input(input, &shell);
		free(input);
	}
	free_env(shell.env);
	return (shell.exit_status);
}
