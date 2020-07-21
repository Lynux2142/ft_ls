/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 14:00:58 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/21 13:17:42 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	test_and_print_file(int *flag, char **files)
{
	struct stat	stat;
	int			i;
	t_list		*file_list;
	t_list		*dir_list;
	t_list		*err_list;

	file_list = NULL;
	dir_list = NULL;
	err_list = NULL;
	i = -1;
	while (files[++i])
	{
		lstat(files[i], &stat);
		if (!access(files[i], F_OK))
		{
			if (S_ISDIR(stat.st_mode))
				make_dir_linked_list(&dir_list, files[i]);
			else
				make_file_linked_list(&file_list, files[i]);
		}
		else
			make_err_linked_list(&err_list, files[i]);
	}
	start_print(flag, err_list, file_list, dir_list);
}

int			main(int ac, char **av)
{
	char		*dir_name;
	int			*flag;
	int			i;

	flag = get_flag(av);
	i = 1;
	while (av[i] && av[i][0] == '-' && ft_strlen(av[i]) > 1)
		++i;
	if (ac == i)
	{
		if (!(dir_name = ft_strnew(1)) || !ft_strcat(dir_name, DEFAULT_PATH))
			exit(42);
		print_file(flag, dir_name);
		if (flag[1])
			explore(flag, dir_name);
	}
	else
		test_and_print_file(flag, av + i);
	return (0);
}
