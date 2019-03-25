/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:27:35 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/25 18:56:15 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_H
# define LIBUI_H

# define WIN_H 800
# define WIN_W 1200
# define C_CYAN	0xFFFFCE33

// Start

void			ui_init_sdl(t_data *data);
void			ui_make_window(char *name, t_data *data);
void			ui_load_font(char *path, t_data *data);
SDL_Surface		*ui_load_image(char *path, t_env *env);

// Other

void			ui_make_frame(void (*fc)(t_env *env), t_env *env);
void			ui_gameloop(int (*event)(t_env *env),
				void (*fc)(t_env *env), t_env *env);

// Lowcode graphics

SDL_Surface		*ui_make_surface(int height, int width);
void			ui_set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

// Making objects

void			ui_make_line(SDL_Surface *surface,
				t_vec vec, Uint32 color);
void			ui_make_dotted_line(SDL_Surface *surface,
				t_vec vec, Uint32 color);
void			ui_make_rect(SDL_Surface *surface, t_rect rect);
void    		ui_make_full_rect(SDL_Surface *surface, 
				SDL_Rect rect, Uint32 color);
void			ui_make_circle(t_circ circ, t_data *data);
void			ui_make_string(t_rect rect, char *text, t_data *data);
void			ui_make_nbrstring(t_rect rect, int value, t_data *data);
void			ui_make_input(SDL_Surface *surface, t_elem *elem, t_data *data);

// Events handling

int				ui_get_events(int (*event)(t_env *env), t_env *env);

// Utils
SDL_Color		ui_hex_to_rgb(int hexa);
int				ui_mouseenter(int x, int y, t_rect rect);
int				ui_close_to(t_pos a, t_pos b, float dist);

// Exit

void			ui_exit_sdl(t_data *data);
void			ui_error_exit_sdl(char *msg, t_data *data);

#endif
