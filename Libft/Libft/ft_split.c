/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:38:04 by mhaksal           #+#    #+#             */
/*   Updated: 2022/02/21 14:37:49 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_occ(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
	}
	return (count);
}

static void	save_strs(char **ptr, const char *s, char c, int occ)
{
	int	i;
	int	j;

	j = 0;
	while (occ > 0)
	{
		i = 0;
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
		{
			s++;
			i++;
		}
		if (*(s - i) != '\0')
		{
			ptr[j] = (char *) ft_calloc(i + 1, 1);
			ft_strlcpy(ptr[j], s - i, i + 1);
		}
		j++;
		occ--;
	}
}

char	**ft_split(char const *s, char c)
{
	int		j;
	int		occ;
	char	**ptr;

	if (!s)
		return (NULL);
	j = 0;
	occ = count_occ(s, c);
	ptr = (char **) ft_calloc((occ + 1) * sizeof(char *), 1);
	if (!ptr)
		return (NULL);
	save_strs(ptr, s, c, occ);
	return (ptr);
}
