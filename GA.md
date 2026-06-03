# DDA
```cpp
/*
===========================================
  LAB 1A — DDA Line Drawing Algorithm
===========================================
  Concepts:
  - DDA (Digital Differential Analyzer)
  - GL_POINTS to plot pixels
  - gluOrtho2D for 2D coordinate system
  - User input before window opens

  Controls: None (enter points in console)
===========================================
*/

#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <cmath>
#include <iostream>
using namespace std;

// Global variables to store user input
float x1_, y1_, x2_, y2_;

// ---- DDA Algorithm ----
void drawDDALine(float x1, float y1, float x2, float y2)
{
    float dx    = x2 - x1;
    float dy    = y2 - y1;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    float Xinc = dx / steps;
    float Yinc = dy / steps;

    float x = x1;
    float y = y1;

    cout << "\nIntermediate Points:\n";

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        cout << i << ": (" << round(x) << ", " << round(y) << ")" << endl;
        glVertex2i(round(x), round(y));
        x += Xinc;
        y += Yinc;
    }
    glEnd();
}

// ---- Display Callback ----
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);   // white line on black background
    drawDDALine(x1_, y1_, x2_, y2_);
    glFlush();
}

// ---- Initialization ----
void init()
{
    glClearColor(0, 0, 0, 0);          // black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);        // 2D coordinate space 0-600
    glPointSize(2);
}

// ---- Main ----
int main(int argc, char** argv)
{
    cout << "Enter starting point (x1 y1): ";
    cin  >> x1_ >> y1_;
    cout << "Enter ending point   (x2 y2): ";
    cin  >> x2_ >> y2_;

    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Lab 1A - DDA Line Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

# Triangle 
```cpp
/*
===========================================
  LAB 1B — Basic Triangle (GL_TRIANGLES)
===========================================
  Concepts:
  - glutInitDisplayMode with GLUT_DOUBLE
  - GL_TRIANGLES with per-vertex color
  - glColor3f before each vertex
  - glutSwapBuffers for double buffering

  Controls: None
===========================================
*/

#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

// ---- Display Callback ----
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw a color-gradient triangle
    glBegin(GL_TRIANGLES);
        glColor3f(0.5f, 0, 0);   // dark red   — bottom left
        glVertex2f(-0.8f, -0.8f);

        glColor3f(0, 1, 0);      // green      — bottom right
        glVertex2f( 0.8f, -0.8f);

        glColor3f(0, 0, 1);      // blue       — top center
        glVertex2f( 0,     0.9f);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

// ---- Main ----
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Lab 1B - Basic Triangle");
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
```

# Cube 
```cpp
/*
===========================================
  LAB 2 — 3D Colored Cube (GL_QUADS)
===========================================
  Concepts:
  - GL_QUADS to build a 3D cube face by face
  - glFrustum for perspective projection
  - resize() callback to handle window resize
  - Keyboard rotation on X / Y / Z axes
  - GL_CULL_FACE to skip back faces
  - GL_DEPTH_TEST for correct 3D overlap

  Controls:
    a / b  — rotate X axis +/-
    c / d  — rotate Y axis +/-
    e / f  — rotate Z axis +/-
    q / ESC — quit
===========================================
*/

#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

// Global rotation angles
float degreeX = 0;
float degreeY = 0;
float degreeZ = 0;

// ---- Projection / Resize ----
static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);   // perspective

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// ---- Cube Primitive ----
// One unit cube from (0,0,0) to (1,1,1)
// Each face has its own color
void cube()
{
    glBegin(GL_QUADS);

    // Front face — red
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    // Left face — yellow
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);

    // Back face — blue
    glColor3f(0, 0, 1);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);

    // Right face — green
    glColor3f(0, 1, 0);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);

    // Bottom face — magenta
    glColor3f(1, 0, 1);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);

    // Top face — cyan
    glColor3f(0, 1, 1);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    glEnd();
}

// ---- Display Callback ----
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glTranslated(0, 0, -7);             // push into view

        glRotated(degreeX, 0.5, 0,   0);   // tilt X
        glRotated(degreeY, 0,   0.5, 0);   // spin Y
        glRotated(degreeZ, 0,   0,   0.5); // roll Z

        cube();
    glPopMatrix();

    glutSwapBuffers();
}

