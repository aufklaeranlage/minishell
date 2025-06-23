/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:51:40 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/24 00:11:21 by akuzmin          ###   ########.fr       */
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
	write(1, "\n", 1);
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		if (isatty(STDIN_FILENO))
		{
			// rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else if (sign == SIGQUIT)
	{
		if (isatty(STDIN_FILENO))
			rl_redisplay();
	}
}

/**
 * @brief Allow correctly terminate running procces
 * @param sign get signal as input
 */
void	handle_exec_signal(int sign)
{
	if (sign == SIGINT)
	{
		g_signal = 128 + sign;
		write(1, "\n", 1);
	}
	else if (sign == SIGQUIT)
	{
		g_signal = 128 + sign;
		write(1, "Quit (core dumped)\n", 19);
	}
}
//
// /**
//  * @brief Run before execution 
//  * and right after comand was completed.
//  */
// void	setup_shell_signals(void)
// {
// 	signal(SIGINT, handle_signal);
// 	signal(SIGQUIT, handle_signal);
// 	signal(SIGTSTP, SIG_IGN);
// 	signal(SIGTERM, SIG_IGN);
// }
//
// /**
//  * @brief Run right after fork in child process
//  */
// void	setup_child_signals(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }
//
// /**
//  * @brief Run before execution of command
//  */
// void setup_exec_signals(void)
// {
// 	signal(SIGINT, handle_exec_signal);
// 	signal(SIGQUIT, handle_exec_signal);
// }

void	setup_signals(int type)
{
	if (type == 1)
	{
		signal(SIGINT, handle_exec_signal);
		signal(SIGQUIT, handle_exec_signal);
	}
	if (type == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (type == 3)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
	}
}

/**
 * @brief Initialisation at program start
 */
void	signal_handler_init(void)
{
	if (g_signal)
		g_signal = 0;
	disable_ctrlc_echo();
	setup_shell_signals();
}
