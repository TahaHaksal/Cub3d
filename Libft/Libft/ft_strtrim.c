/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:38:45 by mhaksal           #+#    #+#             */
/*   Updated: 2022/02/21 15:43:28 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	begin(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s1[i] != set[j] && set[j] != '\0')
		{
			j++;
		}
		if (set[j] == '\0')
		{
			return (i);
		}
		i++;
	}
	return (i);
}

static int	end(char const *s1, char const *set, int i)
{
	int	j;

	while (i > 0)
	{
		j = 0;
		while (set[j] != s1[i] && set[j] != '\0')
			j++;
		if (set[j] == '\0')
			return (i);
		i--;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*ptr;

	ptr = NULL;
	if (!s1 || !set)
		return (ptr);
	i = begin(s1, set);
	j = end(s1, set, ft_strlen(s1) - 1);
	if (j - i > 0)
		ptr = (char *) ft_calloc(j - i + 2, 1);
	else
		ptr = (char *) ft_calloc(1, 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1 + i, j - i + 2);
	return (ptr);
}
