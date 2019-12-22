# version 330 core
out vec4 FragColor;

in vec3 fColor;
uniform float scale;

void main()
{
	FragColor = vec4(fColor * scale, 1.0f);
}

