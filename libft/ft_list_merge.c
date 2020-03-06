/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:49:58 by openelop          #+#    #+#             */
/*   Updated: 2019/08/14 15:49:59 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_merge(t_list **begin_list1, t_list *begin_list2)
{
	t_list	*tmp;

	tmp = *begin_list1;
	if (tmp == NULL)
	{
		*begin_list1 = begin_list2;
	}
	else
	{
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = begin_list2;
	}
}
