#include <bits/stdc++.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <windows.h>

using std::array;
using std::vector;
using ld = GLdouble;
constexpr ld PI = 3.1415926535897932384626433832L;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct point{
    ld x, y, z;

    point(ld x = 0, ld y = 0, ld z = 0) : x(x), y(y), z(z) {}
    point(array<ld, 3> p) : x(p[0]), y(p[1]), z(p[2]) {}

    point operator-() {
        x = -x, y = -y, z = -z; return *this;
    }
    point operator+=(point p) {
        x += p.x, y += p.y, z += p.z; return *this;
    }
    point operator-=(point p) {
        return *this += -p;
    }
    ld operator*=(point p) {
        return x * p.x + y * p.y + z * p.x;
    }
    point operator*=(ld c) {
        x *= c, y *= c, z *=c; return *this;
    }
    point operator^=(point p){
        return point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
    friend point operator+(point p1, point p2) {
        return p1 += p2;
    }
    friend point operator-(point p1, point p2) {
        return p1 -= p2;
    }
    friend ld operator*(point p1, point p2){
        return p1 *= p2;
    }
    friend point operator*(point p, ld c){
        return p *= c;
    }
    friend point operator*(ld c, point p){
        return p *= c;
    }
    friend point operator^(point p1, point p2){
        return p1 ^= p2;
    }
    friend void glVertex3d(point p){
        return glVertex3d(p.x, p.y, p.z);
    }
    friend void glColor3d(point p){
        return glColor3d(p.x / 255, p.y / 255, p.z / 255);
    }
    friend void glTranslated(point p){
        return glTranslated(p.x, p.y, p.z);
    }
    friend void glRotated(ld angle, point p){
        return glRotated(angle, p.x, p.y, p.z);
    }
};
void square(array<point, 4> p){
    glBegin(GL_POLYGON);
    for(auto& i : p) glVertex3d(i);
    glEnd();
}
std::uniform_real_distribution rearth(0.0, 10.0);

void cearth(bool b){
    if(b) glColor3d(point{15, 86, 16});
    else glColor3d(point{18, 79, 232});
}
auto initalseed = rearth(rng);
void earth(ld radius, int slices, int stacks){
    vector<vector<point>> v(slices + 1, vector<point>(stacks));

    ld dphi = 2 * PI / slices;
    ld dtheta = 2 * PI / stacks;
    for(int i = 0; i <= slices; i++){
        for(int j = 0; j < stacks; j++){
            ld x = cos(dphi * i) * sin(dtheta * j);
            ld y = cos(dtheta * j);
            ld z = sin(dphi * i) * sin(dtheta * j);
            v[i][j] = radius * point(x, y, z);
        }
    }
    auto currentseed = initalseed;
    for(int i = 1; i <= slices; i++){
        cearth(currentseed > 7);
        square({v[i][0], v[i - 1][0], v[i - 1][stacks - 1], v[i][stacks - 1]});
        for(int j = 1; j < stacks; j++){
            cearth(currentseed > 7);
            square({v[i][j], v[i - 1][j], v[i - 1][j - 1], v[i][j - 1]});
            currentseed = fmod(currentseed * 1000000007, 10);
        }
    }
}
void orbit(ld radius, int slices){
    ld dtheta = 2 * PI / slices;
    glBegin(GL_LINE_LOOP);
    glLineWidth(0.5);
    glColor3d(point{200, 200, 200});
    for(int i = 0; i < slices; i++){
        glVertex3d(radius * cos(dtheta * i), radius * sin(dtheta * i), 0);
    }
    glEnd();
}