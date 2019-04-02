#include "doom.h"

void			load_map(t_engine *e, t_env *env)
{
	FILE		*fp;
	char	Buf[256];
	char	word[256];
	char	*ptr;
	t_vtx	*vert;
	t_vtx	v;
	int		n;
	int		m;
	int		NumVertices;

	n = 0;
	m = 0;
	vert = NULL;
	NumVertices = 0;
	(void)env;
	if (!(fp = fopen("rsrc/maps/segfault.txt", "rt")))
	{
		perror("map-clear.txt");
		exit(1);
	}
	while (fgets(Buf, sizeof Buf, fp))
	{
		switch(sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
		{
			case 'v': // vertex
				sscanf(ptr += n, "%f%n", &v.x, &n);
				while (sscanf(ptr += n, "%f%n", &v.y, &n) == 1)
				{
					vert = realloc(vert, ++NumVertices * sizeof(*vert));
					vert[NumVertices-1] = v;
				}
				break;
			case 's': // sector
				e->sectors = realloc(e->sectors, ++e->nsectors * sizeof(*e->sectors));
				t_sector *sect = &e->sectors[e->nsectors-1];
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
				sect->head_object = NULL;
				sect->head_enemy = NULL;
				for (n=0; n<m; ++n)
				{
					sect->neighbors[n] = num[m + n];
				}
				for(n=0; n<m; ++n)
				{
					sect->vertex[n+1]  = vert[num[n]]; // TODO: Range checking
				}
				sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
				free(num);
				break;
			case 'o':; //object
				t_vtx	vertex = (t_vtx){0, 0};
				int		s = 0;
				int		ref = 0;
				int		is_wpn = 0;
				sscanf(ptr += n, "%f %f %d %d %d%n", &vertex.x, &vertex.y, &s, &ref, &is_wpn, &n);
				fill_objects_sector(&e->sectors[s], vertex, ref, is_wpn);
				break;
			case 'e':; // enemy
				sscanf(ptr += n, "%f %f %d %d%n", &vertex.x, &vertex.y, &s, &ref, &n);
				fill_enemies_sector(env, &e->sectors[s], vertex, ref);
				break;
			case 'p':; // player
				float angle;
				sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle,&n);
				e->player = (t_player) { {0,0,0}, {v.x, v.y, 0}, {0,0,0}, {0,0,0},{0,1,0,0,0,0}, angle,0,0,0,12, n, env->player.bullet }; // TODO: Range checking
				e->player.where.z = e->sectors[e->player.sector].floor + EYEHEIGHT;
				break;
		}
	}
	if ((e->queue.renderedsectors = (int *)malloc(e->nsectors * sizeof(int))) == NULL)
		return;
	fclose(fp);
	free(vert);
	verify_map(e);
	init_minimap(env);
}
