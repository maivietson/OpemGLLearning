#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform float mixValue;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	color = mix(texture2D(ourTexture1, TexCoord), texture2D(ourTexture2, TexCoord), mixValue) * vec4(lightColor * objectColor, 1.0f);
}