// ---- Keyboard ----
static void key(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 27:
        case 'q': exit(0);      break;

        case 'a': degreeX += 2.5f; break;
        case 'b': degreeX -= 2.5f; break;
        case 'c': degreeY += 2.5f; break;
        case 'd': degreeY -= 2.5f; break;
        case 'e': degreeZ += 2.5f; break;
        case 'f': degreeZ -= 2.5f; break;
    }
    glutPostRedisplay();
}

// ---- Main ----
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Lab 2 - 3D Colored Cube");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);

    glClearColor(1, 1, 1, 1);       // white background
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glutMainLoop();
    return EXIT_SUCCESS;
}
```
# Table 
```cpp
/*
===========================================
  LAB 3 — 3D Table (built from cubes)
===========================================
  Concepts:
  - Building complex objects from cube()
  - glPushMatrix / glPopMatrix per part
  - glTranslated + glScalef for positioning
  - Composing a multi-part scene

  Controls:
    a / b  — rotate X axis +/-
    c / d  — rotate Y axis +/-
    e / f  — rotate Z axis +/-
    q / ESC — quit
===========================================
*/

#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

float degreeX = 0;
float degreeY = 0;
float degreeZ = 0;

// ---- Projection / Resize ----
static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// ---- Cube Primitive ----
void cube()
{
    glBegin(GL_QUADS);

    glColor3f(1, 0, 0);
    glVertex3f(0,1,0); glVertex3f(1,1,0);
    glVertex3f(1,0,0); glVertex3f(0,0,0);

    glColor3f(1, 1, 0);
    glVertex3f(0,1,1); glVertex3f(0,1,0);
    glVertex3f(0,0,0); glVertex3f(0,0,1);

    glColor3f(0, 0, 1);
    glVertex3f(1,1,1); glVertex3f(0,1,1);
    glVertex3f(0,0,1); glVertex3f(1,0,1);

    glColor3f(0, 1, 0);
    glVertex3f(1,1,0); glVertex3f(1,1,1);
    glVertex3f(1,0,1); glVertex3f(1,0,0);

    glColor3f(1, 0, 1);
    glVertex3f(1,0,1); glVertex3f(0,0,1);
    glVertex3f(0,0,0); glVertex3f(1,0,0);

    glColor3f(0, 1, 1);
    glVertex3f(1,1,0); glVertex3f(0,1,0);
    glVertex3f(0,1,1); glVertex3f(1,1,1);

    glEnd();
}

// ---- Table ----
// Tabletop + 4 corner legs, all made of scaled cubes
void table()
{
    // --- Tabletop (wide flat slab) ---
    glPushMatrix();
    glColor3f(1, .3f, .3f);
    glTranslated(-3, -0.5, -6);
    glScalef(6, 0.5f, 4);
    cube();
    glPopMatrix();

    // --- Leg: back-left ---
    glPushMatrix();
    glTranslated(-3, -6, -6);
    glScalef(0.5f, 6, 0.5f);
    cube();
    glPopMatrix();

    // --- Leg: back-right ---
    glPushMatrix();
    glTranslated(2.5f, -6, -6);
    glScalef(0.5f, 6, 0.5f);
    cube();
    glPopMatrix();

    // --- Leg: front-left ---
    glPushMatrix();
    glTranslated(-3, -6, -3);
    glScalef(0.5f, 6, 0.5f);
    cube();
    glPopMatrix();

    // --- Leg: front-right ---
    glPushMatrix();
    glTranslated(2.5f, -6, -3);
    glScalef(0.5f, 6, 0.5f);
    cube();
    glPopMatrix();
}

// ---- Display Callback ----
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(0, 0, -7);

    // Rotate around table center
    glTranslated(-3, -0.5, -6);
    glRotated(degreeX, 1, 0, 0);
    glRotated(degreeY, 0, 1, 0);
    glRotated(degreeZ, 0, 0, 1);
    glTranslated( 3,  0.5,  6);

    table();
    glutSwapBuffers();
}

// ---- Keyboard ----
static void key(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 27:
        case 'q': exit(0);         break;
        case 'a': degreeX += 5;    break;
        case 'b': degreeX -= 5;    break;
        case 'c': degreeY += 5;    break;
        case 'd': degreeY -= 5;    break;
        case 'e': degreeZ += 5;    break;
        case 'f': degreeZ -= 5;    break;
    }
    glutPostRedisplay();
}

