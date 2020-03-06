/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 18:43:12 by openelop          #+#    #+#             */
/*   Updated: 2019/09/02 18:43:15 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s;
	int		k;

	i = 0;
	while (s1[i] != '\0')
		i++;
	s = ft_strnew(i);
	if (!s)
		return (NULL);
	k = 0;
	while (k < i)
	{
		s[k] = s1[k];
		k++;
	}
	return (s);
}
