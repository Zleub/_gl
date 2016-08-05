attribute vec3 vPos;
attribute vec3 vCol;

varying vec3 color;
uniform float w;

void main()
{
    gl_Position = vec4(vPos, w);
    color = vCol;
}
