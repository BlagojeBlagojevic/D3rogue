#version 330
in vec2 fragTexCoord;
in vec4 fragColor;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
out vec4 finalColor;

float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    float time = mod(gl_FragCoord.x + gl_FragCoord.y + float(gl_FragCoord.y), 200.0);
    vec3 col = texture(texture0, fragTexCoord).rgb * colDiffuse.rgb * fragColor.rgb;

    // Grain
    float grain = rand(fragTexCoord * time) * 0.15 - 0.075;
    col += grain;

    // Flicker
    col *= 0.9 + rand(vec2(time, 0.0)) * 0.1;

    finalColor = vec4(clamp(col, 0.0, 1.0), 1.0);
}
