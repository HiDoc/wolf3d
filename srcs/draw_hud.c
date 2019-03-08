#include "doom.h"

int	print_wpn_hud(t_env *env, t_weapon *wpn)
{
	int	l;
	int	r;

	put_img_inv(env, env->player.hud.hud_wpn[wpn->type - 1],
	(t_edge){{120, H / 1.5}, {320, H / 1.5 + 120}}, (t_edge){{0, 0}, {0, 0}});
	if (wpn->type - 1 == 0)
	{
		l = 2;
		r = 1;
	}
	else if (wpn->type - 1 == 2)
	{
		l = 1;
		r = 0;
	}
	else
	{
		l = 0;
		r = 2;
	}
	put_img_inv(env, env->player.hud.hud_wpn[l],
	(t_edge){{20, H / 1.5}, {110, H / 1.5 + 60}}, (t_edge){{0, 0}, {0, 0}});
	put_img_inv(env, env->player.hud.hud_wpn[r],
	(t_edge){{330, H / 1.5}, {420, H / 1.5 + 60}}, (t_edge){{0, 0}, {0, 0}});
	return (0);
}

int	action_pad(t_env *env, int ref, t_edge limits)
{
	int	i;

	i = check_object_type(env, ref);
	if (i > -1)
	{
		put_img_inv(env, env->world.objects[ref].sprite,
		limits, (t_edge){{0, 0}, {0, 0}});
	}
	return (1);
}

int	print_pad(t_env *env)
{
	int	wpad;

	wpad = (W - W / 16) - (W - W / 6);
	put_img_inv(env, env->player.hud.pad,
	(t_edge){{W - W / 6, H - H / 4}, {W - W / 16, H - H / 9}}, (t_edge){{0, 0}, {0, 0}});
	action_pad(env, 0, (t_edge){{W - W / 6 - 35, H - H / 4 + 45}, {W - W / 6, H - H / 4 + 80}});
	action_pad(env, 1, (t_edge){{W - W / 16, H - H / 4 + 45}, {W - W / 16 + 30, H - H / 4 + 75}});
	action_pad(env, 2, (t_edge){{W - W / 6 - wpad / 4, H - H / 4 - 30},
	{W - W / 6 - wpad / 4 + 30, H - H / 4}});
	return (0);
}

int print_hud(t_env *env)
{
	put_img_inv(env, env->player.inventory.ui.icon[0],
	(t_edge){{40, H - 75}, {70, H - 45}}, (t_edge){{0, 0}, {0, 0}});
	put_img_inv(env, env->player.inventory.ui.icon[1],
	(t_edge){{40, H - 115}, {70, H - 85}}, (t_edge){{0, 0}, {0, 0}});
	draw_img(env, (t_edge){{80, H - 80 - env->player.hud.empty_bar->h},
	{80 + env->player.hud.empty_bar->w, H - 80}}, env->player.hud.empty_bar, (t_ixy){0, 0});
	draw_img(env, (t_edge){{80, H - 80 - env->player.hud.bar[1]->h},
	{80 + env->player.shield, H - 80}}, env->player.hud.bar[1], (t_ixy){0, 0});
	draw_img(env, (t_edge){{80, H - 40 - env->player.hud.empty_bar->h},
	{80 + env->player.hud.empty_bar->w, H - 40}}, env->player.hud.empty_bar, (t_ixy){0, 0});
	draw_img(env, (t_edge){{80, H - 40 - env->player.hud.bar[0]->h},
	{80 + env->player.health, H - 40}}, env->player.hud.bar[0], (t_ixy){0, 0});
	print_wpn_hud(env, env->player.inventory.current);
	print_pad(env);
	return (0);
}