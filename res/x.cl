__kernel void square(
	global uint * width,
	global float * dt,
	global float3 * mouse,
	global float3 * dPobj,
	global float3 * dVel,
	global float3 * dCobj
) {
	int Xindex = get_global_id(0);
	int Yindex = get_global_id(1);
	int index = Xindex + Yindex * (int)(*width);

	if (Xindex == 1)
		return ;

	float pos = dPobj[index].x ;
	float vel = dVel[index].x ;

	float att = (*mouse).x ;
	float dst = sqrt(
		pow(dPobj[index].x - (*mouse).x, 2) +
		pow(dPobj[index].y - (*mouse).y, 2)
		// pow(dPobj[index].z - (*mouse).z, 2)
	);

	dVel[index].x += (att - pos) * (dst / 2) ;
	dPobj[index].x += vel * (*dt) ;
	dCobj[index].x = dst * dst;
}
