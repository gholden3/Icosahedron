// Draw an Icosahedron
// ECE4893/8893 Project 4
// YOUR NAME HERE

#include <iostream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <map>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

#define NFACE 20
#define NVERTEX 12
#define DEG2RAD M_PI/180;
#define X .525731112119133606 
#define Z .850650808352039932

void drawIcosahedron(int);

// These are the 12 vertices for the icosahedron
static GLfloat vdata[NVERTEX][3] = {    
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
};

// These are the 20 faces.  Each of the three entries for each 
// vertex gives the 3 vertices that make the face.
static GLint tindices[NFACE][3] = { 
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

int testNumber; // Global variable indicating which test number is desired
int divisions = 0;
// Test cases.  Fill in your code for each test case
void Test1()
{
  cout << "hello from Test1()" << endl;
  drawIcosahedron(0);
//  glFlush();
}

void Test2()
{
}

void Test3()
{
}

void Test4()
{
}

void Test5(int depth)
{
}

void Test6(int depth)
{
}

void drawTriangle(GLfloat* v1, GLfloat* v2, GLfloat* v3)
{
  glBegin(GL_TRIANGLES);
  glColor3f(0.0,0.0,1.0);
  glVertex3fv(v1);
  glVertex3fv(v2);
  glVertex3fv(v3);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glColor3f(1.0,1.0,1.0); //white lines
  glVertex3fv(v1);
  glVertex3fv(v2);
  glVertex3fv(v3);
  glEnd();
}


void subDivide(GLfloat* v1, GLfloat* v2, GLfloat * v3, int depth){
  if(depth==0){
     cout << "hello from subdivide. depth = "<< depth << endl;
    drawTriangle(v1,v2,v3);
    return;
  }
}

void drawIcosahedron(int maxDepth){
  for(int i =0;i<NFACE; i++){
    subDivide(&vdata[tindices[i][0]][0],
                &vdata[tindices[i][1]][0],
                &vdata[tindices[i][2]][0],maxDepth);
  }
}

void display(void)
{ cout << "hello from display()."<< endl;
  //static int pass;
                            
  //cout << "Displaying pass " << ++pass << endl;
  // clear al
  glEnable(GL_LINE_SMOOTH);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);
  // Clear the matrix
  glLoadIdentity();
  // Set the viewing transformation
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glTranslatef(250, 250, 0);
  glScalef(100.0, 100.0, 0);
  //drawTriangle();
  switch(testNumber)
    {
      case 1 :{
        cout << "hello from case 1" << endl;
        Test1();
        //drawIcosahedron(0);
       }
        break;
      case 2 : 
        Test2();
        break;
      case 3 : 
        Test3();
        break;
      case 4 :
        Test4();
        break;
      case 5 :
        Test5(divisions);
        break;
      case 6 :
        Test6(divisions);
        break;
    }
  // Flush buffer
  //glFlush(); // If single buffering
  glutSwapBuffers(); // If double buffering
}

void init(){
  //select clearing (background) color
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}

void normalize(GLfloat v[3]){
  GLfloat d = sqrt(v[0]*v[0] + v[1]*v[1] +v[2]*v[2]);
  if(d ==0) return;
  v[0] /= d;
  v[1] /= d;
  v[2] /= d;  

}


void reshape(int w, int h)
{
  glViewport(0,0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, (GLdouble)w, (GLdouble)0.0, h, (GLdouble)-w, (GLdouble)w);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


void timer(int){
  glutPostRedisplay();
  glutTimerFunc(25.0,timer,0);
}



int main(int argc, char** argv)
{
  if (argc < 2)
    {
      std::cout << "Usage: icosahedron testnumber" << endl;
      exit(1);
    }
  // Set the global test number
  testNumber = atol(argv[1]);
  if(argc>2)
    divisions = atoi(argv[2]);
  // Initialize glut  and create your window here
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Icosahedron");
  init();
  // Set your glut callbacks here
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(25.0, timer, 0);
  // Enter the glut main loop here
  glutMainLoop();
  return 0;
}

