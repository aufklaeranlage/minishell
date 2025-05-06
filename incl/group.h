/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:30:49 by abronner          #+#    #+#             */
/*   Updated: 2025/05/05 15:59:30 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GROUP_H
# define GROUP_H

typedef struct 

typedef struct s_group
{
	int				data_type;
	int				exec_type;
	void			*data;
	struct s_group	*next;
}	t_group;

#endif
