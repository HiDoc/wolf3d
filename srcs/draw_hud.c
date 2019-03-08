#include "doom.h"

int	print_wpn_hud(t_env *env, t_weapon *wpn)
{
	put_img_inv(env, env->player.hud.hud_wpn[wpn->type - 1],
	(t_edge){{120, H / 1.5}, {320, H / 1.5 + 120}}, (t_edge){{0, 0}, {0, 0}});
	return (0);
}

int print_hud(t_env *env)
{
	put_img_inv(env, env->player.inventory.ui.icon[0], (t_edge){{40, H - 75}, {70, H - 45}}, (t_edge){{0, 0}, {0, 0}});
	put_img_inv(env, env->player.inventory.ui.icon[1], (t_edge){{40, H - 115}, {70, H - 85}}, (t_edge){{0, 0}, {0, 0}});
	draw_img(env, (t_edge){{80, H - 80 - env->player.hud.empty_bar->h},
	{80 + env->player.hud.empty_bar->w, H - 80}}, env->player.hud.empty_bar, (t_ixy){0, 0});
	draw_img(env, (t_edge){{80, H - 80 - env->player.hud.bar[1]->h},
	{80 + env->player.shield, H - 80}}, env->player.hud.bar[1], (t_ixy){0, 0});
	draw_img(env, (t_edge){{80, H - 40 - env->player.hud.empty_bar->h},
	{80 + env->player.hud.empty_bar->w, H - 40}}, env->player.hud.empty_bar, (t_ixy){0, 0});
	draw_img(env, (t_edge){{80, H - 40 - env->player.hud.bar[0]->h},
	{80 + env->player.health, H - 40}}, env->player.hud.bar[0], (t_ixy){0, 0});
	print_wpn_hud(env, env->player.inventory.current);
	return (0);
}