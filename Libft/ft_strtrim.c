/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:18:57 by lginer-m          #+#    #+#             */
/*   Updated: 2024/02/02 19:48:11 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed_str;

	if (!s1)
		return (NULL);
	if (!set || *set == '\0')
		return (ft_strdup((char *)s1));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trimmed_str = (char *)malloc(end - start + 1);
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, &s1[start], end - start + 1);
	trimmed_str[end - start] = '\0';
	return (trimmed_str);
}
