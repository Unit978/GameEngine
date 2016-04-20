//FRAGMENT SHADER

#version 330

uniform sampler2D diffuse;

varying vec2 tex_coord0;
varying vec3 normal0;

void main(){

	gl_FragColor = texture2D(diffuse, tex_coord0);
}
