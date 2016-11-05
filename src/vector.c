/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:30:43 by nbouteme          #+#    #+#             */
/*   Updated: 2016/11/05 13:57:33 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/curry.h>
#include <vector.h>
#include <stdlib.h>

t_vector *init_vector(t_vector *self, t_u32 type_size)
{
	static void *members[] = { vector_dtor, vector_get, vector_push, vector_pop,
							   vector_insert, vector_reduce, vector_map,
							   vector_zip, vector_reserve, vector_resize, 0 };

	ft_memset(self, 0, sizeof(*self));
	self->type_size = type_size;
	init_object(&self->base, members);
	return (self);
}

void vector_dtor(t_vector *self)
{
	free(self->data_ptr);
}

void vector_pop(t_vector *self)
{
	self->size--;
}

void *vector_get(t_vector *self, t_u32 i)
{
	return (self->data_ptr + (i * self->type_size));
}

void vector_reserve(t_vector *self, t_u32 i)
{
	void *tmp;

	while (self->capacity <= i)
	{
		self->capacity += self->capacity + 1;
		tmp = self->data_ptr;
		self->data_ptr = malloc(self->capacity * self->type_size);
		ft_memcpy(self->data_ptr, tmp, self->type_size * self->size);
		free(tmp);		
	}
}

void vector_resize(t_vector *self, t_u32 i)
{
	self->reserve(i);
	self->size = i;
}

void vector_push(t_vector *self, void *data)
{
	if (self->size + 1 > self->capacity)
		self->reserve(self->size + 1);
	ft_memcpy(self->data_ptr + self->type_size * self->size, data, self->type_size);
	self->size++;
}

void vector_insert(t_vector *self, void *data, t_u32 idx)
{
	t_u8 *tmp;

	if (idx >= self->size)
		return (self->push(data));
	if (self->size + 1 > self->capacity)
		self->reserve(self->size + 1);
	tmp = &self->data_ptr[self->type_size * idx];
	ft_memmove(tmp + self->type_size, tmp, (self->size - idx) * self->type_size);
	ft_memcpy(self->data_ptr + idx * self->size, data, self->type_size);
	self->size++;
}

void *vector_reduce(t_vector *self, void *init, t_reduce_fun f)
{
	t_u32 i;
	t_u8 *it;

	i = 0;
	it = self->data_ptr;
	while (i < self->size)
	{
		init = f(init, it);
		it += self->type_size;
		++i;
	}
	return (init);
}

#include <stdio.h>

void *map_helper(t_map_fun f, t_vector *self, void *data)
{
	self->resize(self->size + 1);
	f(data, self->get(self->size - 1));
	return (self);
}

t_vector *vector_map(t_vector *self, t_map_fun f, t_u32 ts, t_vector *res)
{
	t_u32 i;
	void *cf;

	i = 0;
	cf = curry(map_helper, (void*)f).p;
	init_vector(res, ts);
	self->reduce(res, cf);
	free_fun(cf);
	return (res);
}

typedef struct	s_zip_info
{
	t_vector	*source;
	t_vector	*acc;
	t_u64		i;
}				t_zip_info;

void *zip_helper(t_zip_fun f, t_zip_info *zi, void *data)
{
	t_vector *ret;
	t_vector *b;

	ret = zi->acc;
	b = zi->source;
	ret->resize(ret->size + 1);
	f(data, b->get(zi->i), ret->get(zi->i));
	zi->i++;
	return (zi);
}

t_vector *vector_zip(t_vector *self, t_zip_fun f, t_vector *b, t_u32 ts)
{
	t_vector *ret;
	void *cf;

	cf = curry(zip_helper, (void*)f).p;
	ret = malloc(sizeof(*ret));
	init_vector(ret, ts);
	self->reduce(&(t_zip_info){b, ret, 0}, cf);
	return (ret);
}
