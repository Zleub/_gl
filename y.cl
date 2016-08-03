__kernel void square(
	global uint * width,
	global float * dt,
	global float3 * mouse,
	global float3 * dPobj,
	global float3 * dVel
) {
	int Xindex = get_global_id(0);
	int Yindex = get_global_id(1);
	int index = Xindex + Yindex * (int)(*width);

	float pos = dPobj[index].y ;
	float vel = dVel[index].y ;

	float att = (*mouse).y ;
	float dst = cbrt(
		pow(dPobj[index].x - (*mouse).x, 2) +
		pow(dPobj[index].y - (*mouse).y, 2) +
		pow(dPobj[index].z - (*mouse).z, 2)
	);

	dVel[index].y += (att - pos) * (dst / 2);
	dPobj[index].y += vel * (*dt) ;
}
