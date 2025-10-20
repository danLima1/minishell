/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:18:07 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/06 21:50:44 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_received = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;
	t_token	*tokens;
	t_cmd	*commands;

	(void)argc;
	(void)argv;
	shell.env = init_env(envp);
	shell.last_exit_status = 0;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = lexer_tokenize(input);
		if (tokens && validate_tokens(tokens))
		{
			commands = parse_tokens(tokens);
			if (commands)
			{
				shell.last_exit_status = execute_command(commands, &shell);
				free_cmd_list(commands);
			}
		}
		free_nodelist(tokens);
		free(input);
	}
	free_env(shell.env);
	return (shell.last_exit_status);
}
