/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:48:13 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/26 22:16:21 by ldos-sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals_handle_sigquit(int sig)
{
	(void)sig;
}

void	signals_init(void)
{
	signal(SIGINT, signals_handle_sigint);
	signal(SIGQUIT, signals_handle_sigquit);
}
