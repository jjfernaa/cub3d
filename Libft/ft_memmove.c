/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:17:55 by lginer-m          #+#    #+#             */
/*   Updated: 2024/02/02 19:20:14 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_cp;
	char	*src_cp;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_cp = (char *)dst;
	src_cp = (char *)src;
	if (dst_cp > src_cp)
	{
		dst_cp += len - 1;
		src_cp += len - 1;
		while (len--)
			*dst_cp-- = *src_cp--;
	}
	else if (dst_cp < src_cp)
	{
		while (len--)
			*dst_cp++ = *src_cp++;
	}
	return (dst);
}
