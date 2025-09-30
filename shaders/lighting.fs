#version 330

// Input attributes from vertex shader
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;
uniform float  ambientStrength;
uniform int lightingOption;
// Input uniform values
uniform sampler2D texture0;
uniform vec3 lightPos;
uniform vec3 viewPos;

// Output color
out vec4 finalColor;

void main() {
    // Normalize the normal vector
    vec3 norm = normalize(fragNormal);
    
    // Calculate light direction from light source to fragment
    vec3 lightDir = normalize(lightPos - fragPosition);
    
    // Calculate view direction
    vec3 viewDir = normalize(viewPos - fragPosition);
    
    // HARDCODED LIGHTING OPTION - CHANGE THIS VALUE TO SWITCH EFFECTS
    //const int lightingOption = 2; // 0: Basic, 1: Phong, 2: Blinn-Phong, 3: Toon, 4: Rim Lighting
    
    // Common lighting parameters (hardcoded)
    //vec3 lightColor = vec3(1.0, 0.8, 0.6);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    //float ambientStrength = 0.7;     
    float specularStrength = 0.25;
    float shininess = 32.0;
    
    // Calculate distance from light for attenuation
    float distance = length(lightPos - fragPosition);
    float attenuation = 1.0 / (1.0 + 0.1 * distance + 0.01 * (distance * distance));
    
    // Ambient lighting (very minimal)
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse lighting
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Initialize specular component
    vec3 specular = vec3(0.1);
    
    // Apply selected lighting model
    if (lightingOption == 0) {
        // Basic lighting - just diffuse
    } 
    else if (lightingOption == 1) {
        // Phong specular model
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        specular = specularStrength * spec * lightColor;
    }
    else if (lightingOption == 2) {
        // Blinn-Phong specular model
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
        specular = specularStrength * spec * lightColor;
    }
    else if (lightingOption == 3) {
        // Toon/Cel shading
        // Quantize the diffuse intensity
        if (diff > 0.8) diffuse = vec3(1.0, 0.8, 0.6);
        else if (diff > 0.5) diffuse = vec3(0.7, 0.7, 0.7);
        else if (diff > 0.2) diffuse = vec3(0.35, 0.35, 0.35);
        else diffuse = vec3(0.0, 0.0, 0.0); // Completely dark for unlit areas
        
        // Simple specular for toon shading
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        if (spec > 0.5) specular = vec3(1.0) * specularStrength;
    }
    else if (lightingOption == 4) {
        // Rim lighting effect
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        specular = specularStrength * spec * lightColor;
        
        // Add rim lighting
        float rim = 1.0 - max(dot(viewDir, norm), 0.0);
        rim = smoothstep(0.4, 1.0, rim);
        vec3 rimLight = vec3(0.2, 0.2, 0.5) * rim * 2.0;
        
        // Add rim light to the diffuse
        diffuse += rimLight;
    }
    
    // Combine lighting components with attenuation
    vec3 lighting = ambient + (diffuse + specular) * attenuation;
    
    // Apply to texture
    vec4 texColor = texture(texture0, fragTexCoord);
    finalColor = vec4(lighting, 1.0) * texColor;
    
    // Ensure unlit areas are completely dark
    if (length(lighting) < 0.01) {
        finalColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}