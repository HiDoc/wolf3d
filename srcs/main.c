#include "wolf.h"

/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */
static t_sector		*sectors = NULL;
static unsigned		NumSectors = 0;

/* Player: location */
static t_player		player;

static void			LoadData(void)
{
	FILE		*fp;
	char	Buf[256];
	char	word[256];
	char	*ptr;
	t_xy	*vert;
	t_xy	v;
	int		n;
	int		m;
	int		NumVertices;

	n = 0;
	m = 0;
	vert = NULL;
	NumVertices = 0;
	if (!(fp = fopen("map-clear.txt", "rt")))
	{
		perror("map-clear.txt");
		exit(1);
	}
	while (fgets(Buf, sizeof Buf, fp))
	{
		switch(sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
		{
			case 'v': // vertex
				sscanf(ptr += n, "%f%n", &v.y, &n);
				while (sscanf(ptr += n, "%f%n", &v.x, &n) == 1)
				{
					vert = realloc(vert, ++NumVertices * sizeof(*vert));
					vert[NumVertices-1] = v;
				}
				break;
			case 's': // sector
				sectors = realloc(sectors, ++NumSectors * sizeof(*sectors));
				t_sector *sect = &sectors[NumSectors-1];
				int* num = NULL;
				sscanf(ptr += n, "%f%f%n", &sect->floor,&sect->ceil, &n);
				for(m=0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; )
				{
					num = realloc(num, ++m * sizeof(*num));
					num[m-1] = word[0] == 'x' ? -1 : atoi(word);
				}
				sect->npoints   = m /= 2;
				sect->neighbors = malloc(m * sizeof(*sect->neighbors));
				sect->vertex    = malloc((m + 1) * sizeof(*sect->vertex));
				printf("Neightbors\n");
				for (n=0; n<m; ++n)
				{
					printf("%d: [%d]", n, num[m + n]);
					sect->neighbors[n] = num[m + n];
				}
				printf("\n\n Vertex:");
				for(n=0; n<m; ++n)
				{
					printf("[%d]", num[n]);
					sect->vertex[n+1]  = vert[num[n]]; // TODO: Range checking
				}
				printf("\n\n");
				sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
				free(num);
				break;
			case 'p':; // player
				float angle;
				sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle,&n);
				player = (t_player) { {v.x, v.y, 0}, {0,0,0}, angle,0,0,0, n }; // TODO: Range checking
				player.where.z = sectors[player.sector].floor + EyeHeight;
		}
	}
	fclose(fp);
	free(vert);
}

static void		UnloadData(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Window *window)
{
	unsigned	a;

	a = 0;
	while (a < NumSectors)
	{
		free(sectors[a].vertex);
		a++;
	}
	a = 0;
	while (a < NumSectors)
	{
		free(sectors[a].neighbors);
		a++;
	}
	free(sectors);
	sectors = NULL;
	NumSectors = 0;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	texture = NULL;
	window = NULL;
	renderer = NULL;
}

/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
static void				vline(t_line l, t_engine *e)
{
	int		*pix;
	int		y;

	pix	= (int *)e->surface->pixels;
	l.y1 = clamp(l.y1, 0, H - 1);
	l.y2 = clamp(l.y2, 0, H - 1);
	if (l.y2 == l.y1)
		pix[l.y1 * W + l.x] = l.middle;
	else if (l.y2 > l.y1)
	{
		pix[l.y1 * W + l.x] = l.top;
		y = l.y1 + 1;
		while (y < l.y2)
		{
			pix[y * W + l.x] = l.middle;
			y++;
		}
		pix[l.y2 * W + l.x] = l.bottom;
	}
}


/* 
** Check where the hole is and whether we're bumping into a wall.
*/
int		is_bumping(const t_sector *sect, float eyeheight, unsigned s)
{
	float			hole_low;
	float			hole_high;

	if (sect->neighbors[s] < 0)
	{
		hole_low = 9e9;
		hole_high = -9e9;
	}
	else
	{
		hole_low = max(sect->floor, sectors[sect->neighbors[s]].floor);
		hole_high = min(sect->ceil, sectors[sect->neighbors[s]].ceil);
	}
	return (hole_high < player.where.z + HeadMargin
			|| hole_low  > player.where.z - eyeheight + KneeHeight);
}

int		is_crossing(const t_xy p, t_xy d, const t_xy *vert, unsigned s)
{
	return (
		IntersectBox(p.x, p.y, p.x + d.x, p.y + d.y,
		vert[s].x, vert[s].y, vert[s + 1].x, vert[s + 1].y)
		&& PointSide(p.x + d.x, p.y + d.y, vert[s].x,
		vert[s].y, vert[s + 1].x, vert[s + 1].y) < 0
	);
}

