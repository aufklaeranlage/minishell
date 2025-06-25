/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/25 18:52:10 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "tokenisation.h"

// static char	*path_to_str(char *str, char **env)
// {
// 	size_t	i;
// 	char	*env_name;
// 	char	*env_value;
//
// 	str++;
// 	i = 0;
// 	while (str[i] && ft_isalnum(str[i]))
// 		i++;
// 	if (i == 0)
// 		return (ft_strdup("$"));
// 	env_name = malloc(i + 1);
// 	if (!env_name)
// 		return (NULL);
// 	ft_strlcpy(env_name, str, i + 1);
// 	env_value = ft_getenv(env_name, env);
// 	free(env_name);
// 	if (env_value)
// 	{
// 		env_value = ft_strdup(ft_strchr(env_value, '=') + 1);
// 		return (env_value);
// 	}
// 	return (ft_strdup(""));
// }

static char	*append_exit_status(char *result, size_t *i, t_env *env)
{
	char	*code;

	code = ft_itoa(env->status);
	if (!code)
		return (NULL);
	result = strjoin_and_free(result, code);
	free(code);
	*i += 2;
	return (result);
}

static char	*append_env_var(char *str, char *result, size_t *i, t_env *env)
{
	char	*tmp;

	tmp = env_getval(str + 1, env);
	tmp = ft_strdup(tmp);
	if (!tmp)
		return (NULL);
	result = strjoin_and_free(result, tmp);
	free(tmp);
	(*i)++;
	while (str[*i] && ft_isalnum(str[*i]))
		(*i)++;
	return (result);
}

static char	*append_literal_char(char *str, char *result, size_t *i)
{
	char	current[2];

	current[0] = str[*i];
	current[1] = '\0';
	result = strjoin_and_free(result, current);
	(*i)++;
	return (result);
}

/**
 * @brief Go thrue function and expand all inclusion 
 * @param str 
 * @param env 
 * @return Expandet string
 */
char	*expand_path(char *str, t_env *env)
{
	char	*result;
	size_t	i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?' \
			&& (!str[i + 2] || str[i + 2] == ' '))
			result = append_exit_status(result, &i, env);
		else if (str[i] == '$' && ft_isalnum(str[i + 1]))
			result = append_env_var(str, result, &i, env);
		else
			result = append_literal_char(str, result, &i);
		if (!result)
			return (NULL);
	}
	return (result);
}
