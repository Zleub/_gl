attribute vec3 vPos;
attribute vec3 vCol;
attribute vec3 tPos;

attribute vec2 size;
attribute vec2 position;

varying vec3 color;
varying vec3 texture;

void main()
{
	// color = vec3(vPos.x, vPos.y, (vPos.x * vPos.y));
	color = vec3(1., 1., 1.);
	texture = tPos;

	gl_Position = vec4(vPos, 1.);
}
