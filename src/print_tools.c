/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:22:47 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/24 15:04:45 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_hour(long rawtime, char **file_date, char **file_time)
{
	if (get_month_diff(rawtime) > 6)
	{
		put_n_space(1);
		ft_putstr(file_date[4]);
		ft_putstr(" ");
	}
	else
	{
		ft_putstr(file_time[0]);
		ft_putstr(":");
		ft_putstr(file_time[1]);
		ft_putstr(" ");
	}
}

static void	print_time(long rawtime)
{
	char	*date;
	char	**file_date;
	char	**file_time;

	if (!(date = ctime(&rawtime))
		|| !(file_date = ft_split_whitespaces(date))
		|| !(file_time = ft_strsplit(file_date[3], ':')))
		exit(42);
	put_n_space(1);
	ft_putstr(file_date[1]);
	put_n_space(2 - ft_strlen(file_date[2]) + 1);
	ft_putstr(file_date[2]);
	put_n_space(1);
	print_hour(rawtime, file_date, file_time);
	free_time(file_date, file_time);
}

static void	set_value(long *max_len, struct stat stat)
{
	struct passwd	*pw;
	struct group	*grp;
	long			tmp;

	if ((tmp = nb_len((long)stat.st_nlink)) > max_len[1])
		max_len[1] = tmp;
	pw = getpwuid((long)stat.st_uid);
	if (pw)
	{
		if ((tmp = (long)ft_strlen(pw->pw_name))
			> max_len[2])
			max_len[2] = tmp;
	}
	else
	{
		if ((tmp = (long)nb_len((int)stat.st_uid))
			> max_len[2])
			max_len[2] = tmp;
	}
	grp = getgrgid((long)stat.st_gid);
	if (grp)
	{
		if ((tmp = (long)ft_strlen(grp->gr_name))
			> max_len[3])
			max_len[3] = tmp;
	}
	else
	{
		if ((tmp = (long)nb_len((int)stat.st_gid))
			> max_len[3])
			max_len[3] = tmp;
	}
	if ((tmp = nb_len((long)stat.st_size)) > max_len[4])
		max_len[4] = tmp;
}

static long	*set_max_len(t_list *file_list)
{
	long			*max_len;
	int				i;
	unsigned int	total;
	int				is_list_empty;

	if (!(max_len = (long*)malloc(sizeof(long) * 5)))
		exit(42);
	i = -1;
	while (++i < 5)
		max_len[i] = 0;
	is_list_empty = (file_list != NULL);
	total = 0;
	while (file_list)
	{
		total += ((t_file*)file_list->content)->stat->st_blocks;
		set_value(max_len, *((t_file*)file_list->content)->stat);
		file_list = file_list->next;
	}
	if (is_list_empty)
	{
		ft_putstr("total ");
		ft_putnbr((int)total);
		ft_putstr("\n");
	}
	return (max_len);
}

void		full_print(t_list *file_list)
{
	struct stat		stat;
	long			*max_len;

	max_len = set_max_len(file_list);
	while (file_list)
	{
		stat = *((t_file*)file_list->content)->stat;
		print_mode(stat.st_mode);
		print_right(stat.st_mode);
		put_n_space(max_len[1] - nb_len((long)stat.st_nlink) + 2);
		ft_putnbr((int)stat.st_nlink);
		print_uid_gid(max_len, stat);
		put_n_space(max_len[4] - nb_len((long)stat.st_size));
		ft_putnbr((int)stat.st_size);
		print_time(stat.st_mtime);
		ft_putendl(((t_file*)file_list->content)->name);
		file_list = file_list->next;
	}
	ft_memdel((void**)&max_len);
}
