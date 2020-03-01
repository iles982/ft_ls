/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:59:08 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/29 22:05:13 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS
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
}					t_ls;

typedef struct		s_data
{
	time_t			time_t;
	char			*name;
	char			*time;
	char			*mode;
	char			*usid;
	char			*grid;
	long int		link;
	long int		size;
	int				dir;
}					t_data;

void	get_flags(t_flags *flags, char **str);
void	init_flags(t_flags *flags);
void	check_len(t_data data, t_flags *flags);
void	parse_data(t_data *data, struct stat *stat, t_flags *flags, struct dirent *name);
void	make_cycle(t_data *data, t_ls *ls, t_flags *flags, char *path);

void		sort_files_t(t_data *arr, int max, t_ls *ls);
char		*return_path(char *path);

void	new_parse(t_flags *flags, char *path);
#endif
