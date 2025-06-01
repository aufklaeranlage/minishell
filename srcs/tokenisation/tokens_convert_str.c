/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_convert_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/01 23:19:46 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

static t_wrap	*init_token_list(void)
{
	t_wrap	*list;

	list = malloc(sizeof(t_wrap));
	if (!list)
		return (NULL);
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

static char	*handle_text_token(char *str, t_wrap *list)
{
	char	*start;
	char	*tmp;
	void	*node;
	size_t	is_space_after;

	start = str;
	is_space_after = 0;
	while (*str && !specifier_one(str) \
	&& !specifier_two(str) && *str != ' ')
		str++;
	tmp = ft_substr(start, 0, str - start);
	if (str[1] == ' ' && cmd_specifier(tmp) == 0)
		is_space_after = 1;
	free(tmp);
	node = ft_lstnew(ft_substr(start, 0, str - start + is_space_after));
	if (node)
		ft_wrapadd_back(list, node);
	return (str);
}

static char	*handle_special_token(char *str, t_wrap *list)
{
	char	*old_str;

	old_str = str;
	str = convert_subfunction(str, list);
	if (str == old_str)
		str++;
	return (str);
}

t_wrap	*convert_str(char *str)
{
	t_wrap	*list;

	list = init_token_list();
	if (!list)
		return (NULL);
	while (str && *str)
	{
		if (*str == ' ')
			str++;
		else if (specifier_one(str) || specifier_two(str))
			str = handle_special_token(str, list);
		else
			str = handle_text_token(str, list);
	}
	return (list);
}