void	bumping_score(t_xy *d, t_xy b)
{
	float			x2;
	float			y2;

	x2 = b.x * b.x;
	y2 = b.y * b.y;
	d->x = b.x * (d->x * b.x + b.y * d->y) / (x2 + y2);
	d->y = b.y * (d->x * b.x + b.y * d->y) / (x2 + y2);
}

void	player_moving(int *moving, int *falling, float eyeheight, int set)
{
	t_xy			d;
	int				s;
	const t_xy		p = {player.where.x, player.where.y};
	const t_sector	*sect = &sectors[player.sector];
	const t_xy		*vert = sect->vertex;

	s = -1;
	d = set ? (t_xy){player.velocity.x, player.velocity.y} : (t_xy){0, 0};
	/* Check if the player is about to cross one of the sector's edges */
	while (set && ++s < (int)sect->npoints)
	{
		if (is_crossing(p, d, vert, s) && is_bumping(sect, eyeheight, s))
		{
			bumping_score(&d, (t_xy){
				vert[s + 1].x - vert[s].x,
				vert[s + 1].y - vert[s].y});
			*moving = 0;
		}
	}
	s = -1;
	while (++s < (int)sect->npoints)
	{
		if (sect->neighbors[s] >= 0 && is_crossing(p, d, vert, s))
		{
			player.sector = sect->neighbors[s];
			break ;
		}
	}
	player.where.x += d.x;
	player.where.y += d.y;
	player.anglesin = sinf(player.angle);
	player.anglecos = cosf(player.angle);
	*falling = 1;
}

