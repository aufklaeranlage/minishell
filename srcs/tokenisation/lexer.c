/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/23 23:41:58 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"
#include "errors.h"

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

	start = str;
	while (*str && !specifier_one(str) && !ft_isspace(*str))
	{
		if (*str == '"')
		{
			str++;
			if (ft_strchr(str, '"'))
				str = ft_strchr(str, '"');
		}
		else if (*str == '\'')
		{
			str++;
			if (ft_strchr(str, '\''))
				str = ft_strchr(str, '\'');
		}
		str++;
	}
	if (str != start)
		ft_wrapadd_back(list, ft_lstnew(ft_substr(start, 0, str - start)));
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

static int	check_bracketbalance(char *str)
{
	size_t	i;
	char	q;

	if (!str)
		return (0);
	q = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			q = str[i];
			while (str[++i] != q)
				if (!str[i])
					return (errormsg_parser("unclosed quotes"), (int)q);
		}
		q = 0;
		++i;
	}
	return ((int)q);
}

/**
 * @brief Create node_list of elements form string
 * -->	input: echo str1"str2 str3" str4 str5'str6 str7'
 * --> output: {[echo], [str1"str2 str3"], [str4], [str5'str6 str7']}
 * @param str 
 * @return splited list of elements with type t_wrap(wraper for node_list).
 */
t_wrap	*convert_str(char *str)
{
	t_wrap	*list;

	if (check_bracketbalance(str))
		return (NULL);
	list = init_token_list();
	if (!list)
		return (NULL);
	while (str && *str)
	{
		if (ft_isspace(*str))
			str++;
		if (specifier_one(str))
			str = handle_special_token(str, list);
		else
			str = handle_text_token(str, list);
	}
	return (list);
}