static void idle(void) { glutPostRedisplay(); }

// ---- Main ----
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Lab 3 - Table");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1, 1, 1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glutMainLoop();
    return EXIT_SUCCESS;
}
```

# Fan Jack
```cpp
/*
===========================================
  LAB 4 — Table + Spinning Fan + Jack Toy
===========================================
  Concepts:
  - Animation with glutIdleFunc
  - Spinning blades using angle variable
  - Cylinder built with GL_POLYGON + GL_QUAD_STRIP
  - Jack toy: 3 elongated spheres + 6 ball tips
  - glutSolidSphere for round objects
  - Composing multiple objects in one scene

  Controls:
    a / b  — rotate X axis +/-
    c / d  — rotate Y axis +/-
    e / f  — rotate Z axis +/-
    q / ESC — quit
===========================================
*/

#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <bits/stdc++.h>

float degreeX = 0, degreeY = 0, degreeZ = 0;
float angle   = 0;   // live spin angle for fan blades

// ---- Projection / Resize ----
static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// ---- Cube Primitive ----
void cube()
{
    glBegin(GL_QUADS);

    glColor3f(1,0,0);
    glVertex3f(0,1,0); glVertex3f(1,1,0);
    glVertex3f(1,0,0); glVertex3f(0,0,0);

    glColor3f(1,1,0);
    glVertex3f(0,1,1); glVertex3f(0,1,0);
    glVertex3f(0,0,0); glVertex3f(0,0,1);

    glColor3f(0,0,1);
    glVertex3f(1,1,1); glVertex3f(0,1,1);
    glVertex3f(0,0,1); glVertex3f(1,0,1);

    glColor3f(0,1,0);
    glVertex3f(1,1,0); glVertex3f(1,1,1);
    glVertex3f(1,0,1); glVertex3f(1,0,0);

    glColor3f(1,0,1);
    glVertex3f(1,0,1); glVertex3f(0,0,1);
    glVertex3f(0,0,0); glVertex3f(1,0,0);

    glColor3f(0,1,1);
    glVertex3f(1,1,0); glVertex3f(0,1,0);
    glVertex3f(0,1,1); glVertex3f(1,1,1);

    glEnd();
}

// ---- Table ----
void table()
{
    glPushMatrix();
    glColor3f(1,.3f,.3f);
    glTranslated(-3,-.5,-6);
    glScalef(6,.5f,4);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3,-6,-6);
    glScalef(.5f,6,.5f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.5f,-6,-6);
    glScalef(.5f,6,.5f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3,-6,-3);
    glScalef(.5f,6,.5f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.5f,-6,-3);
    glScalef(.5f,6,.5f);
    cube();
    glPopMatrix();
}

// ---- Cylinder (used for fan motor head) ----
// r,g,b = color of bottom cap  (top=green, wall=blue)
void circle(double r, double g, double b)
{
    // Bottom cap
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        double theta = 2 * 3.1416 * i / 360;
        glVertex3f(cos(theta), sin(theta), 0);
    }
    glEnd();

    // Top cap
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        double theta = 2 * 3.1416 * i / 360;
        glVertex3f(cos(theta), sin(theta), 0.8f);
    }
    glEnd();

    // Side wall
    glColor3f(0, 0, 1);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 360; i++) {
        double theta = 2 * 3.1416 * i / 360;
        float  x     = cos(theta);
        float  y     = sin(theta);
        glVertex3f(x, y, 0);
        glVertex3f(x, y, 0.8f);
    }
    glEnd();
}

// ---- Fan Blade ----
// rot  = fixed angular offset (0, 120, 240 degrees)
// angle= live spinning value updated by idle()
void wing(GLdouble rot)
{
    glPushMatrix();
    glRotated(rot,   0, 0, 1);   // fixed offset
    glRotatef(angle, 0, 0, 1);   // live spin
    glScalef(1.8f, .3f, 0.05f);
    cube();
    glPopMatrix();
}

