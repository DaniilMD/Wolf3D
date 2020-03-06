/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:59:42 by openelop          #+#    #+#             */
/*   Updated: 2019/09/05 19:08:08 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		len;
	int		left;
	int		right;
	char	*tmp;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	while (s[i] <= 32 && s[i] != '\0')
		i++;
	left = i;
	i = len - 1;
	while (s[i] <= 32 && i >= 0)
		i--;
	right = i;
	if (right < left)
		right = left;
	tmp = ft_strnew(right - left + 1);
	if (!tmp)
		return (NULL);
	ft_strncpy(tmp, s + left, (size_t)(right - left + 1));
	return (tmp);
}
