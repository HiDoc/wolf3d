/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:23:15 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/08 20:13:14 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom.h"

static void		initialisation_sdl(t_env *env)
{
	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		doom_error_exit("Doom_nukem error, can't SDL_Init", env);

	// init window
	if (!(env->sdl.window = SDL_CreateWindow("Doom nukem",
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN)))
		doom_error_exit("Doom_nukem error, can't create window", env);

	// SDL_SetWindowFullscreen(env->sdl.window, SDL_WINDOW_FULLSCREEN);

	// init renderer
	if (!(env->sdl.renderer = SDL_CreateRenderer(env->sdl.window, -1, 0)))
		doom_error_exit("Doom_nukem error, can't create renderer", env);

	// init main surface
	if (!(env->sdl.surface = SDL_CreateRGBSurface(0, W, H, 32,
					0xff000000, 0xff0000, 0xff00, 0xff)))
		doom_error_exit("Doom_nukem error, can't create surface", env);

	// init main texture
	if (!(env->sdl.texture = SDL_CreateTexture(env->sdl.renderer,
					SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, W, H)))
		doom_error_exit("Doom_nukem error, can't create texture", env);
}

static void		initialisation_sound_text(t_env *env)
{
	if (TTF_Init() < 0)
		doom_error_exit("Doom_nukem error, can't TTF_Init", env);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096))
		doom_error_exit("Doom_nukem error, can't Mix_OpenAudio", env);
}

static void		initialisation_cursor(t_env *env)
{
	SDL_Cursor* cursor;

	if (!(cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR)))
		doom_error_exit("Doom_nukem error on SDL_CreateSystemCursor", env);
	SDL_SetCursor(cursor);
	if ((SDL_SetRelativeMouseMode(SDL_TRUE)) < 0)
		doom_error_exit("Doom_nukem error on SDL_SetRelativeMouseMode", env);
}

static void		init_pack_img(t_surface *pack, char *name, int limit, t_env *env)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		if (!(pack[i].sprite = ui_img(name, i)))
			doom_error_exit("Doom_nukem error ???", env);
		i++;
	}
}

static void		load_enemies(t_world *container, t_env *env)
{

	int		i;
	int		j;
	// char	*tmp;
	// int		ret;

	i = 0;
	// ret = 0;
	while (i < WORLD_NB_ENEMIES)
	{
		j = 0;
		// printf("i %i\n", i);
		while (j < 6)
		{
			// tmp = NULL;
			// if ((tmp = ft_itoa(i) && tmp = (ft_strrjoin("enemies/", tmp))
			if (!(container->enemies[i].sprites[j]=ui_img("enemies/suitguy/", j)))
				doom_error_exit("Doom_nukem error ???", env);
			// printf("sprite init\n");
			// printf("j %i\n", j);
			// 	ret = 1;
			// else
			// 	ret = 0;
			// if (tmp)
			// 	free(tmp);
			// if (!ret)
			j++;
		}
		i++;
	}
}

static void		init_container(t_env *env)
{
	t_container	*surface;

	surface = &env->world.surfaces;
	init_pack_img(env->world.surfaces.poster, "posters/", WORLD_NB_POSTERS, env);
	init_pack_img(env->world.surfaces.walls, "walls/", WORLD_NB_WALLS, env);
	init_pack_img(env->world.surfaces.floors, "floors/", WORLD_NB_FLOORS, env);
	init_pack_img(env->world.surfaces.hud, "hud/", NB_HUD_OBJ, env);
	load_enemies(&env->world, env);
}

