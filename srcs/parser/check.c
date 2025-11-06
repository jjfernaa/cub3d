/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:00:01 by lginer-m          #+#    #+#             */
/*   Updated: 2025/11/06 20:49:30 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int check_extension(char *str)
{
	int len;

	len = ft_strlen(str);
	if((len > 4) && (ft_strncmp(&str[len - 4], ".cub", 4) == 0))
		return (1);
	else
		return(-1);
}

//int check_valid_c(t_game);
