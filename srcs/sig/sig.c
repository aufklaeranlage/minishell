/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:51:40 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/01 23:06:19 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

int g_signal = 0;

void	disable_ctrlc_echo(void)
{
	struct termios	t_attr;

	tcgetattr(STDIN_FILENO, &t_attr);
	t_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t_attr);
}

void	handle_signal(int sign)
{
	g_signal = 128 + sign;
	if (sign == SIGINT || sign == SIGQUIT)
		write(1, "\n", 1);
	if (sign == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_shell_signals(void)
{
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, handle_signal);
	signal(SIGTSTP, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
}

void	setup_child_signals(void)
{
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, SIG_DFL);
}

void	signal_handler_init(void)
{
	if (g_signal)
		g_signal = 0;
	disable_ctrlc_echo();
    setup_shell_signals();
}