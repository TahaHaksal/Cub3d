/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:37:59 by mhaksal           #+#    #+#             */
/*   Updated: 2022/02/21 15:38:17 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	loop(int nb, int j, int len, int fd)
{
	if (nb == -2147483648)
	{
		write (fd, "-2", 2);
		nb = nb % 1000000000;
		nb *= -1;
	}
	if (nb < 0)
	{
		nb *= -1;
		write (fd, "-", 1);
	}
	j = nb;
	while (j > 9)
	{
		len *= 10;
		j /= 10;
	}
	while (len > 0)
	{
		ft_putchar_fd(nb / len + '0', fd);
		nb = nb % len;
		len /= 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	int		len;
	int		j;
	char	s;

	if (!fd)
		return ;
	if (n == 0)
	{
		s = 48;
		write(fd, &s, 1);
		return ;
	}
	i = 0;
	len = 1;
	j = 0;
	loop(n, j, len, fd);
}
