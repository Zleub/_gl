attribute vec3 vPos;
attribute vec3 vCol;
attribute vec3 tPos;

attribute vec2 size;
attribute vec2 position;

varying vec3 color;
varying vec3 texture;

void main()
{
	gl_Position = vec4(vPos, 1.);
	color = vec3(vPos.x, vPos.y, (vPos.x * vPos.y));
	texture = tPos;
}
