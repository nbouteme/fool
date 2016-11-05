/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:38:21 by nbouteme          #+#    #+#             */
/*   Updated: 2016/11/04 13:01:48 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include <libft/std.h>

typedef struct s_object t_object;
typedef void(*t_dtorf)(void*);
typedef void(*t_dtorb)(void);

struct s_object
{
	t_u32	vtable_n_elems;
	t_dtorf base_dtor;
	t_dtorf dtor;
};

void init_object(t_object *base, void **vtable);

#endif
