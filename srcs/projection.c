#include "wolf.h"

static float  yaw(float p_yaw, float y, float z)
{
	return (y + z * p_yaw);
}

t_projec    curr_projection(float p_yaw, float yceil, float yfloor, t_edge t, t_edge scale)
{
	t_projec	projection;
	
	projection = (t_projec)
	{
		H/2 - (int)(yaw(p_yaw, yceil, t.y1) * scale.y1),
		H/2 - (int)(yaw(p_yaw, yfloor, t.y1) * scale.y1),
		H/2 - (int)(yaw(p_yaw, yceil, t.y2) * scale.y2),
		H/2 - (int)(yaw(p_yaw, yfloor, t.y2) * scale.y2)
	};
	return (projection);	
}

t_projec	next_projection(float p_yaw, float nyceil, float nyfloor, t_edge t, t_edge scale)
{
	t_projec	projection;

	projection = (t_projec)
	{
		H/2 - (int)(yaw(p_yaw, nyceil, t.y1) * scale.y1),
		H/2 - (int)(yaw(p_yaw, nyfloor, t.y1) * scale.y1),
		H/2 - (int)(yaw(p_yaw, nyceil, t.y2) * scale.y2),
		H/2 - (int)(yaw(p_yaw, nyfloor, t.y2) * scale.y2)
	};
	return (projection);
}