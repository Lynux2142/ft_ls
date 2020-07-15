/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:22:47 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/15 14:07:10 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_time(long rawtime)
{
	char	*date;
	char	**file_date;
	char	**file_time;

	date = ctime(&rawtime);
	file_date = ft_split_whitespaces(date);
	file_time = ft_strsplit(file_date[3], ':');
	put_n_space(1);
	printf("%s", file_date[1]);
	put_n_space(2 - ft_strlen(file_date[2]) + 1);
	printf("%s", file_date[2]);
	put_n_space(1);
	if (get_month_diff(rawtime) > 6)
	{
		put_n_space(1);
		printf("%s ", file_date[4]);
	}
	else
	{
		printf("%s", file_time[0]);
		printf(":");
		printf("%s ", file_time[1]);
	}
	free_time(file_date, file_time);
}

static long	*set_max_len(t_list *file_list)
{
	struct stat	stat;
	long		*max_len;
	long		tmp;
	int			i;

	max_len = (long*)malloc(sizeof(long) * 5);
	i = -1;
	while (++i < 5)
		max_len[i] = 0;
	while (file_list)
	{
		stat = *((t_file*)file_list->content)->stat;
		max_len[0] = 10;
		if ((tmp = nb_len((long)stat.st_nlink)) > max_len[1])
			max_len[1] = tmp;
		if ((tmp = (long)ft_strlen(getpwuid((long)stat.st_uid)->pw_name)) > max_len[2])
			max_len[2] = tmp;
		if ((tmp = (long)ft_strlen(getgrgid((long)stat.st_gid)->gr_name)) > max_len[3])
			max_len[3] = tmp;
		if ((tmp = nb_len((long)stat.st_size)) > max_len[4])
			max_len[4] = tmp;
		file_list = file_list->next;
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
		printf("%ld", (long)stat.st_nlink);
		print_uid_gid(max_len, stat);
		put_n_space(max_len[4] - nb_len((long)stat.st_size));
		printf("%ld", (long)stat.st_size);
		print_time(stat.st_mtime);
		printf("%s%c", ((t_file*)file_list->content)->name, 10);
		file_list = file_list->next;
	}
	ft_memdel((void**)&max_len);
}
