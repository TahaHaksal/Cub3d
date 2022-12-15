/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <m.haksal@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:37:19 by mhaksal           #+#    #+#             */
/*   Updated: 2022/02/21 11:37:19 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;

	while ((*lst)-> next)
	{
		(*del)((*lst)-> content);
		ptr = (*lst)-> next;
		free(*lst);
		*lst = ptr;
	}
	(*del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}
