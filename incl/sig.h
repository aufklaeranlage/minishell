/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:51:40 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/05 14:41:12 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include "minichill.h"
# include <signal.h>
# include <termios.h>

# define INPUTING		100110
# define EXECUTION      100111

extern int	g_signal;

void	disable_ctrlc_echo(void);

void	handle_signal(int sign);

void	setup_signals(int launch_type);

void	signal_handler_init(void);

#endif