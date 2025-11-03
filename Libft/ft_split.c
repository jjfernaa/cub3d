/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:18:18 by lginer-m          #+#    #+#             */
/*   Updated: 2025/04/08 17:52:21 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_enumeratewords(char const *s, char c)
{
	size_t	enumerate;

	if (!s)
		return (0);
	enumerate = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			enumerate++;
		while (*s && *s != c)
			s++;
	}
	return (enumerate);
}

char	**ft_split(const char *s, char c)
{
	char	**ots;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	ots = malloc(sizeof(char *) * (ft_enumeratewords(s, c) + 1));
	if (!ots)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			ots[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	ots[i] = NULL;
	return (ots);
}
