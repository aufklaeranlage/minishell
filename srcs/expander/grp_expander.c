/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grp_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:05:24 by abronner          #+#    #+#             */
/*   Updated: 2025/06/30 09:09:19 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "env.h"
#include "tokenisation.h"

//	BASH does expansion like this
//
//	1.	BRACE EXPANSION:	{str1, str2, [...]}
//		Not Needed
//	2.	TILDE EXPANSION:	'~' = $HOME '~+' = $PWD '~-' = $OLDPWD
//		Already done just needs to be put in the right spot.
//	3.	SHELL PARAMETER EXPANSION:	Anything $
//		Already done
//	4.	COMMAND SUBSTITUTION:	$(command)
//		Not needed
//	5.	ARITHMETIC SUBSTITUTION:	$(( expression ))
//		Not needed
//	6.	PROCESS SUBSTITUTION:	<(list) >(list)
//		Not needed
//	7.	WORD SPLITTING:			split everything except quoted strings
//		will be implemented
//	8.	FILENAME EXPANSION:		*
//		wildcard

int	grp_expand()
{
	size_t	i;
	char	**newcont;
	char	*str;

	tok = (t_tokens *)grp->data;
	i = 0;
	while (i < tok->size)
	{
		str = tilde_expander(tok->content[i], env);
		if (!str)
			return (ft_splitfree(newcont), 1);
		if (split_expander(str, &newcont))
			return (ft_splitfree(newcont), free(str), 1);
		++i;
	}
	tok = (t_tokens *)grp->red;
	i = 0;
	while (i < tok->size)
	{
		str = tilde_expander(tok->content[i], env);
		if (!str)
			return (ft_splitfree(newcont), 1);
		if (split_expander(str, &newcont))
			return (ft_splitfree(newcont), free(str), 1);
		++i;
	}
}
