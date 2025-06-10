/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:31:45 by abronner          #+#    #+#             */
/*   Updated: 2025/06/10 11:18:43 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <string.h>
# include <errno.h>

# include "libft.h"
# include "defines.h"

//	ERRORMSG

void	errormsg(char *prog, char *obj, char *msg, char *opt);

#endif
