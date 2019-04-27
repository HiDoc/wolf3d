/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:32:17 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/27 16:35:38 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	is_spc(int c)
{
	return c == ' ';
}

int	is_tab(int c)
{
	return c == '\t';
}

int	is_min(int c)
{
	return c == '-';
}

int	is_end(int c)
{
	return c == '\n';
}

int	is_sec(int c)
{
	return c == 's';
}