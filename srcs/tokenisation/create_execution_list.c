/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_execution_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/19 23:03:56 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

void	*del_tokens(t_tokens *out)
{
	size_t	i;

	i = 0;
	while (i < out->size)
		free(out->data[i++].cont);
	free(out->data);
	free(out);
	return (NULL);
}

// void	redirection(t_group *group, t_tokens *list, size_t i)
// {
// 	size_t iter = 0;
// 	size_t j = i;

// 	while (j < list->size && list->data[j].type != PIPE && 
// 		   list->data[j].type != AND && list->data[j].type != OR &&
// 		   list->data[j].type != C_BR)
// 	{
// 		if (list->data[j].type >= RED_IN && list->data[j].type <= ADD_OUT)
// 			iter++;
// 		j++;
// 	}
// 	if (iter == 0)
// 	{
// 		group->red = NULL;
// 		return;
// 	}
// 	group->red = malloc(sizeof(t_token) * (iter + 1));
// 	if (!group->red)
// 		return;    
// 	iter = 0;
// 	j = i;
// 	while (j < list->size && list->data[j].type != PIPE && 
// 		   list->data[j].type != AND && list->data[j].type != OR &&
// 		   list->data[j].type != C_BR)
// 	{
// 		if (list->data[j].type >= RED_IN && list->data[j].type <= ADD_OUT)
// 		{
// 			group->red[iter].type = list->data[j].type;
// 			group->red[iter].cont = ft_strdup(list->data[j].cont);
// 			if (!group->red[iter].cont)
// 			{
// 				group->red = del_tokens(group->red);
// 				return ;
// 			}
// 			iter++;
// 		}
// 		j++;
// 	}    
// 	group->red[iter].cont = NULL;
// }

// t_tokens	*subtoken(t_tokens *list, size_t start, size_t end)
// {
// 	t_tokens	*cmd;
// 	size_t		count;
// 	size_t		i;

// 	if (start >= list->size || end > list->size || start >= end)
// 	{
// 		cmd = malloc(sizeof(t_tokens));
// 		if (!cmd)
// 			return (NULL);
// 		cmd->data = malloc(sizeof(t_token));
// 		if (!cmd->data)
// 			return (del_tokens(cmd));
// 		cmd->size = 0;
// 		return (cmd);
// 	}
// 	count = end - start; 
// 	cmd = malloc(sizeof(t_tokens));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->data = malloc(sizeof(t_token) * count);
// 	if (!cmd->data)
// 		return (del_tokens(cmd));
// 	cmd->size = count;
// 	i = 0;
// 	while (i < count)
// 	{
// 		cmd->data[i].type = list->data[start + i].type;
// 		cmd->data[i].cont = ft_strdup(list->data[start + i].cont);
// 		if (!cmd->data[i].cont)
// 			return (del_tokens(cmd));
// 		i++;
// 	}
// 	return (cmd);
// }

t_group	*create_execution_list(char *str, char **env)
{
	t_tokens	*out;
	t_wrap		*list;
	t_group		*group;

	list = convert_str(str);
	if (!list)
		return (NULL);
	out = malloc(sizeof(t_tokens));
	if (!out)
		return (NULL);
	out->data = malloc(sizeof(t_token) * list->size);
	out->size = list->size;
	if (!out->data)
		return (NULL);
	lst_to_tokens(out, list, env);
	ft_wrapclear(list, free);
	group = create_groups(out, NULL, 0, 0);
	free(out->data);
	free(out);
	return (group);
}
