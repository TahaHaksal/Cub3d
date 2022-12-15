/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:37:14 by mhaksal           #+#    #+#             */
/*   Updated: 2022/02/21 11:37:14 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	ptr = *lst;
	if (lst)
	{
		if (!*lst)
			(*lst) = new;
		else
		{
			ptr = ft_lstlast(*lst);
			ptr -> next = new;
		}
	}
}
