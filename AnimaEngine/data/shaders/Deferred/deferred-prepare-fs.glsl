#version 410 core

in vec2 frag_textureCoord;
in vec3 frag_normal;
in vec3 frag_worldPosition;
in mat3 frag_TBNMatrix;

uniform sampler2D MAT_DiffuseTexture;
uniform vec4 MAT_DiffuseColor;

uniform sampler2D MAT_BumpTexture;
uniform bool MAT_HasBump;

uniform sampler2D MAT_OpacityTexture;
uniform bool MAT_HasOpacity;

uniform sampler2D MAT_SpecularTexture;
uniform bool MAT_HasSpecular;
uniform vec3 MAT_SpecularColor;
uniform float MAT_Shininess;

uniform sampler2D MAT_DisplacementTexture;
uniform float MAT_DisplacementScale;
uniform float MAT_DisplacementBias;

uniform vec3 CAM_Position;

out vec4 FragColor[4];

vec2 CalcParallaxTexCoords(vec3 worldPos, vec3 camPos, vec2 originalTextCoords, mat3 tbnMatrix)
{
	vec3 directionToEye = normalize(camPos - worldPos);	
	return originalTextCoords + (directionToEye * tbnMatrix).xy * (texture(MAT_DisplacementTexture, originalTextCoords).r * MAT_DisplacementScale + MAT_DisplacementBias);
}

vec3 calcNormal(vec2 textureCoords)
{
	if(!MAT_HasBump)
		return frag_normal;
	
	vec3 bumpNormal = texture(MAT_BumpTexture, textureCoords).xyz;
	bumpNormal = 2.0 * bumpNormal - vec3(1.0, 1.0, 1.0);	
	vec3 newNormal = frag_TBNMatrix * bumpNormal;
	newNormal = normalize(newNormal);
	
	return newNormal;
}

void main()
{
	vec2 textureCoord = frag_textureCoord;

	if(MAT_HasOpacity)
	{
		if(texture(MAT_OpacityTexture, frag_textureCoord).r <= 0.1)
			discard;
	}

	vec4 diffuseColor = MAT_DiffuseColor;
	vec3 specularColor = MAT_SpecularColor;

    vec4 textureColor = texture(MAT_DiffuseTexture, frag_textureCoord);
	if(textureColor != vec4(0.0, 0.0, 0.0, 1.0))
		diffuseColor = textureColor;

	if(MAT_HasSpecular)
	{
		specularColor = texture(MAT_SpecularTexture, frag_textureCoord).rgb;
	}
		
	vec3 normal = calcNormal(frag_textureCoord);

	float len = length(normal);

	FragColor[1] = diffuseColor * len;
	FragColor[2] = vec4(normal * 0.5 + 0.5, 1.0);
	FragColor[3] = vec4(specularColor, 1.0 / MAT_Shininess);
}
