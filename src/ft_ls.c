/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 14:00:58 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/02 15:38:40 by lguiller         ###   ########.fr       */
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
		while (av[i])
		{
			if (!(dir_name = ft_strnew(ft_strlen(av[i])))
				|| !ft_strcat(dir_name, av[i]))
				exit(42);
			print_file(flag, dir_name);
			if (flag[1])
				explore(flag, dir_name);
			++i;
		}
	}
	return (0);
}
