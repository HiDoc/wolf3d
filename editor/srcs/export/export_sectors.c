/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:43:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 17:59:24 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		export_w_vtx(int fd, t_sct *sct)
{
	t_w_vtx		*w_vtx;

	w_vtx = sct->w_vtx_start;
	while (w_vtx)
	{
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(w_vtx->vtx->id, fd);
		w_vtx = w_vtx->next;
	}
	ft_putstr_fd(" :", fd);
}

static void		export_walltx(int fd, t_sct *sct)
{
	t_w_vtx		*w_vtx;

	w_vtx = sct->w_vtx_start;
	while (w_vtx)
	{
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(w_vtx->ref, fd);
		w_vtx = w_vtx->next;
	}
	ft_putchar_fd('\n', fd);
}

void			export_sectors(int fd, t_env *env)
{
	t_sct		*sct;

	ft_putstr_fd("# sector: cl_h cl_tx fl_h fl_tx", fd);
	ft_putendl_fd("gravity roof type n-vtx n-tx", fd);
	sct = env->editor.sct_start;
	sct->id = 0;
	while (sct)
	{
		ft_putstr_fd("s ", fd);
		ft_putnbr_fd(sct->ceil, fd);
		ft_putstr_fd(" 0 ", fd);
		ft_putnbr_fd(sct->floor, fd);
		ft_putstr_fd(" 0 ", fd);
		ft_putnbr_fd(sct->gravity, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(sct->roof, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(sct->type, fd);
		ft_putstr_fd(" : ", fd);
		export_w_vtx(fd, sct);
		export_walltx(fd, sct);
		sct = sct->next;
		sct->id++;
	}
}
