/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:30:43 by abronner          #+#    #+#             */
/*   Updated: 2025/06/10 14:51:55 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"

# define ENVERRSPC "couldn't create space for new environment"
# define ENVERRINS "couldn't assign variable to environment"

# define ENVSET 0x0
# define ENVEXP 0x1

typedef struct	s_env
{
	size_t	size;
	char	**var;
	char	**val;
	int		*state;
	char	**constructed;
}	t_env;

//	ENV INSERT

int		env_insert(char *varstr, int exp, t_env *env);

//	ENV REMOVE

int		env_remove(char *varname, t_env *env);

//	ENV CONSTRUCT

int		env_replaceconstructed(t_env *env);

char	**env_construct(t_env *env);

//	ENV UTILS

int		env_contains(char *var, t_env *env)

int		env_splitvarstr(char *vatstr, char **var, char **val);

char	*env_constructvarstr(char *var, char *val);

size_t	env_expsize(t_env *env);

void	env_free(t_env *env);

#endif
