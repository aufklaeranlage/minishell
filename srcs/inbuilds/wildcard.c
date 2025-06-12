/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/12 11:10:07 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int	is_wildcard(char *str)
{
	size_t i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (WILDCARD);
		i++;
	}
	return (0);
}

/**
 * 1. Copy first part before wildcart
 *      if it wat '/' execve("/bin/ls", "/")
 *      else execve("/bin/ls", "/")
 * 2. then copy rest before "*" sign
 *      if (match in set from 1) new_set.append;
 *      else --> skip
 * 3. then check is it mutch with part after "*" sign
 *      if (yes) --> seve in final output
 *      else --> go next
 * 4. if final output is empty
 *      return (zsh: no matches found: ger*ta)
 * Also need to check this things every time after execve()
 */
char *expand_wildcard(char *str, t_env *env)
{
	char *before;

	if (!is_wildcard(str))
		return str;
	before = ft_substr(str, 0, ft_strchr(str, '*') - str);
	if (!before)
		return (NULL);
	//if (before[0] == '/')
	char *argv_list[] = {"/bin/ls", "-l", str, NULL};
	execve("/bin/ls", argv_list, env->arr);
	
	return (0);
}
