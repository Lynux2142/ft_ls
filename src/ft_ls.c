/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 14:00:58 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/06 16:40:44 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	char		*dir_name;
	int			*flag;
	int			i;

	flag = get_flag(av);
	i = 1;
	while (av[i] && av[i][0] == '-')
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
	{
		if (ac - i == 1)
		{
			if (!(dir_name = ft_strnew(ft_strlen(av[i])))
				|| !ft_strcat(dir_name, av[i]))
				exit(42);
			print_file(flag, dir_name);
			if (flag[1])
				explore(flag, dir_name);
		}
		else
		{
			while (av[i])
			{
				printf("%s:%c", av[i], 10);
				if (!(dir_name = ft_strnew(ft_strlen(av[i])))
					|| !ft_strcat(dir_name, av[i]))
					exit(42);
				print_file(flag, dir_name);
				if (flag[1])
					explore(flag, dir_name);
				++i;
				if (ac != i)
					printf("%c", 10);
			}
		}
	}
	return (0);
}
