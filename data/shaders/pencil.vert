// Disegno semplice monocromatico
#version 1

void main()
{
	gl_FrontColor = gl_Color;
	gl_Position	= ftransform();
}
