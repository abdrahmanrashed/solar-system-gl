#include "algo.hpp"

ld staticrotation = 0.0;  
ld dynamicrotation = 0.0;      
int delay = 1000 / 75;      
 
void initGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);                     
    glEnable(GL_DEPTH_TEST);  
    glDepthFunc(GL_LEQUAL);    
    glShadeModel(GL_SMOOTH); 
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);    
 
    //sun
    glLoadIdentity(); 
    glTranslated(0, 0.0, -50);  
    glRotated(staticrotation, 1, 1, 1);
    glColor3d(point{247, 203, 7});
    glutSolidSphere(15, 50, 50);
    
    //mercury
    glLoadIdentity();
    glTranslated(0, 0.5, -50);
    glRotated(90, 1, 0, 0);
    orbit(17, 100);
    glRotated(-90, 1, 0, 0);
    glRotated(dynamicrotation * 3.7 - 20, 0, 1, 0);
    glTranslated(0, 0.0, 17);  
    glRotated(staticrotation, 1, 1, 1);
    glColor3d(point{0, 117, 214});
    glutSolidSphere(1, 50, 50);

    //venus
    glLoadIdentity();
    glTranslated(0, -0.5, -50);
    glRotated(90, 1, 0, 0);
    orbit(21, 100);
    glRotated(-90, 1, 0, 0);
    glRotated(dynamicrotation * 2.3, 0, 1, 0);
    glTranslated(0, 0.0, 21);  
    glRotated(staticrotation * 1.3, 1, 1, 1);
    glColor3d(point{193, 202, 204});
    glutSolidSphere(2.8, 50, 50);

    //earth
    glLoadIdentity();
    glTranslated(0, 0.1, -50);
    glRotated(90, 1, 0, 0);
    orbit(28, 100);
    glRotated(-90, 1, 0, 0);
    glRotated(dynamicrotation + 50, 0, 1, 0);
    glTranslated(0, 0, 28);  
    glRotated(staticrotation * 1.7, 1, 8, 1);
    glColor3d(point{0, 255, 7});
    earth(3, 50, 50);

    //moon
    glRotated(staticrotation * 1.7, 1, -8, 1);
    glRotated(staticrotation * 1.7, 1, 5, 2);
    glTranslated(0, -2, 4); 
    glColor3d(point{135, 135, 135});
    glutSolidSphere(1, 50, 50);

    //mars
    glLoadIdentity();
    glTranslated(0, -0.1, -50);
    glRotated(90, 1, 0, 0);
    orbit(33, 100);
    glRotated(-90, 1, 0, 0);
    glRotated(dynamicrotation * 1.5 + 20, 0, 1, 0);
    glTranslated(0, 0, 33);  
    glRotated(staticrotation * 1.3, 1, 1, 1);
    glColor3d(point{251, 81, 30});
    glutSolidSphere(1.5, 50, 50);

    glutSwapBuffers();  
    staticrotation += 0.25;
}
void timer(int value) {
    glutPostRedisplay();      
    glutTimerFunc(delay, timer, 0);
}
void reshape(GLsizei width, GLsizei height) {   
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
    glViewport(0, 0, width, height);
 
    glMatrixMode(GL_PROJECTION);  

    glLoadIdentity();   
    gluPerspective(60.0, aspect, 0.1, 100.0);
}
void normalinput(unsigned char key, int x, int y){
    switch(key){
        case 'a':
            dynamicrotation--;
            break;
        case 'd':
            dynamicrotation++;
            break;
    }
}
void specialinput(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:
            dynamicrotation--;
            break;
        case GLUT_KEY_RIGHT:
            dynamicrotation++;
            break;
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);         
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1280, 720);    
    glutInitWindowPosition(50, 50); 
    glutCreateWindow("solar system"); 
    glutDisplayFunc(display);     
    glutReshapeFunc(reshape); 
    glutKeyboardFunc(normalinput);     
    glutSpecialFunc(specialinput);  
    initGL();                     
    glutTimerFunc(0, timer, 0);  
    glutMainLoop();                
    return 0;
}