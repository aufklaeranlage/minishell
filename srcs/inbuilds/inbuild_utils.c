/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuild_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:54:48 by abronner          #+#    #+#             */
/*   Updated: 2025/06/23 11:56:03 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

//	Gets a allocated version of getcwd that can be freed and only uses it's
//	length + 1 of memoryspace. achives this by looping to enlargen a dynamically
//	allocated array of characters if a call to getcwd failed because of ERANGE.
//	At the end it calls strdup on the string and frees the probablz longer than
//	needed dynamically allocated buffer used with getcwd.

char	*cd_curdir(void)
{
	char	*ret;
	char	*dir;
	size_t	size;

	size = 32;
	dir = malloc(size * sizeof(*dir));
	while (!getcwd(dir, size))
	{
		if (errno != ERANGE)
			return (NULL);
		size *= 2;
		free(dir);
		dir = malloc(size * sizeof(*dir));
	}
	ret = ft_strdup(dir);
	free(dir);
	return (ret);
}
