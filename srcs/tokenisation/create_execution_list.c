/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_execution_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/17 12:00:45 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenisation.h"

/**
 * @brief Frees all memory allocated for the t_tokens structure.
 * Frees the `content` array, the `type` array, 
 * and the t_tokens structure itself.
 * @param out Pointer to the t_tokens structure to be freed.
 * @return Always returns NULL to simplify error handling in return statements.
 */
void	*del_tokens(t_tokens *out)
{
	size_t	i;

	i = 0;
	if (!out)
		return (NULL);
	if (out->content)
	{
		while (i < out->size && out->content[i])
			free(out->content[i++]);
		free(out->content);
	}
	if (out->type)
		free(out->type);
	free(out);
	return (NULL);
}

/**
 * @brief Allocates memory for the t_tokens structure and fills it with data.
 *
 * On allocation failure, frees any allocated memory using @ref del_tokens.
 * After successful allocation, it fills the structure using @ref lst_to_tokens.
 *
 * @see del_tokens()
 * @see lst_to_tokens()
 * @param out Pointer to the t_tokens pointer to be allocated and filled.
 * @param list Parsed data stored in t_wrap list format.
 * @param env Environment variables used for variable expansion.
 * @return 0 on success, 1 on failure.
 */
static int	process_tokens(t_tokens **out, t_wrap *list, char **env)
{
	*out = malloc(sizeof(t_tokens));
	if (!*out)
		return (1);
	(*out)->size = list->size;
	(*out)->type = malloc(sizeof(int) * list->size);
	(*out)->content = malloc(sizeof(char *) * (list->size + 1));
	if (!(*out)->type || !(*out)->content)
	{
		del_tokens(*out);
		*out = NULL;
		return (1);
	}
	(*out)->content[list->size] = NULL;
	lst_to_tokens(*out, list, env);
	return (0);
}

/**
 * @brief Parses a raw string into a token structure suitable for execution.
 *
 * Converts the input string into a wrapped list, updates its values using
 * @ref update_values, then processes it into a t_tokens structure using
 * @ref process_tokens. The list is cleared after use.
 *
 * @see convert_str()
 * @see update_values()
 * @see process_tokens()
 * @see ft_wrapclear()
 * @param out Pointer to the resulting token structure.
 * @param str Input command string.
 * @param env Environment variables for expansion.
 * @return 0 on success, 1 on failure.
 */
static int	wrap_operations(t_tokens **out, char *str, char **env)
{
	t_wrap		*list;

	list = convert_str(str);
	if (!list)
		return (1);
	update_values(list, env);
	if (process_tokens(out, list, env))
	{
		ft_wrapclear(list, free);
		return (1);
	}
	ft_wrapclear(list, free);
	return (0);
}

// void pipeline_insert(t_group *group)
// {
// 	int is_pipe;
// 	t_group *cpy;
// 	int i;

// 	is_pipe = 0;
// 	while (group != NULL || group->exec_type != PIPE)
// 		group =	group->next;
// 	cpy = group;
// 	while (group != NULL || group->exec_type == PIPE)
// 	{
// 		if (group->exec_type != PIPE)
// 			break ;
// 		is_pipe++;
// 		group =	group->next;
// 	}
// 	if (is_pipe)
// 		group = create_group_of_type(PIPELINE, group->parrent);
// 	i = 0;
// 	group->data = cpy;
// 	while (i < is_pipe)
// 	{
// 		cpy->parrent = group;
// 		i++;
// 	}
// }

/**
 * @brief Update `data_type` value, change regular `CMD`
 * to more specific: `STD_CMD` or some of INBUILD CMD.
 * If ther is `SHELL` --> call itself inside SHELL
 * @param parsed_group as input get `t_group`
 */
void	return_cmd_type(t_group *parsed_group)
{
	size_t		i;
	t_tokens	*token;

	// pipeline_insert(parsed_group);
	while (parsed_group != NULL)
	{
		if (parsed_group->data_type == CMD)
		{
			token = (t_tokens *)parsed_group->data;
			i = 0;
			while (token->content[i])
			{
				if (cmd_specifier(token->content[i]) != 0)
					parsed_group->data_type = cmd_specifier(token->content[i]);
				i++;
			}
			if (parsed_group->data_type == CMD)
				parsed_group->data_type = STD_CMD;
		}
		else if (parsed_group->data_type == SHELL)
			return_cmd_type((t_group *)parsed_group->data);
		parsed_group = parsed_group->next;
	}
}

int	create_execution_list(t_group *group, char *str, char **env)
{
	t_tokens	*tokens;
	t_group		*parsed_group;

	if (!group)
		return (1);
	tokens = NULL;
	if (wrap_operations(&tokens, str, env) || parser_input_validation(tokens))
	{
		del_tokens(tokens);
		return (1);
	}
	parsed_group = create_groups(tokens, NULL, 0, 0);
	return_cmd_type(parsed_group);
	del_tokens(tokens);
	if (!parsed_group)
		return (1);
	group->data_type = parsed_group->data_type;
	group->exec_type = parsed_group->exec_type;
	group->red = parsed_group->red;
	group->data = parsed_group->data;
	group->next = parsed_group->next;
	group->parrent = parsed_group->parrent;
	free(parsed_group);
	return (0);
}