// ---- Ceiling Fan ----
void fan()
{
    glPushMatrix();
    glTranslated(0, 0, -4);

    // Pole
    glPushMatrix();
    glTranslated(0, 0, -0.25f);
    glScalef(0.3f, 2, 0.3f);
    cube();
    glPopMatrix();

    // Motor cylinder
    glTranslated(0.1f, 2, 0);
    glPushMatrix();
    glTranslated(0, 0, -0.3f);
    glScalef(0.5f, 0.5f, 0.5f);
    circle(0, 0, 1);
    glPopMatrix();

    // 3 blades at 120° apart
    wing(0);
    wing(120);
    wing(240);

    glPopMatrix();
}

// ---- Sphere helper (for Jack) ----
void spherical(GLdouble tx, GLdouble ty, GLdouble tz,
               GLdouble rotan,
               GLdouble rx, GLdouble ry, GLdouble rz,
               GLdouble sx, GLdouble sy, GLdouble sz)
{
    glPushMatrix();
    glTranslated(tx, ty, tz);
    glRotated(rotan, rx, ry, rz);
    glScaled(sx, sy, sz);
    glutSolidSphere(4.0, 50, 50);
    glPopMatrix();
}

// ---- Jack Toy ----
// 3 crossed rods (elongated spheres) + 6 ball tips
void jack()
{
    // 3 rods — stretched along X, Y, Z
    glColor3f(0, 1, 0);
    spherical(-12,5,8,  90, 1,0,0,  1, .1, .1);
    spherical(-12,5,8,  90, 0,1,0,  1, .1, .1);
    spherical(-12,5,8,  90, 0,0,1,  1, .1, .1);

    // 6 tips — one at each end
    glColor3f(1, 0, 0);
    spherical(-15.5, 5, 8,   0,0,0,0,  .2,.2,.2);
    spherical( -8.5, 5, 8,   0,0,0,0,  .2,.2,.2);
    spherical(-12,   5, 12,  0,0,0,0,  .2,.2,.2);
    spherical(-12,   5, 3.7, 0,0,0,0,  .2,.2,.2);
    spherical(-12,   9, 8,   0,0,0,0,  .2,.2,.2);
    spherical(-12,   1, 8,   0,0,0,0,  .2,.2,.2);
}

// ---- Scene: Table + Fan + Jack ----
void tableElements()
{
    table();

    glPushMatrix();
    glTranslated(-1.5, 0, 0);
    fan();
    glPopMatrix();

    glScaled(0.3, 0.3, 0.3);
    glTranslated(14, 13, -18);
    glRotated(60, 1, 0, 1);
    jack();
}

// ---- Display Callback ----
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(0, 0, -7);

    glTranslated(-3, -0.5, -6);
    glRotated(degreeX, 1, 0, 0);
    glRotated(degreeY, 0, 1, 0);
    glRotated(degreeZ, 0, 0, 1);
    glTranslated( 3,  0.5,  6);

    tableElements();
    glutSwapBuffers();
}

// ---- Idle (Animation) ----
void spin()
{
    angle += 0.5f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
}

// ---- Keyboard ----
static void key(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 27:
        case 'q': exit(0);      break;
        case 'a': degreeX += 5; break;
        case 'b': degreeX -= 5; break;
        case 'c': degreeY += 5; break;
        case 'd': degreeY -= 5; break;
        case 'e': degreeZ += 5; break;
        case 'f': degreeZ -= 5; break;
    }
    glutPostRedisplay();
}

// ---- Main ----
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Lab 4 - Table + Fan + Jack");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(spin);            // starts fan animation

    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return EXIT_SUCCESS;
}
```

# Glulookat Camera 
```cpp
/*
===========================================
  LAB 5 — Viewing Transformation (gluLookAt)
===========================================
  Concepts:
  - gluLookAt(eye, center, up)
  - Moving the camera in 3D space
  - GL_MODELVIEW vs GL_PROJECTION matrix
  - Camera controls separate from object rotation
  - Same scene as Lab 4, different viewpoint control

  Controls:
    x / X  — rotate scene X +/-
    y / Y  — rotate scene Y +/-
    z / Z  — rotate scene Z +/-
    c / C  — move camera right / left
    d / D  — move camera up / down
    e / E  — zoom out / zoom in
    ESC    — quit
===========================================
*/

#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <bits/stdc++.h>

