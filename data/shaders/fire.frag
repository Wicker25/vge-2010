varying vec4 color;

varying float timeAlive;

void main ( void )
{
    gl_FragColor = color;
    
	if ( timeAlive < 0.0 || timeAlive > 0.4 )
	{
		discard;
	}
	else if ( timeAlive < 0.1 )
	{
		gl_FragColor.y += 0.1;
	}
	else if ( timeAlive < 0.2 )
	{
		gl_FragColor.y += 0.2;
	}
	else if ( timeAlive < 0.3 )
	{
		gl_FragColor.y += 0.3;
	}
	else if ( timeAlive < 0.4 )
	{
		gl_FragColor.y += 0.4;
	}
	else
	{
		gl_FragColor.y += 0.5;
	}
	
	clamp( gl_FragColor, 0.0, 1.0 );
}
