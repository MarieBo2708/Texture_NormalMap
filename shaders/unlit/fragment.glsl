#version 330 core

out vec4 FragColor;

in vec3 worldSpace_fragmentPosition;
in vec2 o_uv0;
in vec3 tangentSpace_lightPosition;
in vec3 tangentSpace_viewPosition;
in vec3 tangentSpace_fragmentPosition;

uniform sampler2D colorTexture;
uniform sampler2D normalTexture;
uniform vec3 light_position;
uniform vec3 view_position;

void main() {
    vec3 normale = texture(normalTexture, o_uv0).rgb;
    normale = normalize(normale*2.0 - 1.0);

    vec3 color = texture(colorTexture, o_uv0).rgb;

    vec3 ambient = 1.0 * color;

    vec3 light_direction = normalize(tangentSpace_lightPosition - tangentSpace_fragmentPosition);
    float diff = max(dot(light_direction, normale), 0.0);
    vec3 diffuse = diff*color;

    vec3 view_direction = normalize(tangentSpace_viewPosition - tangentSpace_fragmentPosition);
    vec3 reflexion = reflect(-light_direction, normale);
    vec3 halway = normalize(light_direction + view_direction);
    float spec = pow(max(dot(normale, halway), 0.0), 32.0);
    vec3 specular = vec3(0.2)*spec;

    FragColor = vec4(ambient + diffuse + specular, 1.0);

}
