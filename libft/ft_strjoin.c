/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:18:29 by lginer-m          #+#    #+#             */
/*   Updated: 2025/04/23 21:43:21 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = (char *)malloc(len);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, len);
	if (s1)
		ft_strlcat(ptr, s1, len);
	if (s2)
		ft_strlcat(ptr, s2, len);
	return (ptr);
}