static void         init_fonts(t_uitxt *f, t_env *env)
{
	if (!(f->arial = TTF_OpenFont(F_ARIAL, 100)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont", env);
	if (!(f->doom = TTF_OpenFont(F_DOOM, 100)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont", env);
	if (!(f->text = TTF_OpenFont(F_TEXT, 100)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont", env);
	if (!(f->number = TTF_OpenFont(F_NUMB, 100)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont", env);
}

static void			object_new(t_object *new, int i, int max_stack, t_env *env)
{
	new->max_stack = max_stack;
	if (!(new->sprite = ui_img("consumable/", i)))
		doom_error_exit("Doom_nukem error ???", env);
}

static void			init_consumable(t_env *env)
{
	int i;

	i = 0;
	while (i < WORLD_NB_OBJECTS)
	{
		if (i < WORLD_NB_CSMBLE)
			object_new(&env->world.objects[i], i, i == 5 ? 1 : 5, env);
		else if (i > WORLD_NB_CSMBLE + WORLD_NB_GEMS)
			object_new(&env->world.objects[i], i, 0, env);
		else
			object_new(&env->world.objects[i], i, -1, env);
		i++;
	}
	env->hud.inventory.is_active = 0;
	ft_bzero(&env->player.inventory, sizeof(t_inventory));
	printf("time consumable: %u\n", SDL_GetTicks());
}

static void			init_character(t_character *new, t_env *env)
{
	int i;

	i = -1;
	ft_bzero(&new->actions, sizeof(new));
	new->health = 200;
	new->shield = 200;
	new->max_health = 200;
	new->max_shield = 200;
	if (!(new->bullet = ui_img("bullet/", 0))
			|| !(new->shot = malloc(sizeof(t_impact) * PLYR_NB_SHOT)))
		doom_error_exit("Doom_nukem error ???", env);
	while (++i < PLYR_NB_SHOT)
		ft_bzero(&new->shot[i], sizeof(t_impact));
}

SDL_Surface	*ui_create_simple_string(t_font data)
{
	SDL_Surface	*tmp;
	SDL_Surface	*surface;
	int			ret;

	ret = 0;
	tmp = NULL;
	surface = NULL;
	if ((tmp = TTF_RenderText_Shaded(data.font, data.str, data.color, TRANSPARENT))
	&& (surface = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0)))
		ret = 1;
	if (tmp)
		SDL_FreeSurface(tmp);
	if (!ret && surface)
		SDL_FreeSurface(surface);
	if (!ret)
		return (NULL);
	return (surface);
}

static int	set_inv_strings(t_env *env)
{
	const char	*string[DSCRIP_STR_INV] = {I_STRING_0, I_STRING_1, I_STRING_2, I_STRING_3, I_STRING_4,
	I_STRING_5, I_STRING_6, I_STRING_7, I_STRING_8, I_STRING_9, I_STRING_10, I_STRING_11};
	int	i;

	i = 0;
	while (i < DSCRIP_STR_INV)
	{
		if (!(env->hud.text.i_obj_description[i] = ui_create_simple_string((t_font){WHITE,
		string[i], env->hud.text.text, (t_vtx){0, 0}, 0, -1, -1})))
			return (0);
		i++;
	}
	return (1);
}

static int	set_pick_strings(t_env *env)
{
	const char	*string[HUD_PICK_OBJ] = {P_STRING_0, P_STRING_1, P_STRING_2, P_STRING_3, P_STRING_4,
	P_STRING_5, P_STRING_6, P_STRING_7, P_STRING_8, P_STRING_9, P_STRING_10, P_STRING_11,
	P_STRING_12, P_STRING_13, P_STRING_14};
	int	i;

	i = 0;
	while (i < HUD_PICK_OBJ)
	{
		if (!(env->hud.text.pick_objects[i] = ui_create_simple_string((t_font){WHITE,
		string[i], env->hud.text.text, (t_vtx){0, 0}, 0, -1, -1})))
			return (0);
		i++;
	}
	return (1);
}

static int		set_simple_strings(t_env *env, int i, int j)
{
	const char      *string[UI_NB_STRING] = {STRING_0, STRING_1, STRING_2, STRING_3    , STRING_4,
		STRING_5, STRING_6, STRING_7, STRING_8, STRING_9, STRING_10, STRING_11,
		STRING_12, STRING_13, STRING_14, STRING_15, STRING_16, STRING_17, STRING_18,
		STRING_19, STRING_20, STRING_21, STRING_22, STRING_23, STRING_24, STRING_25,
		STRING_26, STRING_27, STRING_28, STRING_29};
	TTF_Font        *font;

	while (i < UI_NB_STRING)
	{
		if (i < UI_NB_STRING - UI_NB_STR_INV)
		{
			if (!(env->hud.text.string[i] = ui_create_simple_string((t_font){WHITE,
							string[i], env->hud.text.text, (t_vtx){0, 0}, 0, -1, -1})))
				return (0);
		}
		else
		{
			font = j != 2 && j < 6 ? env->hud.text.doom : env->hud.text.text;
			if (!(env->hud.text.t_inv[j] = ui_create_simple_string((t_font){WHITE,
							string[i], font, (t_vtx){0, 0}, 0, -1, -1})))
				return (0);
			j++;
		}
		i++;
	}
	return (set_inv_strings(env) && set_pick_strings(env));
}

static int	init_icon_bloc(t_uinv *inventory, t_container *surfaces)
{
	int 		i;
	int			ref;
	SDL_Rect	rect;
	int			inter;

	inter = W / 8;
	ref = 0;
	rect = (SDL_Rect){W / 24, H - H / 11, W / 21, H / 15.5};
	i = ICON_SLOT_1;
	while (i < FACE_1)
	{
		inventory->icons[ref] = (t_bloc){
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		NULL, NULL, surfaces->hud[i].sprite, rect, ref, 1,
		(t_edge){{0, 0}, {0, 0}}};
		rect.x += rect.w + inter;
		i++;
		ref++;
	}
	return (1);
}

static int	init_hp_bloc(t_hud *hud, t_container *surfaces)
{
	int 		i;
	int 		rfaces;
	int 		rbars;
	SDL_Rect	rect;

	rfaces = 0;
	rbars = 0;
	rect = (SDL_Rect){W / 128, H - H / 2.8, W / 3, H / 4};
	i = FACE_1;
	while (i < W_SLOT_1)
	{
		if (i < HP_BAR_1)
		{
			hud->faces[rfaces] = (t_bloc){
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
			NULL, NULL, surfaces->hud[i].sprite, rect, rfaces, 0,
			(t_edge){{0, 0}, {0, 0}}};
			rfaces++;
		}
		else
		{
			hud->bar[rbars] = (t_bloc){
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
			NULL, NULL, surfaces->hud[i].sprite, rect, rbars, 0,
			(t_edge){{0, 0}, {0, 0}}};
			rbars++;
		}
		i++;
	}
	return (1);
}

static int	init_hwpn_bloc(t_hud *hud, t_container *surfaces)
{
	int			index;
	int			i;
	SDL_Rect	rect;

	rect = (SDL_Rect){W - W / 6, H / 1.2, W / 10, H / 7};
	i = HUD_PISTOL;
	index = 0;
	while (i <= HUD_W_LAST)
	{
		hud->hud_wpn[index] = (t_bloc){
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		NULL, NULL, surfaces->hud[i].sprite, rect, index, 0,
		(t_edge){{0, 0}, {0, 0}}};
		i++;
		index++;
	}
	return (1);
}

static t_minibloc	fill_minibloc(SDL_Rect brect, SDL_Surface *img, t_vctr size)
{
	SDL_Rect	rect;
	t_minibloc	new;

	rect = (SDL_Rect){brect.x + brect.w - brect.w / size.x,
	size.z, brect.w / size.x, brect.h / size.y};

	new = (t_minibloc) {rect, img};
	return (new);
}

static int	init_iwpn_bloc(t_hud *hud, t_uinv *inventory, t_container *surfaces)
{
	int			i;
	int			j;
	int			index;
	SDL_Rect	rect;
	int			inter;

	inter = W / 64;
	rect = (SDL_Rect){W / 32, H / 1.45, W / 10, H / 10};
	i = W_SLOT_1;
	j = INV_PISTOL;
	index = 0;
	while (i < INV_PISTOL && j < HUD_PISTOL)
	{
		inventory->wpn[index] = (t_bloc){
		(t_minibloc){(SDL_Rect){rect.x, rect.y, rect.w / 6, rect.w / 6},
		hud->text.t_inv[2]}, (t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		surfaces->hud[i].sprite, surfaces->hud[j].sprite, NULL,
		rect, index, 0, (t_edge){{0, 0}, {0, 0}}};
		rect.x = i == W_SLOT_1 + 2 ? W / 32 : rect.x + rect.w + inter;
		rect.y = i > W_SLOT_1 + 1 ? inter / 2 + rect.y + rect.h : rect.y;
		i++;
		j++;
		index++;
	}
	return (1);
}

static int	init_iobjects_bloc(t_env *env, t_hud *hud, t_uinv *inventory)
{
	int			i;
	SDL_Rect	rect;
	int			interx;
	int			intery;

	interx = W / 128;
	intery = H / 6.2;
	rect = (SDL_Rect){W / 28, intery, W / 11, W / 11};
	i = 0;
	while (i < 6)
	{
		inventory->objects[i] = (t_bloc){
		fill_minibloc(rect, hud->text.t_inv[2], (t_vctr){5, 4, rect.y}),
		fill_minibloc(rect, hud->text.t_inv[3],
		(t_vctr){4, 4, rect.y + rect.h - rect.h / 4}),
		env->world.surfaces.hud[BOX_E].sprite,
		env->world.surfaces.hud[BOX_F].sprite,
		NULL, rect, i, 0, (t_edge){{0, 0}, {0, 0}}};
		rect.x = i == 2 ? W / 28 : rect.x + interx + rect.w;
		rect.y = i < 2 ? intery : interx + intery + rect.h;
		i++;
	}
	return (1);
}

static int	init_hobjects_bloc(t_hud *hud, t_container *surfaces)
{
	int			i;
	SDL_Rect	rect;
	int			interx;

	interx = W / 404;
	rect = (SDL_Rect){W - W / 1.22, H - H  / 8, W / 20, W / 20};
	i = 0;
	while (i < 5)
	{
		hud->objects[i] = (t_bloc){(t_minibloc)
		{(SDL_Rect){rect.x + rect.w / 2, rect.y - W / 700,
		rect.w / 6, rect.w / 6}, hud->text.t_inv[i + 6]},
		(t_minibloc){(SDL_Rect){rect.x,
		rect.y + rect.h - rect.w / 6, rect.w / 6, rect.w / 6}, NULL},
		surfaces->hud[BOX_E].sprite, surfaces->hud[BOX_F].sprite,
		NULL, rect, i, 0, (t_edge){{0, 0}, {0, 0}}};
		rect.x += interx + rect.w;
		i++;
	}
	return (1);
}

static int	init_inv_bg(t_uinv *inventory, SDL_Surface *img)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){0, 0, W, H};
	inventory->bg = (t_bloc){{{0, 0, 0, 0}, NULL},
	{{0, 0, 0, 0}, NULL},
	NULL, NULL, img, rect, 0, 0, {{0, 0}, {0, 0}}};
	return (1);
}

static int	init_igems_bloc(t_uinv *inventory, t_container *surfaces)
{
	int			i;
	SDL_Rect	rect;
	int			inter;
	int			size;

	inter = W / 132;
	size = W / 17;
	rect = (SDL_Rect){W / 32, H / 1.9, size, size};
	i = 0;
	while (i < WORLD_NB_GEMS)
	{
		inventory->gems[i] = (t_bloc){(t_minibloc)
		{(SDL_Rect){0, 0, 0, 0}, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		surfaces->hud[BOX_E].sprite, surfaces->hud[BOX_F].sprite,
		NULL, rect, i, 0, (t_edge){{0, 0}, {0, 0}}};
		rect.x += inter + size;
		i++;
	}
	return (1);
}

static int	init_hud_blocs(t_env *env)
{
	int	i_tab;
	t_hud	*hud;
	t_uinv	*inv;

	i_tab = 0;
	hud = &env->hud;
	inv = &env->hud.inventory;
    env->hud.is_txt = 0;
	return (init_inv_bg(inv, env->world.surfaces.hud[0].sprite)
	&& init_igems_bloc(inv, &env->world.surfaces)
	&& init_icon_bloc(inv, &env->world.surfaces)
	&& init_iwpn_bloc(hud, inv, &env->world.surfaces)
	&& init_iobjects_bloc(env, hud, inv)
	&& init_hp_bloc(hud, &env->world.surfaces)
	&& init_hwpn_bloc(hud, &env->world.surfaces)
	&& init_hobjects_bloc(hud, &env->world.surfaces));
}

static int weapon_mask(long ref, int pos)
{
	return (((ref >> (pos << 2)) & 0xFF));
}

static t_bloc *weapon_fill(t_weapon *mother, char *path, int size)
{
	int	i;
	t_bloc		*weapons;

	if (!(weapons = malloc(sizeof(t_bloc) * size)))
		return (NULL);

	i = 0;
	// (void)mother;
	// while (i < size)
	// {
	// 	if (!current_sprite(&weapons[i], path, i))
	// 		return (0);
	// 	i++;
	// }
	init_thread(mother, weapons, path, size);
	return (weapons);
}


static int     weapon_sprites(t_weapon *weapon, char *name)
{
	char	*r_path;
	char	*s_path;
	char	*sprite;
	int		ret;

	ret = 0;
	r_path = NULL;
	s_path = NULL;
	sprite = NULL;
	if ((r_path = ft_strjoin(name, "/reload/"))
	&& (s_path = ft_strjoin(name, "/shoot/"))
	&& (sprite = ft_strjoin(name, "/"))
	&& (current_sprite(&weapon->sprite, sprite, 0))
	&& (weapon->sprite_reload = weapon_fill(weapon, r_path, weapon->time_reload))
	&& (weapon->sprite_shoot = weapon_fill(weapon, s_path, weapon->time_shoot)))
		ret = 1;
	if (r_path)
		free(r_path);
	if (s_path)
		free(s_path);
	if (sprite)
		free(sprite);
	return (ret);
}

static int weapon_set(t_weapon *weapon, char *name, int dam, t_vctr ray_scope_vel, int devset)
{
	long	ref;

	ref = weapon->ref;
	weapon->type = (ref & 0xF);
	weapon->time_reload = weapon_mask(ref, 1);
	weapon->time_shoot = weapon_mask(ref, 3);
	weapon->time_shoot_between = weapon_mask(ref, 5);
	weapon->ammo_curr_max = weapon_mask(ref, 7);
	weapon->ammo_mag_max = weapon_mask(ref, 9);
	weapon->ammo_current = weapon_mask(ref, 7);
	weapon->ammo_magazine = weapon_mask(ref, 9);
	weapon->damage = dam;
	weapon->ray = ray_scope_vel.x;
	weapon->scop = ray_scope_vel.y;
	weapon->velocity = ray_scope_vel.z;
	(void)name;
	if (devset)
	{
		if (!weapon_sprites(weapon, name))
			return (0);
	}
	return (1);
}

int		init_weapon(t_env *env)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_WEAPONS)
		env->player.inventory.weapons[i++].current = NULL;
	env->player.inventory.current = NULL;
	env->world.armory[MAGNUM].ref = 0xa2a0601042a2;
	env->world.armory[SHOTGUN].ref = 0xa2a020105123;
	env->world.armory[RIFLE].ref = 0xa8e2000042a4;
	env->world.armory[RPG].ref = 0xa08010108242;
	env->world.armory[FIST].ref = 0xa00000103002;
	weapon_set(&env->world.armory[MAGNUM], "weapons/magnum", 56, (t_vctr){R_MAGNUM, S_MAGNUM, V_MAGNUM}, 0);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[SHOTGUN], "weapons/pompe", 100, (t_vctr){R_SHOTGUN, S_SHOTGUN, V_SHOTGUN}, 0);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[RIFLE], "weapons/rifle", 30, (t_vctr){R_RIFLE, S_RIFLE, V_RIFLE}, 0);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[RPG], "weapons/rpg", 100, (t_vctr){R_RPG, S_RPG, V_RPG}, 1);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[FIST], "weapons/fist", 45, (t_vctr){R_FIST, S_FIST, V_FIST}, 1);
	printf("time weapon: %u\n", SDL_GetTicks());

	// if (weapon_set(&env->world.armory[MAGNUM], "weapons/magnum", 56, (t_vctr){R_MAGNUM, S_MAGNUM, V_MAGNUM}, 1)
	// && weapon_set(&env->world.armory[SHOTGUN], "weapons/pompe", 100, (t_vctr){R_SHOTGUN, S_SHOTGUN, V_SHOTGUN}, 1)
	// && weapon_set(&env->world.armory[RIFLE], "weapons/rifle", 30, (t_vctr){R_RIFLE, S_RIFLE, V_RIFLE}, 1)
	// && weapon_set(&env->world.armory[RPG], "weapons/rpg", 100, (t_vctr){R_RPG, S_RPG, V_RPG}, 1)
	// && weapon_set(&env->world.armory[FIST], "weapons/fist", 45, (t_vctr){R_FIST, S_FIST, V_FIST}, 1))
	// {
		env->player.inventory.f.ref = FIST;
		env->player.inventory.weapons[FIST].current = &env->player.inventory.f;
		env->player.inventory.weapons[FIST].ammo[0] = env->world.armory[FIST].ammo_current;
		env->player.inventory.weapons[FIST].ammo[1] = env->world.armory[FIST].ammo_magazine;
		env->player.inventory.weapons[FIST].ammo[2] = env->world.armory[FIST].damage;
		set_current_wpn(&env->player.inventory, FIST);
		return (1);
	// }
	return (0);
}

static int	enemy_mask(long ref, int pos)
{
	return (((ref >> (pos << 2)) & 0xFF));
}

static int	enemy_set(t_character *enemy)
{
	long	ref;

	ref = enemy->ref;
	enemy->type = (ref & 0xF);
	enemy->damage = enemy_mask(ref, 1);
	enemy->tshoot_between = enemy_mask(ref, 3);
	enemy->salve_shoot = enemy_mask(ref, 5);
	enemy->health = enemy_mask(ref, 7);
	enemy->shield = enemy_mask(ref, 9);
	return (1);
}

static int	init_enemies(t_env *env)
{
	env->world.enemies[0].ref = 0xa64640809140;
	enemy_set(&env->world.enemies[0]);
	return (1);
}

static void		init_gameplay_env(t_env *env)
{
	init_fonts(&env->hud.text, env);
	init_consumable(env);
	init_character(&env->player, env);
	set_simple_strings(env, 0, 0); //TO PROTECT
	init_hud_blocs(env);
	init_weapon(env);
	init_enemies(env);
}

void	initialisation(int ac, char **av, t_env *env)
{
	ft_bzero(env, sizeof(t_env));
	env->god_mod = (ac > 1 && ft_strcmp(av[1], "god")) ? 1 : 0;
	ft_bzero(&env->engine, sizeof(t_engine));
	initialisation_sdl(env);
	initialisation_sound_text(env);
	initialisation_cursor(env);
	init_container(env);
	init_gameplay_env(env);
}
