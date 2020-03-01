/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:59:08 by tclarita          #+#    #+#             */
/*   Updated: 2020/03/01 09:03:47 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "ft_printf/ft_printf.h"
# include <errno.h>
# include <limits.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

typedef struct		s_column
{
	int				columns1;
	int				columns;
	int				lines1;
	int				lines;
	int				count;
	int				i;
	int				k;
	int				j;
}					t_column;

typedef struct		s_flags
{
	int				l;
	int				a;
	int				t;
	int				r;
	int				rr;
	int				i;
	long int		max_len_group;
	long int		max_len_owner;
	long int		max_len_links;
	long int		max_len_size;
	long int		max_len_name;
}					t_flags;

typedef struct		s_ls
{
	DIR				*dir;
	long long		blocks;
	int				i;
	int				d;
	int				z;
	int				a;
	int				b;
	char			*path;
}					t_ls;

typedef struct		s_data
{
	time_t			time1;
	char			*name;
	char			*time;
	char			*mode;
	char			*usid;
	char			*grid;
	long int		link;
	long int		size;
	int				dir;
}					t_data;

int					open_dir(t_ls *ls);
void				get_flags(t_flags *flags, char **str);
void				init_flags(t_flags *flags);
void				check_len(t_data data, t_flags *flags);
void				parse_data(t_data *data, struct stat *stat, t_flags *flags,
					struct dirent *name);
void				make_cycle(t_data *data, t_ls *ls, t_flags *flags,
					char *path);
void				sort_files_t(t_data *arr, int max, t_ls *ls);
char				*return_path(char *path);
char				*get_path(char *path, char *name);
void				new_parse(t_flags *flags, char *path);
void				print_all(t_data *data, t_flags *flags, t_ls *ls);
void				make_ls(t_data *data, t_ls *ls, t_flags *flags, char *path);
void				no_dir(char *path, t_data *data, t_ls *ls);
char				*get_path_2(char *path, char *name, t_ls *ls);

#endif
