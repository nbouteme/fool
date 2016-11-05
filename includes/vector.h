/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:09:56 by nbouteme          #+#    #+#             */
/*   Updated: 2016/11/05 13:59:02 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <libft/std.h>
# include <object.h>

typedef struct s_vector t_vector;

typedef void*(*t_getb)(t_u32);
typedef void(*t_pushb)(void*);
typedef void(*t_insertb)(void*, t_u32);
typedef void(*t_destb)(void);

typedef void*(*t_reduce_fun)(void*, void*);
typedef void*(*t_reduceb)(void*, t_reduce_fun);

typedef void(*t_map_fun)(void*, void*);
typedef t_vector*(*t_mapb)(t_map_fun, t_u32, t_vector*);

typedef void(*t_zip_fun)(void*, void*, void*);
typedef t_vector*(*t_zipb)(t_zip_fun, t_vector*, t_u32);

typedef t_destb t_popb;
typedef t_getb t_reserveb;

struct	s_vector
{
	t_object	base;
	t_getb		get;
	t_pushb		push;
	t_popb		pop;
	t_insertb	insert;
	t_reduceb	reduce;
	t_mapb		map;
	t_zipb		zip;
	t_reserveb	reserve;
	t_reserveb	resize;
	t_dtorb		dtor;
	t_u32		size;
	t_u32		type_size;
	t_u32		capacity;
	t_u8		*data_ptr;
};

t_vector *init_vector(t_vector *self, t_u32 type_size);

void vector_dtor(t_vector *self);
void *vector_get(t_vector *self, t_u32 i);
void vector_push(t_vector *self, void *data);
void vector_pop(t_vector *self);
void vector_insert(t_vector *self, void *data, t_u32 idx);
void *vector_reduce(t_vector *self, void *init, t_reduce_fun f);
t_vector *vector_map(t_vector *self, t_map_fun f, t_u32 ts, t_vector *res);
void vector_reserve(t_vector *self, t_u32 i);
void vector_resize(t_vector *self, t_u32 i);
t_vector *vector_zip(t_vector *self, t_zip_fun f, t_vector *b, t_u32 ts);

#endif
