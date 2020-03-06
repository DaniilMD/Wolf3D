/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:16:43 by openelop          #+#    #+#             */
/*   Updated: 2019/09/05 17:16:44 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	if (!s || !f)
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
		tmp[i] = f(i, s[i]);
		i++;
	}
	return (tmp);
}
