/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:38:38 by mhaksal           #+#    #+#             */
/*   Updated: 2022/02/21 11:45:27 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*(unsigned char *)s1 > *(unsigned char *)s2)
			return (1);
		else if (*(unsigned char *)s2 > *(unsigned char *)s1)
			return (-1);
		else if (*(unsigned char *)s1 == '\0' && *(unsigned char *)s2 == '\0')
			return (0);
		n--;
		s1++;
		s2++;
	}
	return (0);
}
