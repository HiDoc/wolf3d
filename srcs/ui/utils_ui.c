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

int    text_font(t_env *env, char *str, t_vctr pos, SDL_Color color)
{
	SDL_Surface	    *surface;
	TTF_Font        *font;
	SDL_Surface		*tmp;

	if (!(font = TTF_OpenFont("rsrc/font/interbureau.ttf", pos.z)))
        return (0);
	tmp	= TTF_RenderText_Blended(font, str, color);
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

int    number_font(t_env *env, char *str, t_vctr pos, SDL_Color color)
{
	SDL_Surface	    *surface;
	TTF_Font        *font;
	SDL_Surface		*tmp;

	if (!(font = TTF_OpenFont("rsrc/font/5E.ttf", pos.z)))
        return (0);
	tmp	= TTF_RenderText_Blended(font, str, color);
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

typedef struct	s_font
{
	SDL_Color	color;
	const char	*str;
	const char	*font;
	t_vtx		pos;
	int			size;
	int			num;
}				t_font;

int    doom_font(t_env *env, t_font	data)
{
	SDL_Surface	    *surface;
	TTF_Font        *font;
	SDL_Surface		*tmp;
	t_rgba			rgba;
	const t_vtx		pos = data.pos;

	// if (!(font = TTF_OpenFont("rsrc/font/AmazDooMLeft2.ttf", pos.z)))
	if (!(font = TTF_OpenFont(data.font, data.size)))
        return (0);
	tmp	= TTF_RenderText_Blended(font, data.str, data.color);
	surface = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0);
	SetSurfaceAlpha(surface, 128, &rgba);
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
	char            *fps_count;

	if (!(fps_count = ft_strrjoin("fps : ", ft_itoa(fps))))
        return (0);
	text_font(env, fps_count, (t_vctr){10, 10, 20},  (SDL_Color){255, 0, 0, 255});
	free(fps_count);
	fps_count = NULL;
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
#define F_DOOM "rsrc/font/AmazDooMLeft2.ttf"
int     ui_txt_inv(t_env *env)
{
	char	*tmp;
	char	*ptr;
	const SDL_Color c[3] = {{255, 255, 255, 255}, {255, 255, 255, 0}, {8, 8, 255, 255}};

	// doom_font(env, "Inventory", (t_vctr){20, 15, 60}, (SDL_Color){255, 255, 255, 255});
	doom_font(env, (t_font){c[0], "Inventory", F_DOOM, (t_vtx){20, 15}, 60, -1});

    //doom_font(env, "Weapons", (t_vctr){20, H / 1.7, 40}, (SDL_Color){255, 255, 255, 255});
	doom_font(env, (t_font){c[0], "Weapons", F_DOOM, (t_vtx){20, H / 1.7}, 40, -1});

	if (!(tmp = ft_strrjoin("Level : ", ft_itoa(1))))
		return (0);
    //doom_font(env, tmp, (t_vctr){W - W / 3, 15, 60}, (SDL_Color){255, 255, 255, 0});
	doom_font(env, (t_font){c[1], (const char *)tmp, F_DOOM, (t_vtx){W - (W / 3), 15}, 60, -1});
	free(tmp);
	if (!(tmp = ft_strrjoin("Sector : ", ft_itoa(env->engine.player.sector))))
		return (0);
    text_font(env, tmp, (t_vctr){W - W / 3.2, 95, 25}, (SDL_Color){255, 255, 255, 0});
	free(tmp);
	ptr = ft_strrjoin("Keys found : ", ft_itoa(0));
	if (!(tmp = ft_strrjoin(ptr, ft_strrjoin("/", ft_itoa(4)))))
		return (0);
    text_font(env, tmp, (t_vctr){W - W / 3.1, 125, 20}, (SDL_Color){8, 8, 255, 255});
	free(ptr);
	free(tmp);
	ptr = NULL;
	tmp = NULL;
    return (1);
}

int		ui_icon_data(t_env *env, t_vtx v, int iter)
{
	int			data;
	SDL_Color	c;
	char		*tmp;

	if (iter == 0)
	{
		data = env->player.health;
		c = (SDL_Color){8, 255, 8, 255};
	}
	else if (iter == 1)
	{
		data = env->player.shield;
		c = data < 200 ? (SDL_Color){42, 204, 242, 255}  : (SDL_Color){242, 204, 42, 255};
	}
	else
	{
		data = 9942;
		c = (SDL_Color){42, 204, 242, 255};
	}
	if (data < 100)
		c = (SDL_Color){255, 0, 0, 255};
	if (!(tmp = ft_strljoin(ft_itoa(data), "%")))
		return (0);
	text_font(env, tmp, (t_vctr) {v.x + 15, v.y + 8, 28}, c);
	free(tmp);
	tmp = NULL;
	return (1);
}

int	ui_text_msg(t_env *env, char *msg)
{
	text_font(env, msg, (t_vctr){50, H - H / 2.5, 20}, (SDL_Color){255, 255, 255, 255});
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
