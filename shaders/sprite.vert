#version 460 core
layout(location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform vec2 texCoordDivisor;
uniform int activeCell;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    vec2 texCoordPostDivision = vertex.zw / texCoordDivisor;

    TexCoords.x = texCoordPostDivision.x + (texCoordPostDivision.x * activeCell);
    TexCoords.y = texCoordPostDivision.y;

    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}
