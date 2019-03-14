/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_hex_to_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:31:46 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/02 16:51:38 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

SDL_Color		ui_hex_to_rgb(int hexa)
{
	SDL_Color color;

	color.r = hexa >> 24;
	color.g = hexa >> 16;
	color.b = hexa >> 8;
	color.a = hexa;
	return (color);
}
