/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:24:16 by akuzmin           #+#    #+#             */
/*   Updated: 2025/04/27 14:25:49 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISATION_H
# define TOKENISATION_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

# define STR		     3			// 'some string'
# define EXPAND_STR      4			// "Some string $PATH etc."
# define INCMD_ECHO      5
# define INCMD_CD        6
# define INCMD_PWD       7
# define INCMD_EXIT      8
# define INCMD_EXPORT    9
# define INCMD_ENV       10
# define INCMD_UNSET     11
# define STD_CMD		 12			// all comands from PC-s $PATH
# define FLAG            13  		// -l --long and etc.
# define RED_IN          14  		// <
# define RED_OUT         15  		// >
# define BIN_AND         16  		// &
# define PIPE            17 		// |
# define SMCLN           18			// ;
# define CLN			 19 		// :
# define DQ              20 		// "
# define SQ              21 		// '
# define NEW_LINE        22 		// \n
# define HERE_DOC        23			// <<
# define ADD_OUT		 24			// >>
# define AND             25 		// &&
# define OR              26 		// ||
# define TEXT            27
# define O_BR            28			// (
# define C_BR            29 		// )

typedef struct s_token
{
	size_t	size;
	int		*type;
	char	**content;
}	t_token;

// Utils
int		is_falg(char *str);
int		cmd_specifier(char *str);
char	*minishell_getexec(char *execname, char **env);
int		specifier_two(char *str);
int		specifier_one(char *str);

// Modules
t_wrap	*convert_str(char *str);
char	*convert_subfunction(char *str, t_wrap *list);

#endif
