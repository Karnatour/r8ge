@r8ge vertex
#version 460 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0

out vec3 ourColor; // output a color to the fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);
}

@r8ge fragment
#version 460 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
    FragColor = vec4(0.0f,0.0f,0.0f, 1.0);
}
