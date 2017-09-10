#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#define round(a) ((int)(a+0.5))

struct line
{
	int x1, y1;
	int x2, y2;
}L;

typedef struct line line;

void init(line *l)
{
	l->x1 = l->x2 = l->y1 = l->y2 = 0;
}

void getLine(line *l)
{
	printf("Enter the start and end points:\n(x1,y1),(x2,y2)\n");
	scanf("%d %d", &l->x1, &l->y1);
	scanf("%d %d", &l->x2, &l->y2);
}

int sign(int x)
{
	if (x==0)
		return 0;
	else
		return x<0? -1:1;
}

void setpX(GLint XCv, GLint yCv)
{
	glBegin (GL_POINTS);
		glVertex2i(XCv,yCv);
	glEnd();
}

int absl (int n)
{
    return ( (n>0) ? n : ( n * (-1)));
}

void DDA()
{
	float dx = L.x2-L.x1;
	float dy = L.y2-L.y1;
	float len = absl(dx) > absl(dy) ? absl(dx) : absl(dy) ; 
	float delx = dx/(float)len;
	float dely = dy/(float)len;
	float x = L.x1, y = L.y1;
	// x = x + 0.5*sign(dx);
	// y = y + 0.5*sign(dy);
	setpX(x,y);
	while(len--)
	{
		setpX(round(x),round(y));
		x = x+delx;
		y = y+dely;
	}
	
	glFlush();
	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	init(&L);
	getLine(&L);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640,640);
	glutCreateWindow("DDA Line Algo");
	glClearColor(255,255,255,0.f);
	glColor3f(0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(DDA);
	gluOrtho2D(640,0,640,0);
	glutMainLoop();
	return 0;
}