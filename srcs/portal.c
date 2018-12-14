// #include "wolf.h"

// t_portal	portal_pos(t_env *env, t_portal port)
// {
// 	if (env->w_map[(int)(port.pos.x + env->dir.x * 0.2)][(int)port.pos.y] == 0)
// 		port.pos.x += env->dir.x * (0.2 / 2.0);
// 	else
// 		port.hit = 1; 
// 	if (env->w_map[(int)port.pos.x][(int)(port.pos.y + env->dir.y * 0.2)] == 0)
// 		port.pos.y += env->dir.y * (0.2 / 2.0);
// 	else
// 		port.hit = 2;
// 	return (port);
// }

// t_portal	portal(t_env *env, t_portal portal)
// {
// 	portal.hit = 0;
// 	while (portal.hit == 0)
// 		portal = portal_pos(env, portal);
// 	if (portal.hit == 1)
// 	{
// 		portal.temp.x = portal.pos.x + env->dir.x * 0.2;
// 		portal.temp.y = portal.pos.y;
// 	}
// 	else
// 	{
// 		portal.temp.y = portal.pos.y + env->dir.y * 0.2;
// 		portal.temp.x = portal.pos.x;
// 	}
// 	portal.dir = rotate(env->dir, 180.0);
// 	portal.plane = rotate(env->plane, 180.0);
// 	return (portal);
// }

// t_portal	new_portal_img(t_env *env, t_portal portal)
// {
// 	if (!(portal.img = malloc(sizeof(t_img))))
// 		print_error(1, env);
// 	portal.img->iptr = mlx_new_image(E_MLX, 64, 64);
// 	portal.img->data = (int *)mlx_get_data_addr(portal.img->iptr, &portal.img->bpp, &portal.img->size_l, &portal.img->endian);
// 	portal.inout = 1;
// 	return (portal);
// }

// t_portal	save_pdata(t_env *env)
// {
// 	t_portal	temp;

// 	temp.w = WIDTH;
// 	temp.h = HEIGHT;
// 	temp.pos = env->pos;
// 	temp.dir = env->dir;
// 	temp.plane = env->plane;
// 	return (temp);
// }

// t_portal	swap_data(t_env *env, t_portal portal)
// {
// 	portal.inout = 2;
// 	env->width = portal.w;
// 	env->height = portal.h;
// 	env->pos = portal.pos;
// 	env->dir = portal.dir;
// 	env->plane = portal.plane;
// 	return (portal);
// }

// t_env		*back_pdata(t_env *env, t_portal save)
// {
// 	env->width = save.w;
// 	env->height = save.h;
// 	env->dir = save.dir;
// 	env->plane = save.plane;
// 	env->pos = save.pos;
// 	return (env);
// }

