#include "../../includes/cub3d.h"

static int	count_split_elements(char *str)
{
	int	count;
	int	i;

	if (!str)
		return (1);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (1);
	return (0);
}

static int	get_rgb_component(char *str, int *out)
{
	char	*trimmed;
	int		num;

	trimmed = ft_strtrim(str, " \t");
	if (!trimmed)
		return (1);
	if (validate_char_color(trimmed))
	{
		free(trimmed);
		return (1);
	}
	num = ft_atoi(trimmed);
	free(trimmed);
	*out = num;
	return (0);
}

uint32_t	split_path(char *path)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 0;
	b = 0;
	split = NULL;
	if (!path)
		return (print_error("Error: Paths are not loading\n"));
	if (count_split_elements(path) == 1)
		return (print_error("Error: Invalid RGB component comilla\n"));
	split = ft_split(path, ',');
	if (check_split_rgb(split))
		return (print_error("Error: Invalid RGB split\n"));
	if (get_rgb_component(split[0], &r) || get_rgb_component(split[1], &g)
		|| get_rgb_component(split[2], &b))
	{
		free_split(split);
		return (print_error("Error: Invalid RGB component\n"));
	}
	free_split(split);
	return (check_path_colors(r, g, b));
}

uint32_t	check_path_colors(int a, int b, int c)
{
	uint32_t	color;

	if (a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255)
	{
		print_error("Error: RGB values out of range (0-255)\n");
		return (1);
	}
	color = ((uint32_t)a << 24) | ((uint32_t)b << 16)
		| ((uint32_t)c << 8) | 0xFF;
	return (color);
}

int	validate_char_color(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (1);
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		if (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
			return (1);
		if ((str[i] == '+' || str[i] == '-') && i != 0)
			return (1);
		i++;
	}
	if ((i > 3) || (i < 1))
		return (1);
	if (i == 1 && (str[0] == '+' || str[0] == '-'))
		return (1);
	return (0);
}
