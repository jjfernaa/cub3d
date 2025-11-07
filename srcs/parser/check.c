
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

