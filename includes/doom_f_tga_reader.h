
#ifndef DOOM_F_TGA_READER_H
# define DOOM_F_TGA_READER_H

SDL_Surface		*load_texture(const char *path);
void			sym_vert(t_tga *tga);
void			rotatepxl(t_tga *tga);
void			fill(t_tga *tga, unsigned char *base, unsigned char *tofill, int bpp);
unsigned char	*pxlbasecm(t_tga *tga, unsigned char *newstr);
unsigned char	*pxlbase(t_tga *tga, unsigned char *newstr);
int				createpxl(t_tga *tga);
int				uncompress(t_tga *tga);
int				getheader(t_tga *tga);
int				getcm(t_tga *tga);
int				getdata(t_tga *tga);
int				getfile(t_tga *tga, const char *path);
void			*cleartga(t_tga *tga);
int				inittga(t_tga *tga);
t_tga			*load_tga(const char *path);

#endif
