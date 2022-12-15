/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:38:12 by mhaksal           #+#    #+#             */
/*   Updated: 2022/02/21 15:32:45 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	i = ft_strlen(s1);
	ptr = ft_calloc(i + 1, 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, i + 1);
	return (ptr);
}
