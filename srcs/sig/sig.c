/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:51:40 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/05 15:19:51 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

int	g_signal;

// Need to think does its stuf needed or not, 
// maybe this were done just fore correct work on MacOS
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
		if (!((isatty(STDIN_FILENO) && rl_readline_state & RL_STATE_READCMD)))
			write(1, "Quit (core dumped)\n", 19);
	}
}

/**
 * @brief Set the up signals object
 * There is 2 types: 
 * @param launch_type (INPUTING) starts before execution
 * Ignore Ctrl+\
 * @param launch_type (EXECUTION) starts before execution
 * its handle Ctrl+\
 */
void	setup_signals(int launch_type)
{
	signal(SIGINT, handle_signal);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	if (launch_type == INPUTING)
		signal(SIGQUIT, SIG_IGN);
	else if (launch_type == EXECUTION)
		signal(SIGQUIT, handle_signal);
}

/**
 * @brief Initialisation at program start
 */
void	signal_handler_init(void)
{
	g_signal = 0;
	disable_ctrlc_echo();
	setup_signals(INPUTING);
}
