/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:00:58 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/23 01:21:44 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_columns(t_flags *flags)
{
	int		col;
	int		columns;
	int		max_size;
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	col = w.ws_col;
	max_size = flags->max_len_name;
	columns = 1;
	while ((max_size * columns + columns) <= col)
		columns++;
	columns--;
	return (columns);
}


void	print_l(t_data **data, t_flags *flags, t_ls *ls)
{
	int i;
	t_data *start;

	i = 0;
	start = data[i];
	ft_printf("total %d\n", ls->blocks);
	while (data[i]->next)
	{
		ft_printf("%s %3d %s  %s %6d %s %s\n", data[i]->mode, data[i]->link, data[i]->usid, data[i]->grid,
		data[i]->size, data[i]->time, data[i]->name);
		data[i] = data[i]->next;
	}
	ft_printf("%s %3d %s  %s %6d %s %s\n", data[i]->mode, data[i]->link, data[i]->usid, data[i]->grid,
		data[i]->size, data[i]->time, data[i]->name);
	while (start->next)
	{
		free(start->name);
		free(start->time);
		free(start->mode);
		free(start->grid);
		free(start->usid);
		start = start->next;
	}
}

void	just_print(t_data **data, t_flags *flags, t_ls *ls)
{
	int		columns1;
	int		columns;
	int		lines;
	int		lines1;
	int		count;
	int		i;

	columns = get_columns(flags);
	columns1 = 0;
	i = 0;
	lines1 = 0;
	count = ls->i;
	lines = count / columns + ((count % columns > 0) ? 1 : 0);
	while (i < ls->i)
	{
		while ((lines > lines1))
		{
			while ((columns > columns1))
			{
				ft_printf("%-13s", data[columns1 + lines1]->name);
				columns1++;
			}
			write(1, "\n", 1);
			columns1 = 0;
			lines1++;
		}
		i++;
	}
}

void	print_all(t_data **data, t_flags *flags, t_ls *ls)
{
	if (flags->t == 1)
		sort_files_t(data, 100);
	data[0] = revive_files(data);
	if (flags->r == 1)
		data[0] = reverse(data[0]);
	if (flags->l == 1)
		print_l(data, flags, ls);
	else
		just_print(data, flags, ls);
}

void	parse(t_ls *ls, t_data **data, char *file_name, t_flags *flags)
{
	int			n;
	t_data		*start;
	long int	block;

	if (!(ls->dir = opendir(file_name)))
	{
		ft_printf("ls: %s: No such file or directory", file_name);
		return ;
	}
	data[ls->i] = (t_data *)malloc(sizeof(t_data));
    start = data[0];
	while (((ls->name = readdir(ls->dir)) > 0))
		if (ls->name->d_name[0] < 91)
			if ((ls->name->d_name[0] == '.' && flags->a == 1) || ls->name->d_name[0] != '.')
			{
				data[ls->i] = (t_data *)malloc(sizeof(t_data));
				ls->stat = (struct stat *)malloc(sizeof(struct stat));
				stat(ls->name->d_name, ls->stat);
				parse_data(data[ls->i], ls, flags);
				free(ls->stat);
				ls->blocks += ls->stat->st_blocks;
				ls->i++;
			}
	closedir(ls->dir);
	ls->dir = opendir(file_name);
	while (((ls->name = readdir(ls->dir)) > 0))
		if (ls->name->d_name[0] > 90)
		{
			data[ls->i] = (t_data *)malloc(sizeof(t_data));
			ls->stat = (struct stat *)malloc(sizeof(struct stat));
			stat(ls->name->d_name, ls->stat);
			parse_data(data[ls->i], ls, flags);
			free(ls->stat);
			ls->blocks += ls->stat->st_blocks;
			ls->i++;
		}
	closedir(ls->dir);
	n = 0;
	while (n < ls->i)
	{
		data[n]->next = data[n +1];
		n++;
	}
	data[n] = NULL;
	print_all(data, flags, ls);
	free(data);
}
