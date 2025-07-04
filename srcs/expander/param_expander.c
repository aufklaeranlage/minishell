/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:05:41 by abronner          #+#    #+#             */
/*   Updated: 2025/06/30 13:44:14 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

//	Expands all $PARAMETERS found in s that aren't encapsulated by single
//	quotes (').

char	**param_expander(const char *s, size_t total, size_t depth, t_env *env)
{
	char	**ret;
	char	*val;
	size_t	varlen;
	size_t	vallen;

	val = env_getval(s + 1, env);
	varlen = 1;
	while (s[varlen] && !ft_strchr(VAR_DEL, s[varlen]))
		++varlen;
	vallen = varlen;
	if (val)
		vallen = ft_strlen(val);
	else
		val = (char *)s;
	ret = expander_main(s + varlen, total + vallen, depth, env);
	if (ret && ret[depth])
		ft_strncpy(ret[depth] + total, val, vallen);
	return (ret);
}