float  degreeX = 0, degreeY = 0, degreeZ = 0;
float  angle   = 0;

// Camera eye position (moves with c/d/e keys)
double ex = 0, ey = 0, ez = 5;

// ---- Projection / Resize ----
static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    // NOTE: do NOT reset MODELVIEW here — gluLookAt handles it in display()
}

// ---- Cube Primitive ----
void cube()
{
    glBegin(GL_QUADS);

    glColor3f(1,0,0);
    glVertex3f(0,1,0); glVertex3f(1,1,0);
    glVertex3f(1,0,0); glVertex3f(0,0,0);

    glColor3f(1,1,0);
    glVertex3f(0,1,1); glVertex3f(0,1,0);
    glVertex3f(0,0,0); glVertex3f(0,0,1);

    glColor3f(0,0,1);
    glVertex3f(1,1,1); glVertex3f(0,1,1);
    glVertex3f(0,0,1); glVertex3f(1,0,1);

    glColor3f(0,1,0);
    glVertex3f(1,1,0); glVertex3f(1,1,1);
    glVertex3f(1,0,1); glVertex3f(1,0,0);

    glColor3f(1,0,1);
    glVertex3f(1,0,1); glVertex3f(0,0,1);
    glVertex3f(0,0,0); glVertex3f(1,0,0);

    glColor3f(0,1,1);
    glVertex3f(1,1,0); glVertex3f(0,1,0);
    glVertex3f(0,1,1); glVertex3f(1,1,1);

    glEnd();
}

// ---- Table ----
void table()
{
    glPushMatrix();
    glColor3f(1,.3f,.3f);
    glTranslated(-3,-.5,-6); glScalef(6,.5f,4); cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3,-6,-6);  glScalef(.5f,6,.5f); cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.5f,-6,-6); glScalef(.5f,6,.5f); cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3,-6,-3);  glScalef(.5f,6,.5f); cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.5f,-6,-3); glScalef(.5f,6,.5f); cube();
    glPopMatrix();
}

// ---- Cylinder ----
void circle(double r, double g, double b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        double t = 2 * 3.1416 * i / 360;
        glVertex3f(cos(t), sin(t), 0);
    }
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        double t = 2 * 3.1416 * i / 360;
        glVertex3f(cos(t), sin(t), 0.8f);
    }
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 360; i++) {
        double t = 2 * 3.1416 * i / 360;
        glVertex3f(cos(t), sin(t), 0);
        glVertex3f(cos(t), sin(t), 0.8f);
    }
    glEnd();
}

// ---- Fan ----
void wing(GLdouble rot)
{
    glPushMatrix();
    glRotated(rot,   0, 0, 1);
    glRotatef(angle, 0, 0, 1);
    glScalef(1.8f, .3f, 0.05f);
    cube();
    glPopMatrix();
}

void fan()
{
    glPushMatrix();
    glTranslated(0, 0, -4);

    glPushMatrix();
    glTranslated(0, 0, -0.25f);
    glScalef(0.3f, 2, 0.3f);
    cube();
    glPopMatrix();

    glTranslated(0.1f, 2, 0);
    glPushMatrix();
    glTranslated(0, 0, -0.3f);
    glScalef(0.5f, 0.5f, 0.5f);
    circle(0, 0, 1);
    glPopMatrix();

    wing(0); wing(120); wing(240);
    glPopMatrix();
}

// ---- Sphere Helper + Jack ----
void spherical(GLdouble tx, GLdouble ty, GLdouble tz,
               GLdouble rotan,
               GLdouble rx, GLdouble ry, GLdouble rz,
               GLdouble sx, GLdouble sy, GLdouble sz)
{
    glPushMatrix();
    glTranslated(tx,ty,tz);
    glRotated(rotan,rx,ry,rz);
    glScaled(sx,sy,sz);
    glutSolidSphere(4.0, 50, 50);
    glPopMatrix();
}

