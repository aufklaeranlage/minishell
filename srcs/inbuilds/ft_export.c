/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/26 14:46:38 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

/**
 * Need to read how does it works
 */
int	ft_export(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		printf("%s\n", env[i]);
	return (0);
}
