/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:18:12 by lginer-m          #+#    #+#             */
/*   Updated: 2024/02/02 19:20:25 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	nb = (unsigned int)n;
	if (nb > 9)
		ft_putnbr_fd((int)(nb / 10), fd);
	ft_putchar_fd((char)(nb % 10 + 48), fd);
}
