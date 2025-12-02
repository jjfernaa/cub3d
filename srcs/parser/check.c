/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:06:19 by lginer-m          #+#    #+#             */
/*   Updated: 2025/12/02 18:11:49 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if ((len > 4) && (ft_strncmp(&str[len - 4], ".cub", 4) == 0))
		return (0);
	else
		return (1);
}

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
		return (print_error("Error: Invalid arguments\n"));
	if (check_extension(argv[1]) != 0)
		return (print_error("Error: Invalid map extension\n"));
	return (0);
}

int	is_config_line(char *line)
{
	static int	count = 0;

	if (!line || !line[0])
		return (-1);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		count++;
		if ((count > 6))
			return (-1);
		return (1);
	}
	return (0);
}

int	check_valid_chars(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' '
			&& line[i] != '\n')
			return (1);
		i++;
	}
	if (count_chars(line) != 0)
		return (1);
	return (0);
}

int	count_chars(char *line)
{
	int			i;
	static int	count = 0;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			count++;
		i++;
	}
	if (count > 1)
		return (1);
	return (0);
}
