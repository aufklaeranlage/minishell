/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:30:43 by abronner          #+#    #+#             */
/*   Updated: 2025/06/11 15:22:03 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "errors.h"
# include "defines.h"

# define ENVERRSPC "couldn't create space for new environment"
# define ENVERRINS "couldn't assign variable to environment"

# define ENVSET 0x0
# define ENVEXP 0x1

typedef struct	s_env
{
	t_wrap	*wrap;
	char	**arr;
}	t_env;

typedef struct	s_envnode
{
	char	*var;
	char	*val;
	int		state;
}	t_envnode;

//	ENV INIT

t_env		*env_init(char **env);

void		env_free(t_env *env);

//	ENVNODE INIT

t_envnode	*envnode_init(char *varstr, int state);

void		envnode_free(t_envnode *envnode);

void		envnode_free_wrapper(void *envnode);

//	ENV ARR

int			env_arr_init(t_env *env);

int			env_arr_ins(char *var, char *val, t_env *env);

int			env_arr_rmv(char *varstr, t_env *env);

int			env_arr_rep(char *var, char *val, t_env *env);

//	ENV INSERT

int			env_ins(char *varstr, int exp, t_env *env);

//	ENV REMOVE

int			env_rmv(char *varname, t_env *env);

//	ENV PRINT

int			env_print(t_env *env);

//	ENV UTILS

int			env_splitvarstr(char *varstr, char **var, char **val);

size_t		env_expsize(t_env *env);

t_envnode	*env_contains(char *var, t_env *env);

#endif
