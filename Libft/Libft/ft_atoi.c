/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:35:24 by mhaksal           #+#    #+#             */
/*   Updated: 2022/02/22 10:39:58 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chck_max(unsigned long result, int neg)
{
	if (result > 2147483647 && neg == 1)
		return (-1);
	else if (result > 2147483648 && neg == -1)
		return (0);
	else
		return ((int )(neg * result));
}

int	ft_atoi(const char *str)
{
	int				i;
	int				chck_neg;
	unsigned long	result;

	chck_neg = 1;
	result = 0;
	i = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
	{
		i++;
		chck_neg *= -1;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (chck_max(result, chck_neg));
}
