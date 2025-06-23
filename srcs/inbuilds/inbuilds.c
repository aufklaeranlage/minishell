/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/23 17:52:25 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "exec.h"

static int	inbuilt_reddir(t_tokens *tok);

static int	red_out(t_tokens *tok, int *fd, size_t i);

int	inbuilds(t_group *grp, t_env *env)
{
	t_tokens	*tok;
	int			fd;

	fd = inbuilt_reddir((t_tokens *)grp->red);
	if (!fd || fd == -1)
		fd = 1;
	tok = (t_tokens *)grp->data;
	if (!tok->type)
		return (-1);
	if (tok->type[0] == INCMD_ECHO)
		return (ft_echo(tok, env, fd));
	else if (tok->type[0] == INCMD_PWD)
		return (ft_pwd());
	else if (tok->type[0] == INCMD_CD)
		return (ft_cd(tok, env));
	else if (tok->type[0] == INCMD_ENV)
		return (ft_env(env, fd));
	else if (tok->type[0] == INCMD_EXPORT)
		return (ft_export(tok, env, fd));
	else if (tok->type[0] == INCMD_UNSET)
		return (ft_unset(tok, env));
	else if (tok->type[0] == INCMD_EXIT)
		return (ft_exit(grp));
	return (-1);
}

static int	inbuilt_reddir(t_tokens *tok)
{
	size_t	i;
	int		fd;

	if (!tok)
		return (0);
	fd = -1;
	i = 0;
	while (i < tok->size)
	{
		if ((tok->type[i] == RED_OUT || tok->type[i] == ADD_OUT)
			&& red_out(tok, &fd, i))
			return (-1);
		++i;
	}
	return (fd);
}

//	red_out() opens a filedescriptor with the appropriate flags based on the
//	redirection type and stores it in fd[1] to later be duped as stdout.

static int	red_out(t_tokens *tok, int *fd, size_t i)
{
	int	flags;

	flags = 0;
	if (*fd != -1)
		close(*fd);
	if (tok->type[i] == RED_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (tok->type[i] == ADD_OUT)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	*fd = open((char *)tok->content[i], flags, 0644);
	if (*fd == -1)
		return (errormsg(SHNAME, (char *)tok->content[i], strerror(errno),
				NULL), 1);
	return (0);
}
