/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:31:45 by abronner          #+#    #+#             */
/*   Updated: 2025/05/13 11:54:10 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <string.h>
# include <errno.h>

# include "libft.h"
# include "defines.h"

//	ERRORMSG

void	errormsg(char *obj, char *msg);

#endif
