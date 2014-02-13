/* square using vertex buffer objects */

#include "include/Angel.h"

const int NumPoints = 4;

//----------------------------------------------------------------------------

void init()
{
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Specify the vertices for a square
    float ext = 0.5;
    vec3 points[] = {
        vec3(-ext, -ext, 0.0), //v1
        vec3( ext, -ext, 0.0), //v2
        vec3(-ext,  ext, 0.0), //v3
        vec3( ext,  ext, 0.0)  //v4
    };

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Load shaders and use the resulting shader program
    GLuint program = InitShader("vshader.glsl", "fshader.glsl");

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0,
        BUFFER_OFFSET(0));

    glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}

//----------------------------------------------------------------------------

void display()
{
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // Polygon mode and face culling
    glPolygonMode(GL_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);

    // Draw the points as triangle strip
    glDrawArrays(GL_TRIANGLE_STRIP, 0, NumPoints);

    // Force OpenGL to render
    glFlush();
}

//----------------------------------------------------------------------------

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 033: //ESC
        exit(EXIT_SUCCESS);
        break;
    }
}

//----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    // Initialize glut library
    glutInit(&argc, argv);

    // Create the window
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Hello, Square!");

    // Initialize glew library
    // glewInit();

    // Your own initialization
    init();

    // Set callback functions
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    // Start the main loop
    glutMainLoop();

    return 0;
}
