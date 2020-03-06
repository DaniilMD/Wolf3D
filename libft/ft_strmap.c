/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:16:35 by openelop          #+#    #+#             */
/*   Updated: 2019/09/05 17:16:36 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*tmp;

	i = 0;
	if (s == NULL || !f)
		return (NULL);
	while (s[i] != '\0')
		i++;
	tmp = (char*)malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	tmp[i] = '\0';
	i = 0;
	while (s[i] != '\0')
	{
		tmp[i] = f(s[i]);
		i++;
	}
	return (tmp);
}
