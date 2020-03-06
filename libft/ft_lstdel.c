/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:14:37 by openelop          #+#    #+#             */
/*   Updated: 2019/09/09 18:14:38 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	if (*alst && del)
	{
		while (*alst)
		{
			tmp = (*alst)->next;
			del(*alst, (*alst)->content_size);
			*alst = tmp;
		}
		alst = NULL;
	}
}
