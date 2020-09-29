/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:40:09 by lguiller          #+#    #+#             */
/*   Updated: 2020/09/29 13:25:19 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_n_space(long n)
{
	long i;

	i = -1;
	while (n < 20 && ++i < n)
		ft_putstr(" ");
}

void	print_mode(mode_t mode)
{
	if (S_ISBLK(mode))
		ft_putstr("b");
	else if (S_ISCHR(mode))
		ft_putstr("c");
	else if (S_ISFIFO(mode))
		ft_putstr("p");
	else if (S_ISLNK(mode))
		ft_putstr("l");
	else if (S_ISSOCK(mode))
		ft_putstr("s");
	else if (S_ISDIR(mode))
		ft_putstr("d");
	else
		ft_putstr("-");
}

void	print_right(mode_t mode)
{
	static const char	*rwx[] = {"---", "--x", "-w-", "-wx", "r--", "r-x",
		"rw-", "rwx"};
	char				bits[10];

	ft_strcpy(&bits[0], rwx[(mode >> 6) & 7]);
	ft_strcpy(&bits[3], rwx[(mode >> 3) & 7]);
	ft_strcpy(&bits[6], rwx[mode & 7]);
	if (mode & S_ISUID)
		bits[2] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		bits[5] = (mode & S_IXGRP) ? 's' : 'S';
	if (mode & S_ISVTX)
		bits[8] = (mode & S_IXOTH) ? 't' : 'T';
	bits[9] = '\0';
	ft_putstr(bits);
}

void	print_uid_gid(long *max_len, struct stat stat)
{
	struct passwd	*uid;
	struct group	*gid;

	uid = getpwuid((long)stat.st_uid);
	gid = getgrgid((long)stat.st_gid);
	put_n_space(1);
	if (uid)
		ft_putstr(uid->pw_name);
	else
		ft_putnbr((int)stat.st_uid);
	put_n_space(max_len[2] - ((uid) ? (long)ft_strlen(uid->pw_name)
		: (long)nb_len(stat.st_uid)));
	put_n_space(2);
	if (gid)
		ft_putstr(gid->gr_name);
	else
		ft_putnbr((int)stat.st_gid);
	put_n_space(max_len[3] - ((gid) ? (long)ft_strlen(gid->gr_name)
		: (long)nb_len(stat.st_gid)));
}

long	get_month_diff(long file_rawtime)
{
	long	actual_rawtime;

	time(&actual_rawtime);
	return (ft_fabs(actual_rawtime - file_rawtime) / SEC_TO_MONTH);
}
