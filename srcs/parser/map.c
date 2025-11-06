/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:00:12 by lginer-m          #+#    #+#             */
/*   Updated: 2025/11/06 18:39:39 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
Ignorar todos los espacios en blanco iniciales.
Si la fila actual es la fila 0 o la fila final, solo aceptar '1' y ' '.
De lo contrario, el primer y el último carácter siempre deben ser un '1'
En el caso de espacios en blanco no iniciales, los únicos caracteres aceptables adyacentes al espacio son '1' o ' '.
Si la longitud de la fila actual es mayor que la longitud de la fila superior y la columna actual es mayor que la longitud de la fila superior, el carácter actual debe ser '1'.
Si la longitud de la fila actual es mayor que la longitud de la fila inferior y la columna actual es mayor que la longitud de la fila inferior, el carácter actual debe ser '1'.
Estas reglas deben cumplir con todos los requisitos del mapa.*/