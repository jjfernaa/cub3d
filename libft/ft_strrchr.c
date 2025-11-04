/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:18:53 by lginer-m          #+#    #+#             */
/*   Updated: 2024/04/02 22:17:34 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	if (s[len] == ((char) c))
		return ((char *)s + len);
	while (len-- != 0)
	{
		if (s[len] == ((char)c))
			return (((char *)s) + len);
	}
	return (NULL);
}
