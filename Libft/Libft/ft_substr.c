/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:38:54 by mhaksal           #+#    #+#             */
/*   Updated: 2022/02/21 15:43:40 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (len < ft_strlen(s + start))
		ptr = ft_calloc(len + 1, 1);
	else
		ptr = ft_calloc(ft_strlen(s + start) + 1, 1);
	if (!ptr)
		return (NULL);
	if (start < ft_strlen(s))
		ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
