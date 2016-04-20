//VERTEX SHADER

#version 330

attribute vec3 position;
attribute vec2 tex_coord;
attribute vec3 normal;

varying vec2 tex_coord0;
varying vec3 normal0;

// a variable that can be set by the CPU
// this is to get our transform matrix
uniform mat4 transform;

void main(){

	// 2nd parameter is a scalar on the position
	// if it was 2, then it will transform the position twice
	// or double the translation.
	gl_Position = transform * vec4(position, 1.0);
	
	// make the variable be equal to the tex_coord of the vertex
	tex_coord0 = tex_coord;
	
	normal0 = (transform * vec4(normal, 0.0)).xyz;
}
