// Disegno ibrido
void main()
{
	gl_Position	= ftransform();

	gl_FrontColor = gl_Color;
	gl_BackColor = gl_Color;

	gl_TexCoord[0] = gl_MultiTexCoord0;
}
