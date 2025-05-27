/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/26 15:35:25 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int	ft_pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 1024);
	if (!buf)
	{
		printf("Error: Directory could not be determined!\n");
		return (1);
	}
	printf("%s\n", buf);
	return (0);
}