void jack()
{
    glColor3f(0,1,0);
    spherical(-12,5,8, 90,1,0,0, 1,.1,.1);
    spherical(-12,5,8, 90,0,1,0, 1,.1,.1);
    spherical(-12,5,8, 90,0,0,1, 1,.1,.1);

    glColor3f(1,0,0);
    spherical(-15.5,5,8,  0,0,0,0, .2,.2,.2);
    spherical(-8.5, 5,8,  0,0,0,0, .2,.2,.2);
    spherical(-12,  5,12, 0,0,0,0, .2,.2,.2);
    spherical(-12,  5,3.7,0,0,0,0, .2,.2,.2);
    spherical(-12,  9,8,  0,0,0,0, .2,.2,.2);
    spherical(-12,  1,8,  0,0,0,0, .2,.2,.2);
}

// ---- Full Scene ----
void tableElements()
{
    table();
    glPushMatrix();
    glTranslated(-1.5, 0, 0);
    fan();
    glPopMatrix();

    glScaled(0.3, 0.3, 0.3);
    glTranslated(14, 13, -18);
    glRotated(60, 1, 0, 1);
    jack();
}

// ---- Display Callback ----
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Camera positioned by ex, ey, ez — looking at origin
    gluLookAt(ex, ey, ez,   // eye
              0,  0,  0,    // center
              0,  1,  0);   // up vector

    glTranslated(0, 0, -7);
    glTranslated(-3, -0.5, -6);
    glRotated(degreeX, 1, 0, 0);
    glRotated(degreeY, 0, 1, 0);
    glRotated(degreeZ, 0, 0, 1);
    glTranslated( 3,  0.5,  6);

    tableElements();
    glutSwapBuffers();
}

// ---- Idle ----
void spin()
{
    angle += 0.5f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
}

// ---- Keyboard ----
static void key(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 27: exit(0); break;

        // Object rotation
        case 'x': degreeX += 5; break;
        case 'X': degreeX -= 5; break;
        case 'y': degreeY += 5; break;
        case 'Y': degreeY -= 5; break;
        case 'z': degreeZ += 5; break;
        case 'Z': degreeZ -= 5; break;

        // Camera movement
        case 'c': ex++;  break;   // move camera right
        case 'C': ex--;  break;   // move camera left
        case 'd': ey++;  break;   // move camera up
        case 'D': ey--;  break;   // move camera down
        case 'e': ez++;  break;   // zoom out
        case 'E': ez--;  break;   // zoom in
    }
    glutPostRedisplay();
}

// ---- Main ----
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Lab 5 - gluLookAt Camera");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(spin);

    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return EXIT_SUCCESS;
}
```
# Lightning
```cpp
/*
===========================================
  LAB 6 — Lighting, Materials & Wall
===========================================
  Concepts:
  - glEnable(GL_LIGHTING) + GL_LIGHT0, GL_LIGHT1
  - glMaterialfv() — ambient, diffuse, specular, shininess
  - glEnable(GL_NORMALIZE) — fixes normals after scaling
  - Two lights with different colors (white + yellow)
  - Toggle lights on/off with keyboard
  - Wall constructed from cube slabs (floor, left wall, back wall)
  - glColor3f removed — color comes purely from material

  Controls:
    x / X  — rotate scene X +/-
    y / Y  — rotate scene Y +/-
    z / Z  — rotate scene Z +/-
    c / C  — move camera right / left
    d / D  — move camera up / down
    e / E  — zoom out / zoom in
    1 / 0  — enable / disable Light 0 (white)
    7 / 8  — enable / disable Light 1 (yellow)
    ESC    — quit
===========================================
*/

#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <bits/stdc++.h>

float  degreeX = 0, degreeY = 0, degreeZ = 0;
float  angle   = 0;
double ex = 0, ey = 0, ez = 5;

// ---- Projection / Resize ----
static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
}

// ---- Cube Primitive (no glColor — material drives color) ----
void cube()
{
    glBegin(GL_QUADS);

    // Front
    glVertex3f(0,1,0); glVertex3f(1,1,0);
    glVertex3f(1,0,0); glVertex3f(0,0,0);
    // Left
    glVertex3f(0,1,1); glVertex3f(0,1,0);
    glVertex3f(0,0,0); glVertex3f(0,0,1);
    // Back
    glVertex3f(1,1,1); glVertex3f(0,1,1);
    glVertex3f(0,0,1); glVertex3f(1,0,1);
    // Right
    glVertex3f(1,1,0); glVertex3f(1,1,1);
    glVertex3f(1,0,1); glVertex3f(1,0,0);
    // Bottom
    glVertex3f(1,0,1); glVertex3f(0,0,1);
    glVertex3f(0,0,0); glVertex3f(1,0,0);
    // Top
    glVertex3f(1,1,0); glVertex3f(0,1,0);
    glVertex3f(0,1,1); glVertex3f(1,1,1);

    glEnd();
}

