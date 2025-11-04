/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:18:48 by lginer-m          #+#    #+#             */
/*   Updated: 2024/02/02 19:21:06 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (*needle == '\0')
		return ((char *)haystack);
	while (++i < len && *(haystack + i))
	{
		j = 0;
		while (*(haystack + i + j) == *(needle + j) && i + j < len)
		{
			j++;
			if (!*(needle + j))
				return ((char *)haystack + i);
		}
	}
	return (NULL);
}
