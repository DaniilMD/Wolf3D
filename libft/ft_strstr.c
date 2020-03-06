/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:32:49 by openelop          #+#    #+#             */
/*   Updated: 2019/09/03 16:15:38 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	simil_checker(const char *str, const char *find, int counter2)
{
	int counter;
	int indic;

	indic = 0;
	counter = 0;
	while ((str[counter2] != '\0') && (find[counter] != '\0'))
	{
		if (str[counter2] != find[counter])
		{
			indic = 1;
			break ;
		}
		counter2++;
		counter++;
		if ((str[counter2] == '\0') && (find[counter] != '\0'))
			return (1);
	}
	return (indic);
}

char		*ft_strstr(const char *str, const char *to_find)
{
	int	indx;

	indx = 0;
	if (to_find[0] == '\0')
		return ((char*)str);
	while (str[indx] != '\0')
	{
		if (str[indx] == to_find[0])
		{
			if (simil_checker(str, to_find, indx) != 1)
				return ((char*)str + indx);
		}
		indx++;
	}
	return (0);
}
