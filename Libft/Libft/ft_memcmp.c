/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:37:39 by mhaksal           #+#    #+#             */
/*   Updated: 2022/02/21 11:37:40 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((*(unsigned char *)s1) != (*(unsigned char *)s2))
		{
			return ((*(unsigned char *)s1 + i) - (*(unsigned char *)s2 + i));
		}
		s1++;
		s2++;
		i++;
	}
	return (0);
}
