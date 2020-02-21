/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:00:58 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/21 20:26:12 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_all(t_data *data, t_flags *flags, t_ls *ls)
{
	int i;

	i = 0;
	if (flags->t == 1)
		data = sort_t(data, flags);
	write(1, "Q", 1);
	if (flags->r == 1)
		ft_lstrev(&data);
	// while (data->next)
	// {
	// 	if (i != 0)
	// 		ft_printf("%s %2d %s %s %5d %s %s\n", data->mode, data->link, data->usid, data->grid,
	// 		data->size, data->time, data->name);
	// 	data = data->next;
	// 	i++;
	// }
// 	if (flags->l == 1)
// 		print_l(data, flags, ls);
// 	else
// 		just_print(data, flags, ls);
}

t_data  *parse(t_ls *ls, t_data *data, char *file_name, t_flags *flags)
{
    t_data *start;
	long int block;

	if (!(ls->dir = opendir(file_name)))
	{
		ft_printf("ls: %s: No such file or directory", file_name);
		return (data);
	}
	block = 0;
	data = (t_data *)malloc(sizeof(t_data));
    start = data;
	while (((ls->name = readdir(ls->dir)) > 0))
	{
		if (ls->name->d_name[0] < 91)
		{
			if ((ls->name->d_name[0] == '.' && flags->a == 1) || ls->name->d_name[0] != '.')
			{
				ls->stat = (struct stat *)malloc(sizeof(struct stat));
				stat(ls->name->d_name, ls->stat);
				data->next = (t_data *)malloc(sizeof(t_data));
				parse_data(data, ls, flags);
				data = data->next;
				free(ls->stat);
				block += ls->stat->st_blocks;
			}
		}
	}
	closedir(ls->dir);
	ls->dir = opendir(file_name);
	while (((ls->name = readdir(ls->dir)) > 0))
	{
		if (ls->name->d_name[0] > 90)
		{
			ls->stat = (struct stat *)malloc(sizeof(struct stat));
			stat(ls->name->d_name, ls->stat);
			data->next = (t_data *)malloc(sizeof(t_data));
			parse_data(data, ls, flags);
			data = data->next;
			free(ls->stat);
			block += ls->stat->st_blocks;
		}
	}
	closedir(ls->dir);
	data->next = NULL;
	data = start;
	ls->blocks = block;
	print_all(data, flags, ls);
	ft_printf("total %d\n", ls->blocks);
	while (data->next)
	{
		ft_printf("%s %2d %s %s %5d %s %s\n", data->mode, data->link, data->usid, data->grid,
		data->size, data->time, data->name);
		data = data->next;
	}
	free(data);
	data = NULL;
    return (start);
}
