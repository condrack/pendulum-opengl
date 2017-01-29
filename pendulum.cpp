/*
Taylor Condrack 
Program 2
4230
02/14/16
Program Description: This program creates a interactive pendulum.
Right clicking will display a menu. The pendulum can spin counter
clockwise, clockwise, and remain still.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static GLfloat spin = 0.0;
static float r = 1.0;
static float l = 8.0;
static int a;
static int b;
static int data;
void menu(int);

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}
void pendulum(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
//sets the point size to 5 pixels
    glPointSize(5.0f);
//draws anchor point
    glBegin(GL_POINTS);
        glVertex3f(0,0,0);
    glEnd();
//sets spin and spin speed
    glRotatef(spin, 0.0, 0.0, 1.0);
//makes the line width 2
    glLineWidth(2.0);
//draws line attached to anchor
    glBegin(GL_LINES);
        glVertex3f(-0.0, -0.0, 0.0);
        glVertex3f(0,-8,0);
    glEnd();
//translates position to the othe rend of the line for the hexagon
    glTranslatef(0,-8.0,0);
//draws a blue hexagon
    glBegin(GL_POLYGON);
        glColor3f(0,0,128);
        for(int i=0;i<6;i++)
        {
            glVertex2d(r*sin(i/6.0*2*M_PI),r*cos(i/6.0*2*M_PI));
        }
    glEnd();

   glColor3f(1.0, 1.0, 1.0);
   glPopMatrix();
   glutSwapBuffers();
}
//spin callback for counter clockwise
void spinDisplay1(void)
{
    spin = spin + 2.0;

    if(spin > 360.0)
        spin = spin - 360.0;

    glutPostRedisplay();
}
//spin callback for clockwise
void spinDisplay2()
{
    spin = spin -2.0;

    if(spin>360.0)
        spin = spin -360.0;

    glutPostRedisplay();
}
//creates view volume and square viewport
void reshape(int w, int h)
{
//viewport creates a square
    glViewport ((w-h)/2, 0, (GLsizei) h, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.3*l, 1.3*l, -1.3*l, 1.3*l, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN)
                glutIdleFunc(spinDisplay1);
            break;
        case GLUT_MIDDLE_BUTTON:
            if(state == GLUT_DOWN)
                glutIdleFunc(NULL);
            break;
        default:
            break;
   }
}

/*
 *  Request double buffer display mode.
 *  Register mouse input callback functions
 */
//creates the popup menu on rightclick
void popupmenu()
{
//calls the menu function to give commands to each item in the menu
    a = glutCreateMenu(menu);

    glutAddMenuEntry("Rotate counterclockwise '+'",1);
    glutAddMenuEntry("Rotate clockwise '-'",2);
    glutAddMenuEntry("Stop rotation <space>",3);
    glutAddMenuEntry("Exit Program <escape>",4);
//activiates menu on a right click
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void menu(int in)
{
    if(in==0)
    {
        glutDestroyWindow(b);
        exit(0);
    }
    if(in==1)
    {
        glutIdleFunc(spinDisplay1);
    }
    if(in==2)
    {
        glutIdleFunc(spinDisplay2);
    }
    if(in==3)
    {
        glutIdleFunc(NULL);
    }
    if(in==4)
    {
        exit(0);
    }
    else
    {
        data=in;
    }
    glutPostRedisplay();
}
//function to allow the user to activate the menu commands by their hotkeys
void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 27:
            exit(0);
            break;
        case 43:
            glutIdleFunc(spinDisplay1);
            break;
        case 45:
            glutIdleFunc(spinDisplay2);
            break;
        case 32:
            glutIdleFunc(NULL);
            break;


    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    popupmenu();
    glutDisplayFunc(pendulum);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
