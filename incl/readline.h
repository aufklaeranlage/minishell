/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:50:10 by abronner          #+#    #+#             */
/*   Updated: 2025/06/06 15:00:10 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "defines.h"
# include "libft.h"
# include "expander.h"
# include "errors.h"

//	READLINE GENERAL

char	*rl_getline(char *prompt);

//	READLINE APPEND

int		rl_appdel(char **line, char *del, char **ret);

int		rl_appquo(char **line, char quote);

//	HERE DOC

char	*rl_heredoc(char *del);

#endif
