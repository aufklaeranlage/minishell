/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:24:16 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/20 15:22:34 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISATION_H
# define TOKENISATION_H

////
#include <stdio.h>
//////

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

typedef struct s_group t_group;
typedef struct s_token
{
	int		type;
	char	*cont;
}	t_token;

typedef struct s_tokens
{
	size_t	size;
	t_token *data;
}	t_tokens;

typedef struct s_group
{
	int			data_type;
	int			exec_type;
	t_token		*red;
	void		*data;
	t_group		*next;
	t_group		*parrent;
}	t_group;

// Utils
size_t		delimiter(int *d_type, t_tokens *list, size_t i);
int			set_type(char *tmp, char **env);
void		*del_tokens(t_tokens *out);
int			is_falg(char *str);
int			cmd_specifier(char *str);
char		*minishell_getexec(char *execname, char **env);
int			specifier_two(char *str);
int			specifier_one(char *str);

// Modules
t_wrap		*convert_str(char *str);
char		*convert_subfunction(char *str, t_wrap *list);

// Tokenisation helpers
t_tokens	*subtoken(t_tokens *list, size_t start, size_t end);
size_t		delimiter(int *d_type, t_tokens	*list, size_t i);
void		redirection(t_group *group, t_tokens	*list, size_t i);
void		lst_to_tokens(t_tokens *out, t_wrap *list, char **env);

// GROUPS HANDLE CMD
t_group		*handle_command_group(t_tokens *list, t_group *parrent, size_t i);

// GROUPS HANDLE CMD UTILS
int			is_valid_cmd_position(t_tokens *list, size_t i);
t_group		*init_cmd_group(t_tokens *list, t_group *parrent, size_t i);
t_tokens	*get_command_tokens(t_tokens *list, size_t i, size_t j);
size_t		count_valid_tokens(t_tokens *sub);
t_tokens	*filter_tokens(size_t valid_count, t_group *group, t_tokens *sub);

// GROUPS HANDLE CMD UTILS 2
int			copy_valid_tokens(t_tokens *filtered, t_tokens *sub, t_group *group);
void		cleanup_filtered_tokens(t_tokens *fltrd, t_tokens *sub, t_group *group);
void		setup_next_group(t_group *group, t_tokens *list, size_t j, t_group *pnt);
t_group		*prepare_group(t_tokens *list, t_group *pnt, size_t i, size_t *j_out);
t_tokens	*proc_cmd_tokens(t_group *group, t_tokens *list, size_t i, size_t j);

// HANDLE BRACKETS
t_group		*handle_bracket_group(t_tokens *list, size_t i, size_t *j_out);
int			process_bracket_content(t_group *group, t_tokens *list, size_t i, size_t j);
int			handle_bracket_redirection(t_group *group, t_tokens *list, size_t j);
void		free_redirection(t_token *red);

// Create groups
t_group		*create_groups(t_tokens *list, t_group *parrent, size_t i, size_t j);

// Split to execution commands list
t_group		*create_execution_list(char *str, char **env);

#endif
