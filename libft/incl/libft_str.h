/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_str.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:08:22 by abronner          #+#    #+#             */
/*   Updated: 2025/05/21 13:07:09 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STR_H
# define LIBFT_STR_H

# include "libft_ctype.h"

# include <stdlib.h>

//	STR SEARCH

size_t		ft_strlen(const char *s);

char		*ft_strchr(const char *s, int c);

char		*ft_strrchr(const char *s, int c);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		*ft_strnstr(const char *big, const char *little, size_t len);

//	STR MOVE

size_t		ft_strlcpy(char *dst, const char *src, size_t size);

size_t		ft_strlcat(char *dst, const char *src, size_t size);

char		*ft_strncpy(char *dest, char *src, size_t len);

//	STR CREATE

char		*ft_strdup(const char *s);

char		*ft_strjoin(const char *s1, const char *s2);

char		*ft_substr(const char *s, unsigned int start, size_t len);

char		*ft_strtrim(char const *s1, char const *set);

//	STR ITER

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void		ft_striteri(char *s, void (*f)(unsigned int, char*));

//	SPLIT

char		**ft_split(const char *s, char delimiter);

size_t		ft_splitcount(const char **split);

void		ft_freesplit(char **split);

//	SPLIT CREAT

char		**ft_splitlcpy(char **split, size_t len);

char		**ft_cutsplit(const char **split, size_t offset, size_t cut_len);

char		**ft_splitrmv(char **split, size_t pos);

#endif
