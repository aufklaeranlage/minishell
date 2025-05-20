/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_convert_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/19 23:03:56 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

static char	*convert_specifier_one(char *str, t_wrap *list)
{
	void	*node;

	node = NULL;
	if (specifier_one(str) >= HERE_DOC)
		node = ft_lstnew(ft_substr(str, 0, 2));
	else
		node = ft_lstnew(ft_substr(str, 0, 1));
	if (node)
		ft_wrapadd_back(list, node);
	else
		return (str);
	return (NULL);
}

static void	*create_quote_node(char *str, char quote_char)
{
	void	*node;
	char	*end;

	end = ft_strchr(str + 1, quote_char);
	if (!end)
		node = ft_lstnew(ft_substr(str, 0, 1));
	else
		node = ft_lstnew(ft_substr(str, 0, end - str + 1));
	return (node);
}

static char	*convert_specifier_two(char *str, t_wrap *list)
{
	void	*node;
	int		spec;

	node = NULL;
	spec = specifier_two(str);
	if (spec == STR)
		node = create_quote_node(str, '\'');
	else if (spec == EXPAND_STR)
		node = create_quote_node(str, '\"');
	else
		node = ft_lstnew(ft_substr(str, 0, 1));
	if (node)
		ft_wrapadd_back(list, node);
	else
		return (str);
	return (NULL);
}

char	*convert_subfunction(char *str, t_wrap *list)
{
	char	*result;

	result = NULL;
	if (specifier_one(str))
		result = convert_specifier_one(str, list);
	else if (specifier_two(str))
		result = convert_specifier_two(str, list);
	if (result)
		return (result);
	if (list->tail && list->tail->content)
		return (str + ft_strlen(list->tail->content));
	else
		return (str + 1);
}
