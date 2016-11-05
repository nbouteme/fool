#include <libft/std.h>
#include <libft/curry.h>
#include <stdio.h>
#include <vector.h>

t_i64 add(t_i64 a, t_i64 b)
{
	return a + b;
}

typedef long(*t_addcurry)(long);

#define PAGE_SIZE 4096
#define FUN_NBR 64
#define FUN_SIZE 64
#define MSTB_PSIZE (((64 / 8) / PAGE_SIZE) + 1)
#define FUNB_PSIZE (((64 * 64) / PAGE_SIZE) + (((64 * 64) % PAGE_SIZE) != 0))
#define MSTB_SIZE (MSTB_PSIZE * PAGE_SIZE)
#define FUNB_SIZE (FUNB_PSIZE * PAGE_SIZE)

void	**get_master_block(void);
void	init_master_block(void);

void	*funalloc2(void)
{
	int				i;
	unsigned char	*mb;
	int				n;
	int				j;

	mb = *get_master_block();
	if (!mb)
		init_master_block();
	mb = *get_master_block();
	i = 0;
	n = 0;
	while (i < (FUN_NBR / 8))
		if (mb[i] != 0xff)
		{
			j = mb[i];
			while ((j >> n) & 1)
				n++;
			mb[i] |= 1 << n;
			mb += MSTB_SIZE;
			return (mb + (64 * n) + i * 512);
		}
		else
			++i;
	return (0);
}

#include <stdlib.h>

void doubleval(t_i64 *a, t_i64 *b)
{
	*b = 2 * *a;
}

void *sumsqr(t_i64 *a, t_i64 *b)
{
	*a += *b * *b;
	return (a);
}

void sum(t_i64 *a, t_i64 *b, t_i64 *r)
{
	*r = *a + *b * *b;
}

int main()
{
	t_vector vec, vec1;
	long i = 1;
	
	init_vector(&vec, sizeof(long));
	init_vector(&vec1, sizeof(long));

	vec.push(&i);
	vec1.push(&i);
	i = 3;
	vec.push(&i);
	vec1.push(&i);
	i = 7;
	vec.push(&i);
	vec1.push(&i);

	t_vector *v = vec.zip((void*)sum, &vec1, sizeof(long));
	for(t_u32 i = 0; i < v->size; ++i)
	{
		long *pp = v->get(i);
		printf("%ld\n", *pp);
	}
	vec.dtor();
	vec1.dtor();
}