// ---- Material Helpers ----
void setWoodMaterial()
{
    GLfloat amb[]  = {0.7f, 0.2f, 0.0f, 1.0f};
    GLfloat diff[] = {0.7f, 0.2f, 0.0f, 1.0f};
    GLfloat spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat shin[] = {100.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shin);
}

void setWallMaterial()
{
    GLfloat amb[]  = {0.4f, 1.0f, 0.4f, 1.0f};
    GLfloat diff[] = {0.4f, 1.0f, 0.8f, 1.0f};
    GLfloat spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat shin[] = {100.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shin);
}

void setMetalMaterial()
{
    GLfloat amb[]  = {0.0f, 0.0f, 0.2f, 1.0f};
    GLfloat diff[] = {0.0f, 0.0f, 1.0f, 0.6f};
    GLfloat spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat shin[] = {100.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shin);
}

// ---- Table (wood material) ----
void table()
{
    setWoodMaterial();

    glPushMatrix();
    glTranslated(-3,-.5,-6); glScalef(6,.5f,4); cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3,-6,-6);  glScalef(.5f,6,.5f); cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.5f,-6,-6); glScalef(.5f,6,.5f); cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3,-6,-3);  glScalef(.5f,6,.5f); cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.5f,-6,-3); glScalef(.5f,6,.5f); cube();
    glPopMatrix();
}

// ---- Cylinder ----
void circle(double r, double g, double b)
{
    // Bottom cap
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        double t = 2 * 3.1416 * i / 360;
        glVertex3f(cos(t), sin(t), 0);
    }
    glEnd();

    // Top cap
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        double t = 2 * 3.1416 * i / 360;
        glVertex3f(cos(t), sin(t), 0.8f);
    }
    glEnd();

    // Side wall
    glColor3f(1, 0, 0);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 360; i++) {
        double t = 2 * 3.1416 * i / 360;
        glVertex3f(cos(t), sin(t), 0);
        glVertex3f(cos(t), sin(t), 0.8f);
    }
    glEnd();
}

// ---- Fan (metal material on blades) ----
void wing(GLdouble rot)
{
    glPushMatrix();

    setMetalMaterial();

    glRotated(rot,   0, 0, 1);
    glRotatef(angle, 0, 0, 1);
    glScalef(1.8f, .3f, 0.05f);
    cube();
    glPopMatrix();
}

void fan()
{
    glPushMatrix();
    glTranslated(0, 0, -4);

    glPushMatrix();
    glTranslated(0, 0, -0.25f);
    glScalef(0.3f, 2, 0.3f);
    cube();
    glPopMatrix();

    glTranslated(0.1f, 2, 0);
    glPushMatrix();
    glTranslated(0, 0, -0.3f);
    glScalef(0.5f, 0.5f, 0.5f);
    circle(0, 0, 1);
    glPopMatrix();

    wing(0); wing(120); wing(240);
    glPopMatrix();
}

// ---- Sphere helper ----
void spherical(GLdouble tx, GLdouble ty, GLdouble tz,
               GLdouble rotan,
               GLdouble rx, GLdouble ry, GLdouble rz,
               GLdouble sx, GLdouble sy, GLdouble sz)
{
    glPushMatrix();

    GLfloat amb[]  = {0.0f, 0.0f, 0.2f, 1.0f};
    GLfloat diff[] = {0.0f, 0.0f, 1.0f, 0.6f};
    GLfloat spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat shin[] = {100.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shin);

    glTranslated(tx,ty,tz);
    glRotated(rotan,rx,ry,rz);
    glScaled(sx,sy,sz);
    glutSolidSphere(4.0, 50, 50);
    glPopMatrix();
}

