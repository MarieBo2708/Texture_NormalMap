#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent; 
layout(location = 3) in vec2 uv0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 worldSpace_fragmentPosition;
out vec2 o_uv0;
out vec3 tangentSpace_lightPosition;
out vec3 tangentSpace_viewPosition;
out vec3 tangentSpace_fragmentPosition; 

uniform vec3 light_position;
uniform vec3 view_position;

void main() {
  worldSpace_fragmentPosition = vec3(model*vec4(position, 1.0));
  o_uv0 = uv0;

  mat3 normalMatrix = transpose(inverse(mat3(model)));
  vec3 T = normalize(normalMatrix*tangent);
  vec3 N = normalize(normalMatrix*normal);
  T = normalize(T - dot(T,N) * N);
  vec3 B = cross(N, T);

  mat3 TBN = transpose(mat3(T,B,N));
  tangentSpace_lightPosition = TBN * light_position;
  tangentSpace_viewPosition = TBN * view_position;
  tangentSpace_fragmentPosition = TBN * worldSpace_fragmentPosition;

  gl_Position = projection * view * model * vec4(position, 1.0);
  
}