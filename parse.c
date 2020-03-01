/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:00:58 by tclarita          #+#    #+#             */
/*   Updated: 2020/03/01 03:29:30 by tclarita         ###   ########.fr       */
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
		ls->i--;
		while (ls->i >= 0)
		{
			ft_printf("%s %3d %s  %s %6d %s %s\n", data[ls->i].mode, data[ls->i].link, data[ls->i].usid, data[ls->i].grid,
			data[ls->i].size, data[ls->i].time, data[ls->i].name);
			ls->i--;
		}
	}
	else
		while (data[n + ls->a].name)
		{
			ft_printf("%s %6d %10s  %10s %6d %s %s\n", data[n + ls->a].mode, data[n + ls->a].link, data[n + ls->a].usid, data[n + ls->a].grid,
			data[n + ls->a].size, data[n + ls->a].time, data[n + ls->a].name);
			n++;
		}
}

void	just_print(t_data *data, t_flags *flags, t_ls *ls)
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
				ft_printf("%-13s", data[columns1 + lines1].name);
				columns1++;
			}
			write(1, "\n", 1);
			columns1 = 0;
			lines1++;
		}
		i++;
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

void	make_ls(t_data *data, t_ls *ls, t_flags *flags, char *path)
{
	struct stat		stat1;
	struct dirent	*name;
	char			*path1;

	while ((name = readdir(ls->dir)))
		if (name->d_name[0] < 91)
			if ((name->d_name[0] == '.' && flags->a == 1) || name->d_name[0] != '.')
			{
				path1 = ft_strjoin(path, "/");
				path1 = ft_strjoin(path1, name->d_name);
				stat(path1, &stat1);
				parse_data(&data[ls->i + ls->d], &stat1, flags, name);
				ft_printf("%s %3d %s  %s %6d %s %s\n", data[ls->i + ls->d].mode, data[ls->i + ls->d].link, data[ls->i + ls->d].usid, data[ls->i + ls->d].grid,
				data[ls->i + ls->d].size, data[ls->i + ls->d].time, data[ls->i + ls->d].name);
				ls->blocks += stat1.st_blocks;
				ls->i++;
				free(path1);
			}
	closedir(ls->dir);
	ls->dir = opendir(path);
	while ((name = readdir(ls->dir)))
		if (name->d_name[0] > 90)
		{
			path1 = ft_strjoin(path, "/");
			path1 = ft_strjoin(path1, name->d_name);
			stat(path1, &stat1);
			parse_data(&data[ls->i + ls->d], &stat1, flags, name);
			ft_printf("%s %3d %s  %s %6d %s %s\n", data[ls->i + ls->d].mode, data[ls->i + ls->d].link, data[ls->i + ls->d].usid, data[ls->i + ls->d].grid,
			data[ls->i + ls->d].size, data[ls->i + ls->d].time, data[ls->i + ls->d].name);
			ls->blocks += stat1.st_blocks;
			ls->i++;
			free(path1);
		}
		ls->d += ls->i;
		ls->b = ls->i;
	closedir(ls->dir);
}

void	make_cycle(t_data *data, t_ls *ls, t_flags *flags, char *path)
{
	int		i;
	int		d;
	int		count;
	char	*tmp;

	if (!(ls->dir = opendir(path)))
	{
		ft_printf("ls: %s: No such file or directory", path);
		return ;
	}
	i = 0;
	make_ls(data, ls, flags, path);
	d = ls->d - ls->b;
	ls->a = d;
	// print_all(data, flags, ls);
	write(1, "\n", 1);
	count = ls->i - 1;
	while (count >= i)
	{
		while (i <= count && ((data[i + d].mode[0] != 'd') || (ft_strcmp((const char *)data[i + d].name, (const char *)".") == 0)
		|| (ft_strcmp((const char *)data[i + d].name, (const char *)"..") == 0)))
			i++;
		if (i > count)
			return ;
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, data[i + d].name);
		ls->i = 0;
		ft_printf("%s:\n", path);
		make_cycle(data, ls, flags, path);
		path = return_path(path);
		i++;
	}
	free(path);
}

void	new_parse(t_flags *flags, char *path)
{
	t_data	*data;
	t_ls	*ls;
	int		i;

	data = (t_data *)malloc(sizeof(t_data) * 1000000);
	ls = (t_ls *)malloc(sizeof(t_ls));
	ls->i = 0;
	ls->d = 0;
	ls->a = 0;
	ls->blocks = 0;
	i = 0;
	if (flags->rr == 1)
	{
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
		ft_putnbr(i);
		write(1, "\n", 1);
		free(data);
		free(ls);
	}
	else
	{
		if (!(ls->dir = opendir(path)))
		{
			ft_printf("ls: %s: No such file or directory", path);
			return ;
		}
		make_ls(data, ls, flags, path);
		print_all(data, flags, ls);
		free(data);
		free(ls);
	}
}