void jack()
{
    spherical(-12,5,8, 90,1,0,0, 1,.1,.1);
    spherical(-12,5,8, 90,0,1,0, 1,.1,.1);
    spherical(-12,5,8, 90,0,0,1, 1,.1,.1);

    spherical(-15.5,5,8,  0,0,0,0, .2,.2,.2);
    spherical(-8.5, 5,8,  0,0,0,0, .2,.2,.2);
    spherical(-12,  5,12, 0,0,0,0, .2,.2,.2);
    spherical(-12,  5,3.7,0,0,0,0, .2,.2,.2);
    spherical(-12,  9,8,  0,0,0,0, .2,.2,.2);
    spherical(-12,  1,8,  0,0,0,0, .2,.2,.2);
}

// ---- Wall (3 slabs: floor, left, back) ----
void wallSlab(GLdouble tx, GLdouble ty, GLdouble tz,
              GLdouble rotan,
              GLdouble rx, GLdouble ry, GLdouble rz,
              GLdouble sx, GLdouble sy, GLdouble sz)
{
    glPushMatrix();
    setWallMaterial();
    glTranslated(tx, ty, tz);
    glRotated(rotan, rx, ry, rz);
    glScalef(sx, sy, sz);
    cube();
    glPopMatrix();
}

void wall()
{
    // Floor slab
    wallSlab(-10,-7,-10,  0,0,0,0,  18, .1, 10);
    // Left wall
    wallSlab(-10,-7,-10,  0,0,0,0,  .1, 14, 10);
    // Back wall
    wallSlab(-10,-7,-10,  0,0,0,0,  18, 14, .1);
}

// ---- Full Scene ----
void tableElements()
{
    table();

    glPushMatrix();
    glTranslated(-1.5, 0, 0);
    fan();
    glPopMatrix();

    glScaled(0.3, 0.3, 0.3);
    glTranslated(14, 13, -18);
    glRotated(60, 1, 0, 1);
    jack();
}

// ---- Display Callback ----
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(ex, ey, ez,
              0,  0,  0,
              0,  1,  0);

    glTranslated(0, 0, -15);
    glTranslated(-3, -0.5, -6);
    glRotated(degreeX, 1, 0, 0);
    glRotated(degreeY, 0, 1, 0);
    glRotated(degreeZ, 0, 0, 1);
    glTranslated( 3,  0.5,  6);

    glPushMatrix();
    wall();
    glPopMatrix();

    tableElements();
    glutSwapBuffers();
}

// ---- Idle ----
void spin()
{
    angle += 0.5f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
}

// ---- Keyboard ----
static void key(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 27: exit(0); break;

        case 'x': degreeX += 5; break;
        case 'X': degreeX -= 5; break;
        case 'y': degreeY += 5; break;
        case 'Y': degreeY -= 5; break;
        case 'z': degreeZ += 5; break;
        case 'Z': degreeZ -= 5; break;

        case 'c': ex++;  break;
        case 'C': ex--;  break;
        case 'd': ey++;  break;
        case 'D': ey--;  break;
        case 'e': ez++;  break;
        case 'E': ez--;  break;

        // Light toggles
        case '1': glEnable(GL_LIGHT0);  break;
        case '0': glDisable(GL_LIGHT0); break;
        case '7': glEnable(GL_LIGHT1);  break;
        case '8': glDisable(GL_LIGHT1); break;
    }
    glutPostRedisplay();
}

// ---- Lighting Setup ----
void initLighting()
{
    glEnable(GL_LIGHTING);

    // Light 0 — white, upper right
    glEnable(GL_LIGHT0);
    GLfloat amb0[]  = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diff0[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat spec0[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat pos0[]  = {5.0f, 3.0f, 7.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT,  amb0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diff0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);

    // Light 1 — yellow, upper left
    glEnable(GL_LIGHT1);
    GLfloat amb1[]  = {0.2f, 0.2f, 0.0f, 1.0f};
    GLfloat diff1[] = {1.0f, 1.0f, 0.5f, 1.0f};
    GLfloat spec1[] = {1.0f, 1.0f, 0.0f, 1.0f};
    GLfloat pos1[]  = {-5.0f, 5.0f, 2.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_AMBIENT,  amb1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  diff1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
    glLightfv(GL_LIGHT1, GL_POSITION, pos1);
}

// ---- Main ----
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Lab 6 - Lighting & Materials");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(spin);

    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    initLighting();

    glutMainLoop();
    return EXIT_SUCCESS;
}
```
