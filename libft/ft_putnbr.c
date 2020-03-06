/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:25:15 by openelop          #+#    #+#             */
/*   Updated: 2019/09/05 15:25:17 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int indicator;
	int razr;

	razr = 1000000000;
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putchar('-');
	}
	indicator = 0;
	while (razr)
	{
		if (n / razr % 10)
			indicator = 1;
		if (indicator)
			ft_putchar(n / razr % 10 + '0');
		razr /= 10;
	}
	if (n == 0)
		ft_putchar('0');
}
