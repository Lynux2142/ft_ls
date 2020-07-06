/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:44:08 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/06 16:41:27 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		*set_flag(void)
{
	int *flag;
	int i;

	if (!(flag = (int*)malloc(sizeof(int) * 5)))
		exit(42);
	i = -1;
	while (++i < 5)
		flag[i] = 0;
	return (flag);
}

int		correct_flag(char flag)
{
	int i;

	i = -1;
	while (FLAG_LIST[++i])
		if (FLAG_LIST[i] == flag)
			return (i);
	return (-1);
}

void	parse_flag(int *flag, char *av)
{
	int i;
	int value;

	i = 0;
	while (av[++i])
	{
		value = correct_flag(av[i]);
		if (value != -1)
			flag[value] = 1;
		else
		{
			printf("ls: illegal option -- %c%c", av[i], 10);
			printf("usage: ft_ls [-Ralrt] [file ...]%c", 10);
			exit(42);
		}
	}
}

int		*get_flag(char **av)
{
	int *flag;
	int i;

	flag = set_flag();
	i = 0;
	while (av[++i] && av[i][0] == '-')
		parse_flag(flag, av[i]);
	return (flag);
}
