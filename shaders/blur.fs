#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;


out vec4 finalColor;

// === CRT Parameters ===
const float CURVE_AMOUNT       = 0.02;       // barrel distortion
const float SCANLINE_INTENSITY = 0.5;       // strength of scanlines
const float CHROMA_OFFSET      = 1.0;  // RGB shift
const float VIGNETTE_STRENGTH  = 0.1;       // vignette darkening
const float MASK_STRENGTH      = 0.15;      // phosphor mask visibility

// === FOG Parameters ===
const vec3  FOG_COLOR          = vec3(0.01, 0.01, 0.01); // Fog color (black for a dark effect)
const float FOG_START          = 0.00;                // Vertical position where fog begins (0.0 = bottom)
const float FOG_END            = 2.00;                // Vertical position where fog is at full strength (1.0 = top)

// Curves the UVs to simulate CRT glass
vec2 curveCoords(vec2 uv)
{
    uv = uv * 2.0 - 1.0; // map to -1..1
    uv *= 1.0 + CURVE_AMOUNT * (uv.x*uv.x + uv.y*uv.y);
    uv = uv * 0.5 + 0.5; // back to 0..1
    return uv;
}

// Generates an RGB triad phosphor mask
vec3 phosphorMask(vec2 uv, vec2 resolution)
{
    // Scale so mask repeats every pixel
    vec2 pixel = uv * resolution;
    float phase = mod(pixel.x, 3.0);
    
    vec3 mask = vec3(0.0);
    if (phase < 1.0) mask.r = 1.0;
    else if (phase < 2.0) mask.g = 1.0;
    else mask.b = 1.0;

    // Darken slightly to simulate phosphor gaps
    return mix(vec3(1.0), mask, MASK_STRENGTH);
}

void main()
{
    vec2 resolution = vec2(textureSize(texture0, 0));
    vec2 uv = curveCoords(fragTexCoord);

    // If outside the curved screen area, draw black
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0) {
        finalColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    // Chromatic aberration: sample R/G/B channels separately
    float r = texture(texture0, uv + vec2(CHROMA_OFFSET, 0.0)).r;
    float g = texture(texture0, uv).g;
    float b = texture(texture0, uv - vec2(CHROMA_OFFSET, 0.0)).b;
    vec3 col = vec3(r, g, b);

    // Horizontal scanlines
    float scan = sin(uv.y * resolution.y * 3.14159) * SCANLINE_INTENSITY;
    col *= 1.0 - scan;

    // Apply phosphor dot mask
    col *= phosphorMask(uv, resolution);

    // Vignette darkens edges
    vec2 v = uv - 0.5;
    float vign = smoothstep(0.8, 0.0, dot(v, v) * 2.0);
    col *= mix(1.0 - VIGNETTE_STRENGTH, 1.0, vign);

    // --- FOG EFFECT ---
    // Calculate fog intensity based on original vertical texture coordinate.
    // This creates a fog that appears to get denser with "distance" (further up the screen).
    // smoothstep() creates a nice transition between the start and end points.
    float fogFactor = smoothstep(FOG_START, FOG_END, fragTexCoord.y);
    
    // Mix the pixel color with the fog color based on the fog factor.
    col = mix(col, FOG_COLOR, fogFactor);
    // ------------------

    finalColor = vec4(col, 1.0) * colDiffuse * fragColor;
}