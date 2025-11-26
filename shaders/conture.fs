#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

// ===== Tunables (no new uniforms) =====
const float EDGE_THRESHOLD = 0.55; // lower = more edges
const float LINE_INTENSITY = 1.0;  // 1.0 = pure black lines
const bool  TRANSPARENT_BG = false; // true = transparent where no edge
const int   THICKEN_STEPS = 0;     // 0=thin, >0=slightly thicker outline

// Convert color to luminance (perceived brightness)
float luminance(vec3 c) {
    return dot(c, vec3(0.299, 0.587, 0.114));
}

// Sobel edge magnitude in [0, ~1.4]
float sobelEdge(vec2 uv, vec2 texel)
{
    // Sample a 3x3 neighborhood
    float tl = luminance(texture(texture0, uv + texel * vec2(-1.0, -1.0)).rgb);
    float tc = luminance(texture(texture0, uv + texel * vec2( 0.0, -1.0)).rgb);
    float tr = luminance(texture(texture0, uv + texel * vec2( 1.0, -1.0)).rgb);

    float ml = luminance(texture(texture0, uv + texel * vec2(-1.0,  0.0)).rgb);
    float mc = luminance(texture(texture0, uv).rgb);
    float mr = luminance(texture(texture0, uv + texel * vec2( 1.0,  0.0)).rgb);

    float bl = luminance(texture(texture0, uv + texel * vec2(-1.0,  1.0)).rgb);
    float bc = luminance(texture(texture0, uv + texel * vec2( 0.0,  1.0)).rgb);
    float br = luminance(texture(texture0, uv + texel * vec2( 1.0,  1.0)).rgb);

    // Sobel kernels
    float gx = (tr + 2.0*mr + br) - (tl + 2.0*ml + bl);
    float gy = (bl + 2.0*bc + br) - (tl + 2.0*tc + tr);

    // Gradient magnitude
    return sqrt(gx*gx + gy*gy);
}

void main()
{
    vec2 texSize  = vec2(textureSize(texture0, 0));
    vec2 texel    = 1.0 / texSize;

    // Base edge strength
    float edge = sobelEdge(fragTexCoord, texel);

    // Optional local max search to thicken lines a bit (cheap dilation)
    if (THICKEN_STEPS > 0) {
        float eMax = edge;
        for (int dy = -THICKEN_STEPS; dy <= THICKEN_STEPS; ++dy) {
            for (int dx = -THICKEN_STEPS; dx <= THICKEN_STEPS; ++dx) {
                if (dx == 0 && dy == 0) continue;
                eMax = max(eMax, sobelEdge(fragTexCoord + texel * vec2(dx, dy), texel));
            }
        }
        edge = eMax;
    }

    // Normalize and threshold
    // Sobel magnitude can exceed 1.0; scale a bit for a tight threshold feel
    float e = smoothstep(EDGE_THRESHOLD, EDGE_THRESHOLD + 0.1, edge);

    // Output only contours: black lines where edge, white or transparent elsewhere
    //vec3 lineColor = vec3(1.0); // black outlines
    vec3 lineColor = vec3(0.1, 1.0, 0.1);
    float alpha = 1.0;

    if (TRANSPARENT_BG) {
        // Black lines on transparent background
        float line = e * LINE_INTENSITY;
        finalColor = vec4(mix(vec3(0.0), lineColor, line), line); // alpha = line
    } else {
        // Black lines on white background
        vec3 bg = vec3(0.1, 0.1, 0.1);
        float line = e * LINE_INTENSITY;
        vec3 col = mix(bg, lineColor, line);
        finalColor = vec4(col, 1.0);
    }
}
