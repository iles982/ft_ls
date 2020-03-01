/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 05:32:29 by tclarita          #+#    #+#             */
/*   Updated: 2020/03/01 08:11:08 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_columns(t_flags *flags)
{
	int				col;
	int				columns;
	int				max_size;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	col = w.ws_col;
	max_size = flags->max_len_name;
	columns = 1;
	while ((max_size * columns + columns) <= col)
		columns++;
	columns--;
	return (columns);
}

void	print_l(t_data *data, t_flags *flags, t_ls *ls)
{
	int		n;

	n = 0;
	ft_printf("total %d\n", ls->blocks);
	if (flags->r == 1)
	{
		ls->b--;
		while (ls->b >= 0)
		{
			ft_printf("%s %6d %10s  %10s %6d %s %s\n", data[ls->a + ls->b].mode,
			data[ls->a + ls->b].link, data[ls->a + ls->b].usid,
			data[ls->a + ls->b].grid, data[ls->a + ls->b].size,
			data[ls->a + ls->b].time, data[ls->a + ls->b].name);
			ls->b--;
		}
	}
	else
		while (data[n + ls->a].name)
		{
			ft_printf("%s %6d %10s  %10s %6d %s %s\n", data[n + ls->a].mode,
			data[n + ls->a].link, data[n + ls->a].usid, data[n + ls->a].grid,
			data[n + ls->a].size, data[n + ls->a].time, data[n + ls->a].name);
			n++;
		}
}

void	init_a(t_column *a)
{
	a->columns1 = 0;
	a->lines1 = 0;
}

void	just_print(t_data *data, t_flags *flags, t_ls *ls)
{
	t_column	a[1];
	int		i;
	int		k;
	int		j;

	i = 0;
	j = 0;
	k = 0;
	init_a(a);
	a->columns = get_columns(flags);
	a->count = ls->i;
	a->lines = a->count / a->columns + ((a->count % a->columns > 0) ? 1 : 0);
	while (a->lines1 < a->lines)
	{
		k = 0;
		while (i < ls->i && k < a->columns && k * a->lines <= ls->i && k * a->lines + a->lines1 < ls->i)
		{
			a->columns1 = 0;
			ft_putstr(data[k * a->lines + a->lines1].name);
			j = ft_strlen(data[k * a->lines + a->lines1].name);
			while (j < flags->max_len_name)
			{
				write(1, " ", 1);
				j++;
			}
			k++;
		}
		write(1, "\n", 1);
		a->lines1++;
	}
}

void	print_all(t_data *data, t_flags *flags, t_ls *ls)
{
	if (flags->t == 1)
		sort_files_t(data, 100, ls);
	if (flags->l == 1)
		print_l(data, flags, ls);
	else
		just_print(data, flags, ls);
}
