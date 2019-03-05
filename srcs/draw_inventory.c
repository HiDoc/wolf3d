#include "doom.h"

void	put_img_inv(t_env *env, SDL_Surface *img, t_edge bloc)
{
	SDL_Rect	rect;
	SDL_Surface	*new;
	Uint32		*pixls[2];

	rect.w = bloc.v2.x - bloc.v1.x;
	rect.h = bloc.v2.y - bloc.v1.y;
	rect.y = rect.w / 8;
	rect.x = rect.h / 8;
	if (img)
	{
		new = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 
		0xff000000, 0xff0000, 0xff00, 0xff);
		SDL_LockSurface(new);
		pixls[0] = new->pixels;
		pixls[1] = img->pixels;
		scale_img(pixls[0], pixls[1], rect, img);
		SDL_UnlockSurface(new);
		draw_img(env, bloc, new);
		SDL_FreeSurface(new);
	}
}

int		use_drop_icon(t_env *env, t_edge bloc, int i)
{
	float	blocx;

	blocx = bloc.v2.x - bloc.v1.x;
	env->player.inventory.objects[i].udbox[0].v1.x = bloc.v2.x - blocx / 7;
	env->player.inventory.objects[i].udbox[0].v1.y = bloc.v1.y;
	env->player.inventory.objects[i].udbox[0].v2.x = bloc.v2.x;
	env->player.inventory.objects[i].udbox[0].v2.y = bloc.v1.y + blocx / 7;
	draw_flat_rect(env->engine.surface,
	env->player.inventory.objects[i].udbox[0], 0x00000000);
	env->player.inventory.objects[i].udbox[1].v1.x = bloc.v2.x - blocx / 3;
	env->player.inventory.objects[i].udbox[1].v1.y = bloc.v2.y - blocx / 7;
	env->player.inventory.objects[i].udbox[1].v2.x = bloc.v2.x;
	env->player.inventory.objects[i].udbox[1].v2.y = bloc.v2.y;
	draw_flat_rect(env->engine.surface,
	env->player.inventory.objects[i].udbox[1], 0x0);
	return (0);
}

int		fill_bloc(t_env *env, t_edge *bloc, t_vtx *n, int i)
{
	int inter;
	int sbloc;

	inter = W / 2 / 4 / 4 / 4;
	sbloc = W / 2 / 3 - W / 2 / 4 / 4;
	bloc->v1 = (t_vtx){n->x, n->y};
	n->x += sbloc;
	n->y = i < 3 ? sbloc + H / 6 : 2 * sbloc + inter + H / 6;
	bloc->v2 = (t_vtx){n->x, n->y};
	draw_flat_rect(env->engine.surface, *bloc, 0x88888888);
	if (env->player.inventory.objects[i].current)
	{
		put_img_inv(env, 
		env->world.objects[env->player.inventory.objects[i].current->ref].sprite,
		*bloc);
		use_drop_icon(env, *bloc, i);
	}
	n->x = i == 2 ? W / 2 / 4 / 4 : n->x + inter;
	n->y = i < 2 ? H / 6 : inter + H / 6 + sbloc;
	return (1);
}

int		print_inventory(t_env *env)
{
	t_edge	edge;
	t_vtx	n;
	int		iter;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	n = (t_vtx){W / 2 / 4 / 4, H / 6};
	iter = 0;
	edge.v1 = (t_vtx){0, 0};
	edge.v2 = (t_vtx){env->engine.surface->w / 2, env->engine.surface->h};
	draw_flat_rect(env->engine.surface, edge,
	SDL_MapRGB(env->engine.surface->format, 0, 0, 0));
	while (iter < 6)
		iter += fill_bloc(env, &env->player.inventory.blocs[iter], &n, iter);
	return (0);
}
