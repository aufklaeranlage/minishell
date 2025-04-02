/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:43:24 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:50:20 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_put.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	slen;

	slen = ft_strlen(s);
	write(fd, s, slen);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	dig;

	if (n >= 10)
	{
		dig = n % 10;
		ft_putnbr_fd(n / 10, fd);
	}
	else if (n < 0)
	{
		dig = -(n % 10);
		ft_putchar_fd('-', fd);
		if (n <= -10)
			ft_putnbr_fd(-(n / 10), fd);
	}
	else
		dig = n;
	dig += '0';
	ft_putchar_fd(dig, fd);
}
