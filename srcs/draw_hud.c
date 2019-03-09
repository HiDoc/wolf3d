#include "doom.h"

int	print_wpn_hud(t_env *env, t_weapon *wpn)
{
	char	*tmp;

	// draw_img(env, (t_edge){{W - W / 4.5, H / 1.5},
	// {W - W / 4.5 + 190, H / 1.5 + 140}},
	// env->player.hud.shadow, (t_ixy){0, 0});
	put_img_inv(env, env->player.hud.hud_wpn[wpn->type - 1],
	(t_edge){{W - W / 4.5, H / 1.5}, {W - W / 4.5 + 190, H / 1.5 + 140}}, (t_edge){{0, 0}, {0, 0}});
	tmp = ft_itoa(env->player.inventory.current->ammo_current);
	number_font(env, tmp, (t_vctr){W - W / 4.5 + 115, H / 1.5 + 80, 30}, (SDL_Color){242, 204, 42, 255});
	free(tmp);
	tmp = NULL;
	tmp = ft_strrjoin("/", ft_itoa(env->player.inventory.current->ammo_magazine));
	number_font(env, tmp, (t_vctr){W - W / 4.5 + 130, H / 1.5 + 110, 30}, (SDL_Color){242, 204, 42, 255});
	free(tmp);
	tmp = NULL;
	return (0);
}

int	action_pad(t_env *env, int ref, t_edge limits)
{
	int	i;

	i = check_object_type(env, ref);
	if (i > -1)
		put_img_inv(env, env->world.objects[ref].sprite,
		limits, (t_edge){{0, 0}, {0, 0}});
	else
		put_img_inv(env, env->player.hud.e_pad[ref],
		limits, (t_edge){{0, 0}, {0, 0}});

	return (1);
}

int	print_pad(t_env *env)
{
	int	wpad;

	wpad = (W - W / 16) - (W - W / 6);
	put_img_inv(env, env->player.hud.pad,
	(t_edge){{W - W / 1.5, H - H / 4.5}, {W - W / 1.5 + 110, H - H / 4.5 + 110}}, (t_edge){{0, 0}, {0, 0}});
	action_pad(env, 0, (t_edge){{W - W / 1.5 - 40, H - H / 4 + 60}, {W - W / 1.5 - 5, H - H / 4 + 90}});
	action_pad(env, 1, (t_edge){{W - W / 1.5 + 110, H - H / 4 + 64}, {W - W / 1.5 + 140, H - H / 4 + 92}});
	action_pad(env, 2, (t_edge){{W - W / 1.5 + 60, H - H / 4 - 30},
	{W - W / 1.5 + 90, H - H / 4}});
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
	if (env->player.inventory.current)
		print_wpn_hud(env, env->player.inventory.current);
	print_pad(env);
	return (0);
}