/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:50:10 by abronner          #+#    #+#             */
/*   Updated: 2025/04/26 16:07:16 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "expander.h"

# ifndef RL_PROMPT
#  define RL_PROMPT "minichill $>"
# endif

//	READLINE GENERAL

char	*rl_getline(char *prompt);

//	READLINE APPEND

int		rl_appdel(char **str, char *del);

int		rl_appquo(char **line, char quote);

#endif
