/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:35:23 by abronner          #+#    #+#             */
/*   Updated: 2025/06/25 18:16:31 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define HD_PROMPT "> "

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define STR		     3
# define EXPAND_STR      4
# define INCMD_ECHO      5
# define INCMD_CD        6
# define INCMD_PWD       7
# define INCMD_EXIT      8
# define INCMD_EXPORT    9
# define INCMD_ENV       10
# define INCMD_UNSET     11
# define INCMD_ASSIGN
# define STD_CMD		 12			// all comands from PC-s $PATH
# define FLAG            13  		// -l --long and etc.
# define RED_IN          14  		// <
# define RED_OUT         15  		// >
# define HERE_DOC        16			// <<
# define ADD_OUT		 17			// >>
# define SMCLN           18			// ;
// # define CLN			 19 		// :
# define DQ              20 		// "
# define SQ              21 		// '
# define NEW_LINE        22 		// \n
# define BIN_AND         23  		// &
# define PIPE            24 		// |
# define AND             25 		// &&
# define OR              26 		// ||
# define TEXT            27
# define O_BR            28			// (
# define C_BR            29			// )
# define WILDCARD        30
# define ASSIGNMENT      31

# define CMD             100
# define SHELL           101
# define PIPELINE        102		// Currently unused

# define SHNAME "minichill"

# define PWDNDT "Error: Directory could not be determined!"

# ifndef RL_PROMPT
#  define RL_PROMPT "minichill"
# endif

# include <stdlib.h>

typedef struct s_group	t_group;

typedef struct s_tokens	t_tokens;

typedef struct s_shell	t_shell;
typedef struct s_tokens
{
	size_t	size;
	int		*type;
	char	**content;
}	t_tokens;

typedef struct s_group
{
	int			data_type;
	int			exec_type;
	t_tokens	*red;
	void		*data;
	t_group		*next;
	t_group		*parrent;
	t_shell		*shell;
}	t_group;

#endif
