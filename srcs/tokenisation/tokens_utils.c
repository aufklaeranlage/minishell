/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/19 23:03:56 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

int	specifier_one(char *str)
{
	if (*str == '|' && str[1] == '|')
		return (OR);
	if (*str == '&' && str[1] == '&')
		return (AND);
	if (*str == '>' && str[1] == '>')
		return (ADD_OUT);
	if (*str == '<' && str[1] == '<')
		return (HERE_DOC);
	if (*str == '|')
		return (PIPE);
	if (*str == '&')
		return (BIN_AND);
	if (*str == '>')
		return (RED_OUT);
	if (*str == '<')
		return (RED_IN);
	return (0);
}

int	specifier_two(char *str)
{
	if (str[0] == '(')
		return (O_BR);
	if (str[0] == ')')
		return (C_BR);
	if (str[0] == ';')
		return (SMCLN);
	if (str[0] == ':')
		return (CLN);
	if (str[0] == '\n')
		return (NEW_LINE);
	if (str[0] == '\"' && ft_strchr(str + 1, '\"') == NULL)
		return (DQ);
	if (str[0] == '\'' && ft_strchr(str + 1, '\'') == NULL)
		return (SQ);
	if (str[0] == '\"' && ft_strchr(str + 1, '\"') != NULL)
		return (EXPAND_STR);
	if (str[0] == '\'' && ft_strchr(str + 1, '\'') != NULL)
		return (STR);
	return (0);
}

char	*minishell_getexec(char *execname, char **env)
{
	char	*exec;
	char	*tmp;
	char	**paths;
	size_t	i;

	paths = ft_splitpaths((ft_getenv("PATH", env)));
	tmp = ft_strjoin("/", execname);
	if (!tmp)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		exec = ft_strjoin(paths[i], tmp);
		if (!exec)
			return (free(tmp), NULL);
		if (access(exec, F_OK | X_OK) == 0)
			return (free(tmp), exec);
		free(exec);
		++i;
	}
	return (NULL);
}

int	cmd_specifier(char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		return (INCMD_ECHO);
	if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		return (INCMD_CD);
	if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		return (INCMD_EXIT);
	if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		return (INCMD_PWD);
	if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		return (INCMD_EXPORT);
	if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		return (INCMD_ENV);
	if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		return (INCMD_UNSET);
	return (0);
}

int	is_falg(char *str)
{
	if (str[0] == '-' && ft_isalpha(str[1]))
		return (FLAG);
	if (str[0] == '-' && str[1] == '-' && ft_isalpha(str[2]))
		return (FLAG);
	return (0);
}
