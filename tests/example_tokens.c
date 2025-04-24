/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:16 by abronner          #+#    #+#             */
/*   Updated: 2025/04/24 18:35:28 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_token
{
	char	*str;
	int		type;
}	t_token;

t_token	*token_redin(char *str)
{
	t_token	*ret;
	size_t	i;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i] < 2 && str[])
}
