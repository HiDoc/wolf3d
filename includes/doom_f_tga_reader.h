

#ifndef DOOM_F_TGA_READER_H
# define DOOM_F_TGA_READER_H

//rle.c
void				rle_uncompress(t_tga *tga);

// tga_reader_file.c
void				hdr_parser(t_tga *tga, unsigned char *hdr);
int					count_n_malloc(t_tga *tga, char *str);
int					get_data_tga(t_tga *tga, const char *path);
int					tga_load(t_tga *tga, const char *path);
int					read_hdr(t_tga *tga, int fd);
int					check_tv_signature(t_tga *tga);
int					get_data_tga(t_tga *tga, const char *path);
int					read_data(t_tga *tga, int fd);
int					read_cm(t_tga *tga, int fd);

//set_pxl_color.c
void				range_pxl(t_tga *tga);

//set_data_pxl.c.c
void				fill_pxl(t_tga *tga, int i, int mode);
void				fille_pxl_from_cm(t_tga *tga);
void				fill_data(t_tga *tga, int mode);
void				create_pxl(t_tga *tga);

//tga_type_read.c
void				read_color(t_pixel *tab, int bits, unsigned char *file, int pos);
void				read_color_cm(t_pixel *tab, int bits, unsigned char *file, int pos);

//rle_color.c
int					loadnew(int bpp, unsigned char *n, unsigned char *file, int mode);

SDL_Surface			*set_surface(t_tga *tga);
SDL_Surface			*ui_make_surface(int height, int width);
SDL_PixelFormat		*fill_pxlformat(SDL_PixelFormat *fmt);


#endif