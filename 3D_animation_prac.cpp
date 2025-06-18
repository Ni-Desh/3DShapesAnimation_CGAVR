#include <windows.h>  // For MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h

// Global variables
char title[] = "3D Shapes with Animation";
GLfloat anglePyramid = 0.0f;  // Rotational angle for pyramid
GLfloat angleCube = 0.0f;     // Rotational angle for cube
int refreshMills = 15;        // Refresh interval in milliseconds

// Initialize OpenGL Graphics
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set background color to black and opaque
    glClearDepth(1.0f);                    // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);               // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);                // Set the type of depth test
    glShadeModel(GL_SMOOTH);               // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    // Render a color-cube
    glLoadIdentity();                 // Reset the model-view matrix
    glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen
    glRotatef(angleCube, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis

    glBegin(GL_QUADS);  // Begin drawing the cube
    // Front face (z = 1.0f)
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);

    // Back face (z = -1.0f)
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Top face (y = 1.0f)
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    // Bottom face (y = -1.0f)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    // Right face (x = 1.0f)
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);

    // Left face (x = -1.0f)
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();

    // Render a pyramid
    glLoadIdentity();                  // Reset the model-view matrix
    glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen
    glRotatef(anglePyramid, 1.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis

    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid
    // Front face
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);

    // Right face
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Back face
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left face
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glEnd();

    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

    // Update the rotational angle after each refresh
    anglePyramid += 0.2f;
    angleCube -= 0.15f;
}

// Timer callback function
void timer(int value) {
    glutPostRedisplay();               // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0);  // Next timer call milliseconds later
}

// Reshape callback function
void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);            // Set the viewport to cover the new window
    glMatrixMode(GL_PROJECTION);                // To operate on the Projection matrix
    glLoadIdentity();                           // Reset
    gluPerspective(45.0f, aspect, 0.1f, 100.0f); // Enable perspective projection
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);                      // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE);           // Enable double buffered mode
    glutInitWindowSize(640, 480);               // Set the window's initial width & height
    glutInitWindowPosition(50, 50);             // Position the window's initial top-left corner
    glutCreateWindow(title);                    // Create window with the given title
    glutDisplayFunc(display);                   // Register display callback handler
    glutReshapeFunc(reshape);                   // Register reshape callback handler
    initGL();                                   // OpenGL initialization
    glutTimerFunc(0, timer, 0);                 // First timer call immediately
    glutMainLoop();                             // Enter the infinite event-processing loop
    return 0;
}


