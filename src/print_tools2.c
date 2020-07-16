/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:40:09 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/16 14:38:22 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_n_space(long n)
{
	long i;

	i = -1;
	while (n < 20 && ++i < n)
		printf(" ");
}

void	print_mode(mode_t mode)
{
	if (S_ISBLK(mode))
		printf("b");
	else if (S_ISCHR(mode))
		printf("c");
	else if (S_ISFIFO(mode))
		printf("p");
	else if (S_ISLNK(mode))
		printf("l");
	else if (S_ISSOCK(mode))
		printf("s");
	else if (S_ISDIR(mode))
		printf("d");
	else
		printf("-");
}

void	print_right(mode_t mode)
{
	printf(mode & S_IRUSR ? "r" : "-");
	printf(mode & S_IWUSR ? "w" : "-");
	printf(mode & S_IXUSR ? "x" : "-");
	printf(mode & S_IRGRP ? "r" : "-");
	printf(mode & S_IWGRP ? "w" : "-");
	printf(mode & S_IXGRP ? "x" : "-");
	printf(mode & S_IROTH ? "r" : "-");
	printf(mode & S_IWOTH ? "w" : "-");
	printf(mode & S_IXOTH ? "x" : "-");
}

void	print_uid_gid(long *max_len, struct stat stat)
{
	struct passwd	*uid;
	struct group	*gid;

	if (!(uid = getpwuid((long)stat.st_uid))
		|| !(gid = getgrgid((long)stat.st_gid)))
		exit(42);
	put_n_space(1);
	printf("%s", uid->pw_name);
	put_n_space(max_len[2] - (long)ft_strlen(uid->pw_name) + 1);
	put_n_space(1);
	printf("%s", gid->gr_name);
	put_n_space(max_len[3] - (long)ft_strlen(gid->gr_name) + 2);
}

long	get_month_diff(long file_rawtime)
{
	long	actual_rawtime;

	time(&actual_rawtime);
	return (ft_fabs(actual_rawtime - file_rawtime) / SEC_TO_MONTH);
}
