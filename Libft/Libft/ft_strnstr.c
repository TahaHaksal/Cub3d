/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:29:16 by mhaksal           #+#    #+#             */
/*   Updated: 2022/02/21 12:29:17 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	if (*str2 == '\0')
		return ((char *)str1);
	while (i < len && str1[i] != '\0')
	{
		j = 0;
		while (str1[i] == str2[j] && i < len)
		{
			j++;
			i++;
			if (str2[j] == '\0')
				return ((char *)(str1 + i - j));
		}
		i = i - j;
		i++;
	}
	return (NULL);
}