static void DrawScreen(t_engine *e)
{
	enum { MaxQueue = 32 };  // maximum number of pending portal renders
	t_item		queue[MaxQueue];
	t_item		*head;
	t_item		*tail;
	int			ytop[W];
	int			ybottom[W];
	int			renderedsectors[NumSectors];
	t_item		now;
	t_sector	*sect;

	ft_memset(ybottom, (H - 1), sizeof(int) * W);
	ft_bzero(ytop, sizeof(int) * W);
	ft_bzero(renderedsectors, sizeof(int) * NumSectors);
	head = queue;
	tail = queue;

	/* Begin whole-screen rendering from where the player is. */
	*head = (t_item) {player.sector, 0, W - 1};
	if (++head == queue + MaxQueue)
		head = queue;

	while (head != tail)
	{
		/* Pick a sector & slice from the queue to draw */
		now = *tail;
		if (++tail == queue + MaxQueue)
			tail = queue;

		if (renderedsectors[now.sectorno] & 0x21)
			continue ; // Odd = still rendering, 0x20 = give up
		++renderedsectors[now.sectorno];
		sect = &sectors[now.sectorno];
		/* Render each wall of this sector that is facing towards player. */
		int s = -1;
		while (++s < (int)sect->npoints)
		{
			/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
			t_vertex v = (t_vertex){
				sect->vertex[s + 0].x - player.where.x,
				sect->vertex[s + 0].y - player.where.y,
				sect->vertex[s + 1].x - player.where.x,
				sect->vertex[s + 1].y - player.where.y
			};
			/* Rotate them around the player's view */
			float pcos = player.anglecos;
			float psin = player.anglesin;
			t_vertex t = (t_vertex){
				v.x1 * psin - v.y1 * pcos,
				v.x1 * pcos + v.y1 * psin,
				v.x2 * psin - v.y2 * pcos,
				v.x2 * pcos + v.y2 * psin
			};
			/* Is the wall at least partially in front of the player? */
			if (t.y1 <= 0 && t.y2 <= 0)
				continue;
			/* If it's partially behind the player, clip it against player's view frustrum */
			if (t.y1 <= 0 || t.y2 <= 0)
			{
				float nearz = 1e-4f;
				float farz = 5;
				float nearside = 1e-5f;
				float farside = 20.f;
				// Find an intersection between the wall and the approximate edges of player's view
				t_xy i1 = Intersect(t.x1,t.y1,t.x2,t.y2, -nearside,nearz, -farside,farz);
				t_xy i2 = Intersect(t.x1,t.y1,t.x2,t.y2,  nearside,nearz,  farside,farz);
				if (t.y1 < nearz) {
					if (i1.y > 0)
					{
						t.x1 = i1.x;
						t.y1 = i1.y;
					}
					else
					{
						t.x1 = i2.x;
						t.y1 = i2.y;
					}
				}
				if (t.y2 < nearz) {
					if (i1.y > 0)
					{
						t.x2 = i1.x;
						t.y2 = i1.y;
					}
					else
					{
						t.x2 = i2.x;
						t.y2 = i2.y;
					}
				}
			}
			/* Do perspective transformation */
			t_vertex scale = (t_vertex){
				hfov / t.y1,
				vfov / t.y1,
				hfov / t.y2,
				vfov / t.y2
			};
			int x1 = W/2 - (int)(t.x1 * scale.x1);
			int x2 = W/2 - (int)(t.x2 * scale.x2);

			/* Verify if transformation is visible */
			if (x1 >= x2 || x2 < now.sx1 || x1 > now.sx2)
				continue ;

			/* Acquire the floor and ceiling heights, relative to where the player's view is */
			float yceil  = sect->ceil  - player.where.z;
			float yfloor = sect->floor - player.where.z;

			/* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
			int neighbor = sect->neighbors[s];
			float nyceil = 0;
			float nyfloor = 0;

			if (neighbor >= 0) // Is another sector showing through this portal?
			{
				nyceil  = sectors[neighbor].ceil  - player.where.z;
				nyfloor = sectors[neighbor].floor - player.where.z;
			}

			/* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
			#define Yaw(y,z) (y + z * player.yaw)
			int y1a = H/2 - (int)(Yaw(yceil, t.y1) * scale.y1);
			int y1b = H/2 - (int)(Yaw(yfloor, t.y1) * scale.y1);
			int y2a = H/2 - (int)(Yaw(yceil, t.y2) * scale.y2);
			int y2b = H/2 - (int)(Yaw(yfloor, t.y2) * scale.y2);
			/* The same for the neighboring sector */
			int ny1a = H/2 - (int)(Yaw(nyceil, t.y1) * scale.y1);
			int ny1b = H/2 - (int)(Yaw(nyfloor, t.y1) * scale.y1);
			int ny2a = H/2 - (int)(Yaw(nyceil, t.y2) * scale.y2);
			int ny2b = H/2 - (int)(Yaw(nyfloor, t.y2) * scale.y2);

			/* Render the wall. */
			int beginx = max(x1, now.sx1);
			int endx = min(x2, now.sx2);
			for (int x = beginx; x <= endx; ++x)
			{
				/* Calculate the Z coordinate for this point. (Only used for lighting.) */
				int z = ((x - x1) * (t.y2 - t.y1) / (x2 - x1) + t.y1) * 8;
				/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
				int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a;
				int cya = clamp(ya, ytop[x], ybottom[x]); // top
				int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b;
				int cyb = clamp(yb, ytop[x], ybottom[x]); // bottom

				/* Render ceiling: everything above this sector's ceiling height. */
				vline((t_line){x, ytop[x], cya - 1, 0x111111 , 0x222222, 0x111111}, e);

				/* Render floor: everything below this sector's floor height. */
				vline((t_line){x, cyb + 1, ybottom[x], 0x0000FF,0x0000AA,0x0000FF}, e);

				/* Is there another sector behind this edge? */
				if (neighbor >= 0)
				{
					/* Same for _their_ floor and ceiling */
					int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a;
					int	cnya = clamp(nya, ytop[x],ybottom[x]);
					int nyb = (x - x1) * (ny2b-ny1b) / (x2 - x1) + ny1b;
					int cnyb = clamp(nyb, ytop[x],ybottom[x]);

					/* If our ceiling is higher than their ceiling, render upper wall */
					unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
					vline((t_line){x, cya, cnya-1, 0, x==x1 || x==x2 ? 0 : r1, 0}, e); // Between our and their ceiling
					ytop[x] = clamp(max(cya, cnya), ytop[x], H - 1);   // Shrink the remaining window below these ceilings

					/* If our floor is lower than their floor, render bottom wall */
					vline((t_line){x, cnyb + 1, cyb, 0, x==x1 || x==x2 ? 0 : r2, 0}, e); // Between their and our floor
					ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
				}
				else
				{
					/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
					unsigned r = 0x010101 * (255 - z);
					vline((t_line){x, cya, cyb, 0, x==x1 || x==x2 ? 0 : r, 0}, e);
				}
			}
			/* Schedule the neighboring sector for rendering within the window formed by this wall. */
			if (neighbor >= 0 && endx >= beginx && (head+MaxQueue + 1 - tail) % MaxQueue)
			{
				*head = (t_item) { neighbor, beginx, endx };
				if(++head == queue+MaxQueue) head = queue;
			}
		} // for s in sector's edges
		++renderedsectors[now.sectorno];
	}
}

int		sdl_render(SDL_Texture *texture, SDL_Renderer *renderer, t_engine *e)
{
	SDL_LockSurface(e->surface);
	DrawScreen(e);
	SDL_UnlockSurface(e->surface);
	if (texture == NULL)
		texture = SDL_CreateTextureFromSurface(renderer, e->surface);
	else
	{
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(renderer, e->surface);
	}
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	return (1);
}

