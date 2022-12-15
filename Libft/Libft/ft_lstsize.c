/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:37:34 by mhaksal           #+#    #+#             */
/*   Updated: 2022/02/21 11:37:34 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*ptr;
	int		i;

	i = 0;
	ptr = lst;
	if (ptr)
		i += 1;
	else
		return (0);
	while (ptr -> next != NULL)
	{
		ptr = ptr -> next;
		i++;
	}
	return (i);
}
