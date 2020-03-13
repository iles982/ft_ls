/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:00:58 by tclarita          #+#    #+#             */
/*   Updated: 2020/03/13 13:23:30 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	make_r_cycle(t_data *data, t_ls *ls, t_flags *flags, char *path)
{
	int		i;
	int		d;

	if (open_dir(ls) == 1)
		return ;
	make_ls(data, ls, flags, ls->path);
	i = ls->i - 1;
	d = ls->d - ls->b;
	ls->a = d;
	print_all(data, flags, ls);
	while (i > 0)
	{
		while (i >= 0 && ((data[i].mode[0] != 'd') ||
		(ft_strcmp(data[i].name, ".") == 0)
		|| (ft_strcmp(data[i].name, "..") == 0)))
			i--;
		if (i < 0)
			return ;
		ls->path = get_path_2(ls->path, data[i + d].name, ls);
		make_cycle(data, ls, flags, ls->path);
		ls->path = return_path(ls->path);
		i--;
	}
}

void	make_cycle(t_data *data, t_ls *ls, t_flags *flags,
		char *path)
{
	int		i;
	int		d;
	int		count;

	if (open_dir(ls) == 1)
		return ;
	i = 0;
	make_ls(data, ls, flags, ls->path);
	d = ls->d - ls->b;
	ls->a = d;
	print_all(data, flags, ls);
	count = ls->i - 1;
	while (count >= i)
	{
		while (i <= count && ((data[i + d].mode[0] != 'd') ||
		(ft_strcmp(data[i + d].name, ".") == 0)
		|| (ft_strcmp(data[i + d].name, "..") == 0)))
			i++;
		if (i > count)
			return ;
		kostil(flags, ls, data[i + d].name);
		make_cycle(data, ls, flags, ls->path);
		ls->path = return_path(ls->path);
		i++;
	}
}

void	flag_rr(t_data *data, t_ls *ls, t_flags *flags, char *path)
{
	int		i;

	i = 0;
	if (flags->r == 1)
		make_r_cycle(data, ls, flags, path);
	else
		make_cycle(data, ls, flags, path);
	while (i < ls->d)
	{
		free(data[i].name);
		free(data[i].usid);
		free(data[i].grid);
		free(data[i].time);
		free(data[i].mode);
		i++;
	}
	free(data);
	free(ls->path);
	free(ls);
}

void	just_do_it(t_data *data, t_ls *ls, t_flags *flags, char *path)
{
	int i;

	i = 0;
	if (!(ls->dir = opendir(path)))
		no_dir(path, data, ls);
	make_ls(data, ls, flags, path);
	print_all(data, flags, ls);
	while (i < ls->d)
	{
		free(data[i].name);
		free(data[i].usid);
		free(data[i].grid);
		free(data[i].time);
		free(data[i].mode);
		i++;
	}
	free(data);
	free(ls->path);
	free(ls);
}

void	new_parse(t_flags *flags, char *path)
{
	t_data	*data;
	t_ls	*ls;
	int		i;
	char	*path1;

	ls = (t_ls *)malloc(sizeof(t_ls));
	if (!(ls->dir = opendir(path)))
	{
		ft_printf("ft_ls: %s: No such file or directory", path);
		free(ls);
		return ;
	}
	closedir(ls->dir);
	if (flags->p == 1)
	{
		if (flags->l == 0)
			write(1, "\n", 1);
		ft_printf("%s:\n", path);
	}
	data = (t_data *)malloc(sizeof(t_data) * 1000000);
	i = mini_init(i, ls, path);
	do_next(data, ls, flags, path);
}
