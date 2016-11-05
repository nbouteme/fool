/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:35:13 by nbouteme          #+#    #+#             */
/*   Updated: 2016/11/04 13:26:23 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/curry.h>
#include <object.h>

void init_object(t_object *base, void **vtable)
{
	void **dvtable;
	void **dvtable_end;

	base->base_dtor = curry(*vtable++, base).p;
	dvtable = (void**)&base[1];
	dvtable_end = dvtable;
	while (*vtable)
		*dvtable_end++ = curry(*vtable++, base).p;
	*dvtable_end = base->base_dtor;
	base->vtable_n_elems = dvtable_end - dvtable;
}

void object_dtor(t_object *self)
{
	void **dvtable;

	self->dtor(self);
	dvtable = (void**)&self[1];
	free_fun(self->base_dtor);
	while (self->vtable_n_elems--)
		free_fun(*dvtable++);
	free_fun(self->dtor);
}
