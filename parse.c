/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:00:58 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/21 22:31:13 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_all(t_data **data, t_flags *flags, t_ls *ls)
{
	if (flags->t == 1)
		sort_files_t(data, 100);
	data[0] = revive_files(data);
	if (flags->r == 1)
		data[0] = reverse(data[0]);
	// if (flags->l == 1)
	// 	print_l(data, flags, ls);
	// else
	// 	just_print(data, flags, ls);
}

void	parse(t_ls *ls, t_data **data, char *file_name, t_flags *flags)
{
	int n;
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
	int i;
	i = 0;
	print_all(data, flags, ls);
	ft_printf("total %d\n", ls->blocks);
	while (data[i]->next)
	{
		ft_printf("%s %2d %s %s %5d %s %s\n", data[i]->mode, data[i]->link, data[i]->usid, data[i]->grid,
		data[i]->size, data[i]->time, data[i]->name);
		data[i] = data[i]->next;
	}
	ft_printf("%s %2d %s %s %5d %s %s\n", data[i]->mode, data[i]->link, data[i]->usid, data[i]->grid,
		data[i]->size, data[i]->time, data[i]->name);
	free(data);
	data = NULL;
}
