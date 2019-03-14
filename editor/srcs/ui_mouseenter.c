/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_mouseenter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:43:59 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/02 19:54:56 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		ui_mouseenter(int x, int y, t_square square)
{
	return (x > square.rect.x && x < square.rect.x + square.rect.w
	&& y > square.rect.y && y < square.rect.y + square.rect.h);
}
