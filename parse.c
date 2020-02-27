/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:00:58 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/27 08:34:53 by tclarita         ###   ########.fr       */
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
			// free(data[ls->i].name);
			// free(data[ls->i].grid);
			// free(data[ls->i].usid);
			// free(data[ls->i].mode);
			// free(data[ls->i].time);
			ls->i--;
		}
	}
	else
		while (n < ls->i)
		{
			ft_printf("%s %3d %s  %s %6d %s %s\n", data[n].mode, data[n].link, data[n].usid, data[n].grid,
			data[n].size, data[n].time, data[n].name);
			// free(data[n].name);
			// free(data[n].grid);
			// free(data[n].usid);
			// free(data[n].mode);
			// free(data[n].time);
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
	ls->i = 0;
	ls->blocks = 0;
	while ((ls->name = readdir(ls->dir)))
		if (ls->name->d_name[0] < 91)
			if ((ls->name->d_name[0] == '.' && flags->a == 1) || ls->name->d_name[0] != '.')
			{
				ls->stat = (struct stat *)malloc(sizeof(struct stat));
				lstat(ls->name->d_name, ls->stat);
				parse_data(&data[ls->i], ls, flags);
				free(ls->stat);
				ls->blocks += ls->stat->st_blocks;
				ls->i++;
			}
	closedir(ls->dir);
	ls->dir = opendir(path);
	while ((ls->name = readdir(ls->dir)))
		if (ls->name->d_name[0] > 90)
		{
			ls->stat = (struct stat *)malloc(sizeof(struct stat));
			lstat(ls->name->d_name, ls->stat);
			parse_data(&data[ls->i], ls, flags);
			free(ls->stat);
			ls->blocks += ls->stat->st_blocks;
			ls->i++;
		}
	closedir(ls->dir);
}

char	*return_path(char *path)
{
	int i;
	int k;
	char *tmp;

	i = 0;
	k = 0;
	while (path[i])
	{
		if (path[i] == '/')
			k = i;
		i++;
	}
	tmp = ft_strnew(k);
	tmp = ft_strncpy(tmp, path, k);
	free(path);
	return (tmp);
}

void	make_cycle(t_data *data, t_ls *ls, t_flags *flags, char *path)
{
	int		i;
	t_data	*new;
	t_ls	*ls1;

	if (!(ls->dir = opendir(path)))
	{
		ft_printf("ls: %s: No such file or directory", path);
		return ;
	}
	i = 0;
	make_ls(data, ls, flags, path);
	print_all(data, flags, ls);
	while (ls->i > i)
	{
		while (i < ls->i && ((data[i].mode[0] != 'd') || (ft_strcmp(data[i].name, ".") == 0) || (ft_strcmp(data[i].name, "..") == 0)))
			i++;
		if (i == ls->i)
			return ;
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, data[i].name);
		ft_printf("\n%s:\n", path);
		new = (t_data *)malloc(sizeof(t_data) * 100);
		ls1 = (t_ls *)malloc(sizeof(t_ls));
		ls1->i = 0;
		ls1->blocks = 0;
		make_cycle(new, ls1, flags, path);
		path = return_path(path);
		i++;
	}
	// i = 0;
	// while (data[i].name)
	// {
	// 	free(data[i].name);
	// 	free(data[i].usid);
	// 	free(data[i].grid);
	// 	free(data[i].mode);
	// 	free(data[i].time);
	// 	i++;
	// }
	
}

void	new_parse(t_flags *flags, char *path)
{
	t_data	*data;
	t_ls	*ls;
	int		i;

	data = (t_data *)malloc(sizeof(t_data) * 100);
	ls = (t_ls *)malloc(sizeof(t_ls));
	ls->i = 0;
	ls->blocks = 0;
	i = 0;
	if (flags->rr == 1)
		make_cycle(data, ls, flags, path);
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