void	player_falling(int *falling, int *moving, int *ground, float *eyeheight)
{
	float nextz;

	player.velocity.z -= 0.05f; /* Add gravity */
	nextz = player.where.z + player.velocity.z;
	if (player.velocity.z < 0 && nextz < sectors[player.sector].floor + *eyeheight) // When going down
	{
		/* Fix to ground */
		player.where.z    = sectors[player.sector].floor + *eyeheight;
		player.velocity.z = 0;
		*falling = 0;
		*ground  = 1;
	}
	else if (player.velocity.z > 0 && nextz > sectors[player.sector].ceil) // When going up
	{
		/* Prevent jumping above ceiling */
		player.velocity.z = 0;
		*falling = 1;
	}
	if (*falling)
	{
		player.where.z += player.velocity.z;
		*moving = 1;
	}
}


int		sdl_loop(SDL_Texture *texture, SDL_Renderer *renderer, t_engine *e)
{
	
	int				wsad[4] = {0,0,0,0};
	int				ground;
	int				falling;
	int				moving;
	int				ducking;
	float           yaw;
	float           eyeheight;

	yaw = 0;
	eyeheight = 0;
	ground = 0;
	falling = 1;
	moving = 0;
	ducking = 0;

	while (1)
	{
		sdl_render(texture, renderer, e);

		/* Vertical collision detection */
		eyeheight = ducking ? DuckHeight : EyeHeight;
		ground = !falling;
		if (falling)
			player_falling(&falling, &moving, &ground, &eyeheight);

		/* Horizontal collision detection */
		if (moving)
			player_moving(&moving, &falling, eyeheight, 1);

		SDL_Event ev;
		while(SDL_PollEvent(&ev))
			switch(ev.type)
			{
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					switch(ev.key.keysym.sym)
					{
						case 'w': wsad[0] = ev.type==SDL_KEYDOWN; break;
						case 's': wsad[1] = ev.type==SDL_KEYDOWN; break;
						case 'a': wsad[2] = ev.type==SDL_KEYDOWN; break;
						case 'd': wsad[3] = ev.type==SDL_KEYDOWN; break;
						case 'q': return (0);
						case ' ': /* jump */
							if (ground) { player.velocity.z += 0.5; falling = 1; }
							break;
						case SDLK_LCTRL: /* duck */
						case SDLK_RCTRL: ducking = ev.type==SDL_KEYDOWN; falling=1; break;
						default: break;
					}
					break;
				case SDL_QUIT:
					return (0); 
					break;
			}

		/* mouse aiming */
		int x,y;
		SDL_GetRelativeMouseState(&x,&y);
		player.angle += x * 0.03f;
		yaw          = clamp(yaw + y * 0.05f, -5, 5);
		player.yaw   = yaw - player.velocity.z * 0.5f;
		player_moving(&moving, &falling, eyeheight, 0);

		float move_vec[2] = {0.f, 0.f};
		if(wsad[0]) { move_vec[0] += player.anglecos*0.2f; move_vec[1] += player.anglesin*0.2f; }
		if(wsad[1]) { move_vec[0] -= player.anglecos*0.2f; move_vec[1] -= player.anglesin*0.2f; }
		if(wsad[2]) { move_vec[0] += player.anglesin*0.2f; move_vec[1] -= player.anglecos*0.2f; }
		if(wsad[3]) { move_vec[0] -= player.anglesin*0.2f; move_vec[1] += player.anglecos*0.2f; }
		int pushing = wsad[0] || wsad[1] || wsad[2] || wsad[3];
		float acceleration = pushing ? 0.4 : 0.2;

		player.velocity.x = player.velocity.x * (1-acceleration) + move_vec[0] * acceleration;
		player.velocity.y = player.velocity.y * (1-acceleration) + move_vec[1] * acceleration;

		if(pushing) moving = 1;

		SDL_Delay(10);
	}
	return (0);
}

int		main()
{
	SDL_Window      *window;
	SDL_Texture     *texture;
	SDL_Renderer    *renderer;
	t_engine		e;

	window = SDL_CreateWindow("Doom nukem",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		W, H, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	texture = NULL;
	e.NumSectors = 0;
	e.sectors = NULL;
	e.surface = SDL_CreateRGBSurface(0, W, H, 32, 0xff000000, 0xff0000, 0xff00, 0xff);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	LoadData();
	sdl_loop(texture, renderer, &e);
	
	
	UnloadData(texture, renderer, window);
	SDL_Quit();
	return 0;
}
