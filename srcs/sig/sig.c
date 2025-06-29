/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:51:40 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/30 00:11:12 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

int	g_signal;

void	disable_ctrlc_echo(void)
{
	struct termios	t_attr;

	tcgetattr(STDIN_FILENO, &t_attr);
	t_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t_attr);
}

void	handle_signal(int sign)
{
	g_signal = sign + 128;
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		if ((isatty(STDIN_FILENO) && rl_readline_state & RL_STATE_READCMD))
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else if (sign == SIGQUIT)
	{
		if ((isatty(STDIN_FILENO) && rl_readline_state & RL_STATE_READCMD))
			rl_redisplay();
		else
			write(1, "Quit (core dumped)\n", 19);
	}
}

/**
 * @brief Allow correctly terminate running procces
 * @param sign get signal as input
 */
void	handle_exec_signal(int sign)
{
	g_signal = 128 + sign;
	if (sign == SIGINT)
		write(1, "\n", 1);
	else if (sign == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

/**
 * @brief Initialisation at program start
 */
void	signal_handler_init(void)
{
	g_signal = 0;
	disable_ctrlc_echo();
	setup_signals();
}
