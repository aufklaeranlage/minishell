/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/26 14:42:39 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

// static t_wrap	*init_list(void)
// {
// 	t_wrap	*list;

// 	list = malloc(sizeof(t_wrap));
// 	if (!list)
// 		return (NULL);
// 	list->size = 0;
// 	list->head = NULL;
// 	list->tail = NULL;
// 	return (list);
// }

// static void	lst_to_env(t_wrap *list, char **env)
// {
// 	size_t		i;
// 	t_list		*current;

// 	i = 0;
// 	current = list->head;
// 	while (i < list->size && current)
// 	{
// 		env[i] = ft_strdup((char *)current->content);
// 		current = current->next;
// 		i++;
// 	}
// }

void	delete_from_env(char *name, char ***env)
{
	char	**new_env;
	size_t	count;
	size_t	len;
	size_t	i;
	size_t	j;

	count = 0;
	len = ft_strlen(name);
	while ((*env)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], name, len) != 0 || (*env)[i][len] != '=')
			new_env[j++] = (*env)[i];
		i++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
}

/**
 * I Think ther is no way to change originat env
 * But steel need to check
 * Maybe we need to work with it local copy in all our programmmake
 */
int	ft_unset(t_tokens *tokens, char ***env_ptr)
{
	size_t	i;

	i = 1;
	if (tokens->size <= 1)
		return (0);
	while (i < tokens->size)
	{
		delete_from_env(tokens->content[i], env_ptr);
		i++;
	}
	return (0);
}
