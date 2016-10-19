#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <stdio.h>

class Vetor {
public:	Vetor(GLdouble x, GLdouble y)  {
		_x = x;
		_y = y;
	};

	void SetX(GLdouble x) {
		_x = x;
	};

	void SetY(GLdouble y) {
		_y = y;
	};

	GLdouble GetX() const {
		return(_x);
	};

	GLdouble GetY() const {
		return(_y);
	};

	void add(Vetor _v) {
		_x += _v.GetX();
		_y += _v.GetY();
	};

	void sub(Vetor _v) {
		_x -= _v.GetX();
		_y -= _v.GetY();
	};

	void div(Vetor _v){
		_x = (_x / _v.GetX());
		_y = (_y / _v.GetY());
	};

	void mult(Vetor _v){
		_x *= _v.GetX();
		_y *= _v.GetY();
	};

	GLdouble mag() {
		return(sqrt((_x*_x) + (_y*_y)));
	};

	void normalize(){
		float _m = mag();

		if (_m > 0){
			div(Vetor (_m,_m));
		}
	};

private:
	GLdouble _x, _y;
};

GLdouble margemEsquerda = -300, margemDireita = 300;
GLdouble margemInferior = 300, margemSuperior = -300;
GLdouble larguraJanela = 600, alturaJanela = 600;

GLdouble _m;
Vetor _mouse(0, 0);

void mouse(int x, int y) {
	_mouse = Vetor(x, y);
	Vetor canto(300, 300);
	_mouse.sub(canto);
	_mouse.normalize();
	_mouse.mult(Vetor (50,50));
	
	glutPostRedisplay();
}

void PontoInical(){
	glLineWidth(2.5);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2d(0.0f, 0.0f);
	glVertex2d(_mouse.GetX(), _mouse.GetY());
	glEnd();
}

void desenha() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_VIEWPORT);

	//viewPort mouse
	glViewport(0, 0, larguraJanela, alturaJanela);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(margemEsquerda, margemDireita, margemInferior, margemSuperior);
	PontoInical();

	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Gc - Normalize Vetor");
	glutDisplayFunc(desenha);
	glutPassiveMotionFunc(mouse);
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glutMainLoop();
	return(0);
}