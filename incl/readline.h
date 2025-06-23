/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:50:10 by abronner          #+#    #+#             */
/*   Updated: 2025/06/23 12:15:17 by abronner         ###   ########.fr       */
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

char	*rl_hdapp(const char *del, char **line);

//	HERE DOC

char	*rl_heredoc(const char *del);

#endif
