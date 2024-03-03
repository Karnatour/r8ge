@r8ge vertex
#version 460 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vec4 pos = projection * view * vec4(aPos, 1.0f);
    gl_Position = vec4(pos.x,pos.y,pos.w,pos.w);
    TexCoords = vec3(aPos.x, aPos.y, -aPos.z);
}

@r8ge fragment
#version 460 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, TexCoords);
}


