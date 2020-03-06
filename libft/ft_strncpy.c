/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:58:11 by openelop          #+#    #+#             */
/*   Updated: 2019/09/04 20:58:14 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	int		ind;

	ind = 0;
	i = 0;
	while (i < len)
	{
		if (src[i] == '\0')
			ind = 1;
		if (ind != 1)
			dst[i] = src[i];
		else
			dst[i] = '\0';
		i++;
	}
	return (dst);
}
