/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:14:20 by openelop          #+#    #+#             */
/*   Updated: 2019/09/07 17:14:22 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*tmpd;
	unsigned char	*tmps;

	i = 0;
	tmpd = (unsigned char*)dst;
	tmps = (unsigned char*)src;
	if (tmpd == NULL && tmps == NULL)
		return (NULL);
	if (tmpd > tmps)
		while (len--)
			tmpd[len] = tmps[len];
	else
		while (i < len)
		{
			tmpd[i] = tmps[i];
			i++;
		}
	return (dst);
}
