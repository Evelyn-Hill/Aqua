#version 460 core
layout(location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform int segmentIndex;
uniform vec2 segmentCount;

uniform mat4 model;
uniform mat4 projection;

vec2 currentSegment = vec2(0, 0);
vec2 segmentSize;

void main()
{
    // Calculate the normalized size of one segment.
    segmentSize = vec2(1.0 / segmentCount.x, 1.0 / segmentCount.y);

    // Calculate the x, y position of the sprite sheet from a scalar index.
    currentSegment.x = segmentIndex % int(segmentCount.x);
    currentSegment.y = floor(segmentIndex / int(segmentCount.x));

    TexCoords = (vertex.zw / segmentCount) + (segmentSize * currentSegment);
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}
