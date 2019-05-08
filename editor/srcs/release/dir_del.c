/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:45:18 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 20:45:44 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		dir_del(void **ap)
{
	DIR			*dr;

	dr = (DIR *)(*ap);
	if (ap && *ap)
	{
		closedir(dr);
		dr = 0;
	}
}
