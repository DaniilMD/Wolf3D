/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 18:16:52 by openelop          #+#    #+#             */
/*   Updated: 2019/09/02 18:16:54 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nb)
{
	int i;

	i = 0;
	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	while (i <= nb / 2)
	{
		if (i == 46340)
			return (0);
		if (i * i > nb)
			return (0);
		else if (i * i == nb)
			return (i);
		i++;
	}
	return (0);
}
