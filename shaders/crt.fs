#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

// === Parameters ===
const float SCANLINE_INTENSITY = 0.25; // strength of scanlines
const float CURVE_AMOUNT = 0.12;       // barrel distortion
const float CHROMA_OFFSET = 1.0 / 512.0; // RGB shift amount
const float VIGNETTE_STRENGTH = 0.25; // vignette darkness

vec2 curveCoords(vec2 uv)
{
    // Map from 0..1 to -1..1
    uv = uv * 2.0 - 1.0;
    // Barrel distortion
    uv *= 1.0 + CURVE_AMOUNT * (uv.x*uv.x + uv.y*uv.y);
    // Back to 0..1
    uv = uv * 0.5 + 0.5;
    return uv;
}

void main()
{
    // Screen curvature
    vec2 uv = curveCoords(fragTexCoord);

    // If outside the curved screen area, draw black
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0) {
        finalColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    // Chromatic aberration: sample R/G/B at slightly different positions
    float r = texture(texture0, uv + vec2(CHROMA_OFFSET, 0.0)).r;
    float g = texture(texture0, uv).g;
    float b = texture(texture0, uv - vec2(CHROMA_OFFSET, 0.0)).b;
    vec3 col = vec3(r, g, b);

    // Apply scanlines (horizontal)
    float scan = sin(uv.y * textureSize(texture0, 0).y * 3.14159) * SCANLINE_INTENSITY;
    col *= 1.0 - scan;

    // Vignette
    vec2 v = uv - 0.5;
    float vign = smoothstep(0.8, 0.0, dot(v, v) * 2.0);
    col *= mix(1.0 - VIGNETTE_STRENGTH, 1.0, vign);

    finalColor = vec4(col, 1.0) * colDiffuse * fragColor;
}
