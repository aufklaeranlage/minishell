/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/12 10:55:27 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

static char	*path_to_str(char *str, t_env *env)
{
	size_t	i;
	char	*env_name;
	char	*env_value;

	str++;
	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	if (i == 0)
		return (ft_strdup("$"));
	env_name = malloc(i + 1);
	if (!env_name)
		return (NULL);
	ft_strlcpy(env_name, str, i + 1);
	env_value = env_getval(env_name, env);
	if (env_value)
	{
		env_value = ft_substr(ft_strdup(env_value), \
		ft_strlen(env_name) + 1, ft_strlen(env_value));
		free(env_name);
		return (env_value);
	}
	free(env_name);
	return (ft_strdup(""));
}

char	*expand_path(char *str, t_env *env)
{
	char	*result;
	char	*tmp;
	size_t	i;
	
	if (!str)
		return (NULL);
	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && ft_isprint(str[i+1]))
		{
			tmp = path_to_str(&str[i], env);
			if (tmp)
			{
				char *old_result = result;
				result = ft_strjoin(result, tmp);
				free(old_result);
				free(tmp);
				i++;
				while (str[i] && ft_isalnum(str[i]))
					i++;
			}
			else
				i++;
		}
		else
		{
			char old_char = str[i + 1];
			str[i + 1] = '\0';
			
			char *old_result = result;
			tmp = ft_strjoin(result, &str[i]);
			free(old_result);
			result = tmp;
			
			str[i + 1] = old_char;
			i++;
		}
	}
	return (result);
}

int ft_echo(t_tokens *tokens, t_env *env)
{
	size_t i = 1;
	int new_line = 1;
	char *out;

	if (tokens->size == 1) { printf(""); return (0);}
	else if (tokens->size >= 2 && !ft_strncmp(tokens->content[1], "-n\0", 3))
		new_line = 0, i++;

	while (i < tokens->size)
	{
		out = ft_strdup("");
		if (is_wildcard(tokens->content[i]))
			expand_wildcard(tokens->content[i], env);
		else if (tokens->type[i] == EXPAND_STR)
			out = ft_strjoin(out, expand_path(tokens->content[i], env));
		else
			out = ft_strjoin(out, tokens->content[i]);
		
		printf("%s", out);
		if (i < tokens->size - 1)
			printf(" ");
		i++;
	}
	if (new_line)
	{
		printf("\n");
	}
	free(out);
	return (0);
}
