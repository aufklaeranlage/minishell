/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/26 14:39:16 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int ft_cd(t_tokens *tokens, char **env)
{
	char *dir;

	(void)env;
	dir = tokens->content[1];
	if (chdir(dir) == -1)
		printf("cd: permission denied: %s\n", ft_substr(dir, 0, ft_strlen(dir) - 1));
	return (0);
}
