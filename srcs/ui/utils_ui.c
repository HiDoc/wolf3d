/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:57 by abaille           #+#    #+#             */
/*   Updated: 2019/03/11 14:28:40 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Surface *ui_img(char *filename)
{
	SDL_Surface	*new;
	char		*path;
	const char	*png = ".png";

	path = ft_strjoin("./rsrc/img/inventory/", filename);
	path = ft_strljoin(path, (char *)png);
	if (!(new = surface_fr_png(path)))
        return (NULL);
	free(path);
	path = NULL;
	return (new);
}

int    number_font(t_env *env, char *str, t_vctr pos, SDL_Color color)
{
	SDL_Surface	    *surface;
	TTF_Font        *font;
	SDL_Surface		*tmp;

	if (!(font = TTF_OpenFont("rsrc/font/5E.ttf", pos.z)))
        return (0);
	tmp	= TTF_RenderText_Shaded(font, str, color, TRANSPARENT);
	surface = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0);
	SDL_FreeSurface(tmp);
	tmp = NULL;
    draw_img(env,(t_edge){{pos.x, pos.y},{pos.x + surface->w, pos.y + surface->h}}, surface, (t_ixy){0, 0});
	SDL_FreeSurface(surface);
	surface = NULL;
	TTF_CloseFont(font);
	font = NULL;
    return (1);
}

SDL_Surface	*str_join_text(t_font data, TTF_Font *font)
{
	char		*strjoin;
	SDL_Surface	*new;

	strjoin = NULL;
	if (data.l > -1)
	{
		if (!(strjoin = ft_strljoin(ft_itoa(data.l), (char *)data.str)))
			return (NULL);
	}
	else if (data.r > -1)
	{
		if (!(strjoin = ft_strrjoin((char *)data.str, ft_itoa(data.r))))
			return (NULL);
	}
	if (!(new = TTF_RenderText_Shaded(font, strjoin ? strjoin : data.str, data.color, TRANSPARENT)))
		return (0);
	if (strjoin)
		free(strjoin);
	return (new);
}

int    ui_put_string(t_env *env, t_font	data)
{
	SDL_Surface	    *surface;
	SDL_Surface		*tmp;
	TTF_Font		*font;
	const t_vtx		pos = data.pos;

	if (!(font = TTF_OpenFont(data.font, data.size)))
        return (0);
	if (!(tmp = str_join_text(data, font)))
		return (0);
	if (!(surface = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0)))
		return (0);
	SDL_FreeSurface(tmp);
	tmp = NULL;
    draw_img(env,(t_edge){{pos.x, pos.y},{pos.x + surface->w, pos.y + surface->h}}, surface, (t_ixy){0, 0});
	SDL_FreeSurface(surface);
	surface = NULL;
	TTF_CloseFont(font);
	font = NULL;
    return (1);
}

int    ui_put_fps(t_env *env, int fps)
{
	ui_put_string(env, (t_font){RED, "fps : ", F_NUMB, (t_vtx){10, 10}, 20, -1, fps});
    return (1);
}
// typedef struct	s_font
// {
// 	SDL_Color	color;
// 	const char	*str;
// 	const char	*font;
// 	t_vtx		pos;
// 	int			size;
// 	int			num;
// }				t_font;

int     ui_txt_inv(t_env *env)
{
	ui_put_string(env, (t_font){BLACK, "Inventory", F_DOOM, (t_vtx){20, 15}, 60, -1, -1});
	ui_put_string(env, (t_font){BLACK, "Weapons", F_DOOM, (t_vtx){20, H / 1.7}, 40, -1, -1});
	ui_put_string(env, (t_font){BLACK, "Level : ", F_DOOM, (t_vtx){W - (W / 3), 15}, 60, -1, 1});
    ui_put_string(env, (t_font){BLUE, "Sector : ", F_TEXT, (t_vtx){W - W / 3.2, 95}, 25, -1, env->engine.player.sector});
    ui_put_string(env, (t_font){RED, "Enemies to kill : ", F_TEXT, (t_vtx){W - W / 3.1, 125}, 20, -1, 1});
    return (1);
}

int		ui_icon_data(t_env *env, t_vtx v, int iter)
{
	int				data;
	SDL_Color 		c;
	const SDL_Color	clrs[4] = {
		{8, 255, 8, 255},
		{42, 204, 242, 255},
		{242, 204, 42, 255},
		{255, 0, 0, 255}};

	if (iter == 0)
	{
		data = env->player.health;
		c = clrs[0];
	}
	else if (iter == 1)
	{
		data = env->player.shield;
		c = data < 200 ? clrs[1] : clrs[2];
	}
	else
	{
		data = 9942;
		c = clrs[1];
	}
	if (data < 100)
		c = clrs[3];
	ui_put_string(env, (t_font){c, "%", F_TEXT, (t_vtx){v.x + 15, v.y + 8}, 28, data, -1});
	return (1);
}

int	ui_text_msg(t_env *env, char *msg)
{
	ui_put_string(env, (t_font){(SDL_Color){255, 255, 255, 255}, msg,
	F_TEXT, (t_vtx){50, H - H / 2.5}, 20, -1, -1});
	return (0);
}

int	ui_draw_msg(t_env *env, int *nb, int *tframe)
{
	if (*nb)
	{
		if (*nb == 1)
			ui_text_msg(env, "Already full shield !");
		else if (*nb == 2)
			ui_text_msg(env, "No shield in stock, stop crying & find some");
		else if (*nb == 3)
			ui_text_msg(env, "Already full of life, enjoy mate !");
		else if (*nb == 4)
			ui_text_msg(env, "No heal in stock, hang on !");
		else if (*nb == 5)
			ui_text_msg(env, "Too greedy man.. Already full stack of this item");
		else if (*nb == 6)
			ui_text_msg(env, "New item placed in inventory");
		else if (*nb == 7)
			ui_text_msg(env, "Inventory full - Max 6 different items");
		else if (*nb == 8)
			ui_text_msg(env, "Item suppressed from inventory");
		else if (*nb == 9)
			ui_text_msg(env, "Weapon already full");
		else if (*nb == 10)
			ui_text_msg(env, "No ammo for this weapon");
		else if (*nb == 11)
			ui_text_msg(env, "JetPack ON");
		else if (*nb == 12)
			ui_text_msg(env, "JetPack OFF");
		else if (*nb == 13)
			ui_text_msg(env, "No JetPack here, keep looking bro !");
		if (*tframe < 60)
			++(*tframe);
		else
		{
			*tframe = 0;
			*nb = 0;
		}
	}
	return (0);
}
