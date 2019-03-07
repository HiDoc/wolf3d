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

    (void)env;
	if (!(font = TTF_OpenFont("rsrc/font/interbureau.ttf", pos.z)))
        return (0);
	surface	= TTF_RenderText_Blended(font, str, color);
    draw_img(env,(t_edge){{pos.x, pos.y},{pos.x + surface->w, pos.y + surface->h}}, surface, (t_ixy){0, 0});
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
    return (1);
}

int    doom_font(t_env *env, char *str, t_vctr pos, SDL_Color color)
{
	SDL_Surface	    *surface;
	TTF_Font        *font;

    (void)env;
	if (!(font = TTF_OpenFont("rsrc/font/AmazDooMLeft2.ttf", pos.z)))
        return (0);
	surface	= TTF_RenderText_Blended(font, str, color);
    draw_img(env,(t_edge){{pos.x, pos.y},{pos.x + surface->w, pos.y + surface->h}}, surface, (t_ixy){0, 0});
	SDL_FreeSurface(surface);
	str = NULL;
	TTF_CloseFont(font);
    return (1);
}

int    ui_put_fps(t_env *env, int fps)
{
	char            *fps_count;

	if (!(fps_count = ft_strrjoin("fps : ", ft_itoa(fps))))
        return (0);
	text_font(env, fps_count, (t_vctr){10, 10, 20},  (SDL_Color){255, 0, 0, 255});
	free(fps_count);
    return (1);
}

// void    ui_put_health(t_env *env)
// {
// 	health(env);
// 	put_img(env, env->life.img, 20, 400);
// }

int     ui_txt_inv(t_env *env)
{
	char	*tmp;
	char	*ptr;

	doom_font(env, "Inventory", (t_vctr){20, 15, 60}, (SDL_Color){255, 255, 255, 255});
    doom_font(env, "Weapons", (t_vctr){20, H / 1.7, 40}, (SDL_Color){255, 255, 255, 255});
	if (!(tmp = ft_strrjoin("Level : ", ft_itoa(1))))
		return (0);
    doom_font(env, tmp, (t_vctr){505, 15, 60}, (SDL_Color){255, 255, 255, 0});
	free(tmp);
	if (!(tmp = ft_strrjoin("Sector : ", ft_itoa(env->engine.player.sector))))
		return (0);
    text_font(env, tmp, (t_vctr){535, 95, 25}, (SDL_Color){255, 255, 255, 0});
	free(tmp);
	ptr = ft_strrjoin("Keys found : ", ft_itoa(0));
	if (!(tmp = ft_strrjoin(ptr, ft_strrjoin("/", ft_itoa(4)))))
		return (0);
    text_font(env, tmp, (t_vctr){525, 125, 20}, (SDL_Color){0, 0, 255, 0});
	free(ptr);
	free(tmp);
    return (0);
}

int		ui_icon_data(t_env *env, t_vtx v, int iter)
{
	int			data;
	SDL_Color	c;

	if (iter == 0)
	{
		data = env->player.health;
		c = (SDL_Color){8, 167, 8, 8};
	}
	else if (iter == 1)
	{
		data = env->player.shield;
		c = data < 200 ? (SDL_Color){242, 204, 42, 255} : (SDL_Color){0, 191, 255, 0};
	}
	else
	{
		data = 9942;
		c = (SDL_Color){42, 204, 242, 255};
	}
	if (data < 100)
		c = (SDL_Color){0, 0, 255, 0};
	text_font(env, ft_strljoin(ft_itoa(data), "%"),
	(t_vctr) {v.x + 15, v.y + 8, 28}, c);
	return (1);
}

// int		use_drop_inv(t_env *, t_edge **blocs, int)