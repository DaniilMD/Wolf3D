/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char_starstar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:02:14 by openelop          #+#    #+#             */
/*   Updated: 2020/01/06 14:02:15 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		free_char_starstar(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] != NULL)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}
