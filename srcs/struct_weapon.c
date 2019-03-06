#include "doom.h"

static int weapon_mask(long ref, int pos)
{
    return (((ref >> (pos << 2)) & 0xFF));
}

/*
** Protect this area
** from null malloc
*/

SDL_Surface **weapon_fill(char *path, int size)
{
    int     i;
    SDL_Surface **weapons;
    char    *filename;

    i = 0;
    if ((weapons = malloc(sizeof(SDL_Surface *) * size)) == NULL)
        return (NULL);
    while (i < size)
    {
        filename = ft_strrjoin((char *)path, ft_itoa(i + 1));
        weapons[i] = img_wpn(filename);
        free(filename);
        filename = NULL;
        i++;
    }
    return (weapons);
}

void weapon_set(t_weapon *weapon, char *name, int dam)
{
    char *r_path;
    char *s_path;
    char *sprite;
    long ref;

    ref = weapon->ref;
    weapon->type = (ref & 0xF);
    weapon->time_reload = weapon_mask(ref, 1);
    weapon->time_shoot = weapon_mask(ref, 3);
    weapon->time_shoot_between = weapon_mask(ref, 5);
    weapon->ammo_current = weapon_mask(ref, 7);
    weapon->ammo_magazine = weapon_mask(ref, 9);
    weapon->damage = dam;
    r_path = ft_strjoin(name, "/reload/");
    s_path = ft_strjoin(name, "/shoot/");
    sprite = ft_strjoin(name, "/");
    sprite = ft_strljoin(sprite, name);
    weapon->sprite = img_wpn(sprite);
    weapon->sprite_reload = weapon_fill(r_path, weapon->time_reload);
    weapon->sprite_shoot = weapon_fill(s_path, weapon->time_shoot);
    free(r_path);
    free(s_path);
    free(sprite);
}

SDL_Surface *ui_wpn_img(char *filename)
{
	SDL_Surface	*new;
	char		*path;
	const char	*png = ".png";

	path = ft_strjoin("./rsrc/img/inventory/wpn/", filename);
	path = ft_strljoin(path, (char *)png);
	new = surface_fr_png(path);
	free(path);
	path = NULL;
	return (new);
}

int     init_wpn_inv(t_env *env)
{
    env->player.inventory.ui.mini_wpn[0] = ui_wpn_img("lmini_ak");
    env->player.inventory.ui.mini_wpn[1] = ui_wpn_img("lmini_pistol");
    env->player.inventory.ui.mini_wpn[2] = ui_wpn_img("lmini_rifle");
    env->player.inventory.ui.hud_wpn[0] = ui_wpn_img("hud_ak");
    env->player.inventory.ui.hud_wpn[1] = ui_wpn_img("hud_pistol");
    env->player.inventory.ui.hud_wpn[2] = ui_wpn_img("hud_rifle");
    env->player.inventory.ui.empt_wpn[0] = ui_wpn_img("empty_ak");
    env->player.inventory.ui.empt_wpn[1] = ui_wpn_img("empty_pistol");
    env->player.inventory.ui.empt_wpn[2] = ui_wpn_img("empty_rifle");
    return (0);
}

int		init_weapon(t_env *env)
{
	env->world.armory[1].ref = 0xa1e0502061a1;
	env->world.armory[0].ref = 0xa2a0602092a2;
	env->world.armory[2].ref = 0xa8e2002102f3;
	weapon_set(&env->world.armory[1], "ak47", 12);
	weapon_set(&env->world.armory[0], "pistol", 17);
	weapon_set(&env->world.armory[2], "rifle", 30);
    env->player.inventory.weapons[0] = &env->world.armory[0];
    env->player.inventory.weapons[1] = &env->world.armory[1];
    env->player.inventory.weapons[2] = &env->world.armory[2];
    env->player.inventory.current = env->player.inventory.weapons[0];
    env->player.inventory.ui.front_pic = surface_fr_png("./rsrc/img/inventory/fond.png");
	env->player.inventory.ui.wwheel = 0;
    env->player.inventory.ui.nb_wpn = 3;    
    env->player.inventory.nb_current_obj = 0;
    init_wpn_inv(env);
    return (0);
}