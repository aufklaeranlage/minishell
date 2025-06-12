/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/12 10:53:11 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int ft_cd(t_tokens *tokens, t_env *env)
{
	char *dir;

	(void)env;
	dir = tokens->content[1];
	if (chdir(dir) == -1)
		printf("cd: permission denied: %s\n", ft_substr(dir, 0, ft_strlen(dir) - 1));
	return (0);
}
