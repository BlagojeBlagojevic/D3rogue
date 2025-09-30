#version 330
// Input vertex attributes (from model)
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

// Output vertex attributes (to fragment shader)
out vec3 fragPosition;
out vec2 fragTexCoord;
out vec3 fragNormal;

// Input uniform values
uniform mat4 mvp;
uniform mat4 matModel;

void main() {
    // Transform vertex position to clip space
    gl_Position = mvp * vec4(vertexPosition, 1.0);
    
    // Pass vertex position and normal to the fragment shader
    fragPosition = (matModel * vec4(vertexPosition, 1.0)).xyz;
    fragNormal = normalize(mat3(matModel) * vertexNormal);
    
    // Pass texture coordinates to fragment shader
    fragTexCoord = vertexTexCoord;
}