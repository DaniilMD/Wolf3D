/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:27:39 by openelop          #+#    #+#             */
/*   Updated: 2019/09/05 16:27:40 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*tmp;

	if (size + 1 == 0)
		return (NULL);
	tmp = (char*)malloc((size + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_memset(tmp, '\0', size + 1);
	return (tmp);
}
