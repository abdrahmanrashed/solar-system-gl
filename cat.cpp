#include <bits/stdc++.h>
//using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <windows.h>
using ld = long double;
constexpr ld PI = 3.1415926535897932384626433832L;

void arc(ld r, ld theta, ld phi, ld px = 0, ld py = 0){
    glLineWidth(7.2);
    glBegin(GL_POLYGON);

    int len = 20;
    ld dt = (phi - theta) / len;
    for(int i = 0; i <= len; i++){
        glVertex2d(px + r * cosl(i * dt + theta), py + r * sinl(i * dt + theta));
    }
    glVertex2d(px, py);

    glEnd();
}
void oval(ld r1, ld r2, ld theta, ld phi, ld px = 0, ld py = 0){
    glLineWidth(7.2);
    glBegin(GL_POLYGON);

    int len = 20;
    ld dt = (phi - theta) / len;
    ld dr = abs(r2 - r1) / len;
    for(int i = 0; i <= len; i++){
        glVertex2d(px + (dr * i + r1) * cosl(i * dt + theta), py + (dr * i + r1) * sinl(i * dt + theta));
    }
    glVertex2d(px, py);

    glEnd();
}
void rectangle(ld x1, ld x2, ld y1, ld y2){
    glLineWidth(7.2);
    glBegin(GL_POLYGON);

    glVertex2d(x1, y1);
    glVertex2d(x1, y2);
    glVertex2d(x2, y2);
    glVertex2d(x2, y1);

    glEnd();
}
void triangle(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3){
    glLineWidth(7.2);
    glBegin(GL_POLYGON);

    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glVertex2d(x3, y3);

    glEnd();
}
void line(ld x1, ld x2, ld y1, ld y2){
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);

    glVertex2d(x1, y1);
    glVertex2d(x2, y2);

    glEnd();
}
ld dear = 0.09, ear = 0;
ld dker = 0.01, ker = 0;

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3d(244.0 / 255, 125.0 / 255, 22.0 / 255); //orange
    triangle(-5, 0, -4 + ear * 1.3, 4, -1, 0);
    triangle(5, 0, 4 - ear * 1.3, 4, 1, 0);
    rectangle(-5, 5, -2, 0);
    arc(5, -PI / 2, 0, 0, -2);
    arc(5, -PI / 2, -PI, 0, -2);

    glColor3d(238.0 / 255, 165.0 / 255, 239.0 / 255); //pink
    triangle(-4.52, 0, -3.8 + ear, 3, -1.7, 0);
    triangle(4.52, 0, 3.8 - ear, 3, 1.7, 0);
    ear += dear;
    if(ear >= 1.3 || ear <= -1.3) dear = -dear;

    glColor3d(1, 1, 1); //white
    oval(0.7, 2, 0, PI / 2, -3, -2.5);
    oval(0.7, 2, PI, PI / 2, -3, -2.5);
    oval(0.7, 2, 0, PI / 2, 3, -2.5);
    oval(0.7, 2, PI, PI / 2, 3, -2.5);

    glColor3d(0, 0, 0); //black
    arc(0.5, 0, PI, 0, -3);
    triangle(0, -3.3, 0.5, -3, -0.5, -3);
    oval(0.5, 1.7, 0, PI / 2, -3, -2.5);
    oval(0.5, 1.7, PI, PI / 2, -3, -2.5);
    oval(0.5, 1.7, 0, PI / 2, 3, -2.5);
    oval(0.5, 1.7, PI, PI / 2, 3, -2.5);

    auto kx2 = [=](ld kx, ld ky) {return kx * cosl(ker) - (ky + 3) * sinl(ker);};
    auto ky2 = [=](ld kx, ld ky) {return kx * sinl(ker) + (ky + 3) * cosl(ker) - 3;};
    using std::array;
    array<ld, 4> arr[] = {
        array<ld, 4>({0, 1.2, -3, -2.9}),
        array<ld, 4>({0, 1.1, -2.95, -2.6}),
        array<ld, 4>({0, 1.05, -3.05, -3.2}),
        array<ld, 4>({0, -1.2, -3, -2.9}),
        array<ld, 4>({0, -1.1, -2.95, -2.6}),
        array<ld, 4>({0, -1.05, -3.05, -3.2})
    };
    for(int j = 0; j < 6; j++){
        auto kur = arr[j];
        line(kur[0], kx2(kur[1], kur[3]), kur[2], ky2(kur[1], kur[3]));
    }
    ker += dker;
    if(ker >= 10 * PI / 180 || ker <= -10 * PI / 180) dker = -dker;

    glColor3d(255.0 / 255, 7.0 / 255, 36.0 / 255); //red
    arc(1.5, 0.3, -PI / 2, 0, -4.5);
    arc(1.5, -PI - 0.3, -PI / 2, 0, -4.5);

    glFlush();
    glClear(GL_COLOR_BUFFER_BIT);
}
void reshape(int w,int h){
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-12, 12, -8, 8, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}
void timer(int)
{
    int fps = 60;
    glutPostRedisplay();
    glutTimerFunc(1000 / fps, timer, 0);

}
int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200,0);
    glutInitWindowSize(1200, 800);

    glutCreateWindow("cat");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glClearColor(63.0 / 255, 137.0 / 255, 234.0 / 255, 0.0);

    glutMainLoop();
}