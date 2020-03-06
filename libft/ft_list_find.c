/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:45:20 by openelop          #+#    #+#             */
/*   Updated: 2019/09/02 17:47:07 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)())
{
	t_list	*tmp;

	tmp = begin_list;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (cmp(tmp->content, data_ref) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
