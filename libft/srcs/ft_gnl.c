/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:42:28 by abronner          #+#    #+#             */
/*   Updated: 2025/04/03 23:22:57 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gnl.h"

static char	*read_to_out(t_wrap *wrap, int fd, size_t tsize);

static char	*init_out(size_t size, size_t tsize);

static void	store_remainder(t_wrap *wrap, char *str, size_t size);

char	*get_next_line(int fd)
{
	static t_wrap	wrap[MAXFDS];
	char			testbuf;
	char			*out;
	size_t			size;

	if (fd < 0 || fd >= MAXFDS)
		return (NULL);
	if (read(fd, &testbuf, 0) == -1)
		return (ft_wrapclear(wrap + fd, free), NULL);
	size = 0;
	if (wrap[fd].head)
		size = wrap[fd].head->size;
	if (size && ((char *)(wrap[fd].head->content))[size - 1] == '\n')
		init_out(size + 1, 0);
	else
		out = read_to_out(wrap + fd, fd, size);
	if ((wrap + fd)->head)
		ft_strncpy(out, (char *)wrap[fd].head->content, size);
	if (size)
		ft_wrapdelfirst(wrap + fd, free);
	if (!out)
		ft_wrapclear(wrap + fd, free);
	return (out);
}

static char	*read_to_out(t_wrap *wrap, int fd, size_t tsize)
{
	char	*out;
	char	*buf;
	ssize_t	size;
	char	*tmp;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(*buf));
	if (!buf)
		return (NULL);
	size = read(fd, buf, BUFFER_SIZE);
	if (size < 0)
		return (free(buf), init_out(size, tsize));
	buf[size] = '\0';
	tmp = ft_strchr(buf, '\n');
	if (tmp || size == 1)
	{
		store_remainder(wrap, tmp + 1, size - (tmp - buf) - 1);
		size = tmp - buf + 1;
		out = init_out(size, tsize);
	}
	else
		out = read_to_out(wrap, fd, tsize + size);
	if (!out)
		return (free(buf), ft_wrapclear(wrap, free), NULL);
	ft_strncpy(out + tsize, buf, size);
	return (free(buf), out);
}

static char	*init_out(size_t size, size_t tsize)
{
	char	*out;

	if (tsize + size <= 0)
		return (NULL);
	out = malloc((tsize + size + 1) * sizeof(*out));
	if (!out)
		return (NULL);
	out[tsize + size] = '\0';
	return (out);
}

static void	store_remainder(t_wrap *wrap, char *str, size_t size)
{
	char	*tmp;
	t_list	*node;
	char	*check;

	if (size == 0)
		return ;
	node = malloc(sizeof(*node));
	if (!node)
		return (ft_wrapclear(wrap, free));
	check = ft_strchr(str, '\n');
	if (!check)
		check = str + size;
	else
		++check;
	tmp = ft_substr(str, 0, check - str);
	if (!tmp)
		return (ft_wrapclear(wrap, free));
	node->content = (void *)tmp;
	node->size = check - str;
	node->next = NULL;
	ft_wrapadd_back(wrap, node);
	if (*(check - 1) == '\n' && size - (check - str))
		store_remainder(wrap, check, size - (check - str));
}
