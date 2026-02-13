#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

// === PS1 Performance Simulation ===
const float JITTER_RES     = 240.0; 
const float COLOR_STEPS    = 32.0;  

// === PS1 Darkness Fog ===
const vec3  FOG_COLOR      = vec3(0.01, 0.01, 0.02); 
const float FOG_START      = 0.2;                   
const float FOG_END        = 0.8;                   

void main()
{
    // 1. RESOLUTION SNAPPING
    vec2 res = vec2(textureSize(texture0, 0));
    float aspect = res.x / res.y;
    vec2 virtualRes = vec2(JITTER_RES * aspect, JITTER_RES);
    vec2 uv = floor(fragTexCoord * virtualRes) / virtualRes;

    // 2. TEXTURE SAMPLING & COLOR CRUNCH
    vec4 texel = texture(texture0, uv);
    vec3 col = floor(texel.rgb * COLOR_STEPS) / COLOR_STEPS;

    // 3. CALCULATE FOG FACTOR
    float fogFactor = clamp((uv.y - FOG_START) / (FOG_END - FOG_START), 0.0, 1.0);
    
    // 4. DITHER MASK (The "Checkerboard")
    // Use gl_FragCoord to get the actual screen pixel position
    // We create a 2x2 repeating pattern
    int x = int(mod(gl_FragCoord.x, 2.0));
    int y = int(mod(gl_FragCoord.y, 2.0));
    
    // This creates a threshold: 0.25, 0.5, 0.75, etc.
    float ditherThreshold = 0.0;
    if (x == 0 && y == 0) ditherThreshold = 0.25;
    else if (x == 1 && y == 1) ditherThreshold = 0.5;
    else if (x == 1 && y == 0) ditherThreshold = 0.75;
    else ditherThreshold = 1.0;

    // 5. APPLY DITHERED FOG
    // If the fog is stronger than the dither threshold, it snaps to FOG_COLOR
    if (fogFactor > ditherThreshold) {
        col = FOG_COLOR;
    } else {
        // Subtle mix for the areas in between to keep it from being too harsh
        col = mix(col, FOG_COLOR, fogFactor * 0.5);
    }

    finalColor = vec4(col, texel.a) * colDiffuse * fragColor;
}