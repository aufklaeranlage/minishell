/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:31:45 by abronner          #+#    #+#             */
/*   Updated: 2025/06/24 17:07:43 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <string.h>
# include <errno.h>

# include "libft.h"
# include "defines.h"

//	ERRORMSG

void	errormsg(const char *prog, const char *obj, const char *msg, \
	const char *opt);

#endif
