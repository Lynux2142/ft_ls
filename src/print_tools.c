/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:22:47 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/09 15:31:28 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	full_print(t_list *file_list)
{
	struct stat	stat;

	while (file_list)
	{
		stat = *((t_file*)file_list->content)->stat;
		printf(S_ISDIR(stat.st_mode) ? "d" : "-");
		printf(stat.st_mode & S_IRUSR ? "r" : "-");
		printf(stat.st_mode & S_IWUSR ? "w" : "-");
		printf(stat.st_mode & S_IXUSR ? "x" : "-");
		printf(stat.st_mode & S_IRGRP ? "r" : "-");
		printf(stat.st_mode & S_IWGRP ? "w" : "-");
		printf(stat.st_mode & S_IXGRP ? "x" : "-");
		printf(stat.st_mode & S_IROTH ? "r" : "-");
		printf(stat.st_mode & S_IWOTH ? "w" : "-");
		printf(stat.st_mode & S_IXOTH ? "x" : "-");
		printf("  ");
		printf("%s%c", ((t_file*)file_list->content)->name, 10);
		file_list = file_list->next;
	}
}

void	simple_print(t_list *file_list)
{
	while (file_list)
	{
		printf("%s%c", ((t_file*)file_list->content)->name, 10);
		file_list = file_list->next;
	}
}
