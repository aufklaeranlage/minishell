/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:35:23 by abronner          #+#    #+#             */
/*   Updated: 2025/05/23 14:37:58 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2

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
# define HERE_DOC        16			// <<
# define ADD_OUT		 17			// >>
# define SMCLN           18			// ;
# define CLN			 19 		// :
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

# define CMD				31
# define GROUP				32 

# define SHNAME "minichill"

# ifndef RL_PROMPT
#  define RL_PROMPT "minichill $>"
# endif

#endif
