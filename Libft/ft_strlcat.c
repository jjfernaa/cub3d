/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:18:32 by lginer-m          #+#    #+#             */
/*   Updated: 2024/02/02 19:20:50 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (dst[i] != '\0')
		++i;
	while (src[j] != '\0')
		++j;
	if (dstsize <= i)
		j = j + dstsize;
	else
		j = j + i;
	while (src[k] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[k];
		++i;
		++k;
	}
	dst[i] = '\0';
	return (j);
}
