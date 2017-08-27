#version 330 core
out vec4 color;

void main()
{
	vec3 objectColor = vec3(0.6, 0.6, 1.0);
	color = vec4(objectColor,1);
}
