/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 14:00:58 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/02 13:48:06 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	char		*dir_name;

	dir_name = ft_strnew((ac == 1) ? 1 : ft_strlen(av[1]));
	ft_strcat(dir_name, (ac == 1) ? DEFAULT_PATH : av[1]);
	print_file(dir_name);
	explore(dir_name);
	//while (1);
	return (0);
}
