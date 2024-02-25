@r8ge vertex
#version 460 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0

out vec3 ourColor; // output a color to the fragment shader

uniform mat4 model;       // uniform variable for the model matrix
uniform mat4 view;        // uniform variable for the view matrix
uniform mat4 projection;  // uniform variable for the projection matrix
uniform vec3 randomColor;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourColor = randomColor;
}

@r8ge fragment
#version 460 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(randomColor, 1.0); // use the random color provided from the CPU
}