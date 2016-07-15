#include "LoadBMP.h"
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl\glut.h>
double window_x = 0, window_y = 0, window_z = -20.0, window_a = 30;
GLUquadric *quadric = gluNewQuadric();

//行星
GLfloat rot0 = 30.0;
GLfloat rot1 = 0.0;
GLfloat rot2 = 0.0;
GLfloat rot3 = 0.0;
GLfloat rot4 = 0.0;
GLfloat rot5 = 0.0;
GLfloat rot6 = 0.0;
GLfloat rot7 = 0.0;
GLfloat rot8 = 0.0;
//卫星
GLfloat rot9 = 0.0;
GLfloat rot10 = 0.0;
GLfloat rot11 = 0.0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glShadeModel(GL_FLAT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);	//启用二维纹理
	LoadAllTextures();			//调入纹理
}

void idle()
{
	rot0 += 0.1;
	if (rot0 >= 360.0)
		rot0 -= 360.0;

	rot1 += 0.416;
	if (rot1 >= 360.0)
		rot1 -= 360.0;

	rot2 += 0.1631;
	if (rot2 >= 360.0)
		rot2 -= 360.0;

	rot3 += 0.053;
	if (rot3 >= 360.0)
		rot3 -= 360.0;

	rot4 += 0.0083;
	if (rot4 >= 360.0)
		rot4 -= 360.0;

	rot5 += 0.0034;
	if (rot5 >= 360.0)
		rot5 -= 360.0;

	rot6 += 0.00119;
	if (rot6 >= 360.0)
		rot6 -= 360.0;

	rot7 += 0.00069;
	if (rot7 >= 360.0)
		rot7 -= 360.0;

	rot8 += 0.0008;
	if (rot8 >= 360.0)
		rot8 -= 360.0;

	rot9 += 1.0;
	if (rot9 >= 360.0)
		rot9 -= 360.0;

	rot10 += 0.005;
	if (rot10 >= 360.0)
		rot10 -= 360.0;

	rot11 += 0.01;
	if (rot11 >= 360.0)
		rot11 -= 360.0;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		if (first)
		{
			glutIdleFunc(idle);
			first = !first;
		}
		else
		{
			glutIdleFunc(0);
			first = !first;
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{	
	switch (key) {
	case VK_ESCAPE:exit(0); break;
	case 'a':window_x++; break;
	case 'd':window_x--; break;
	case 's':window_y++; break;
	case 'w':window_y--; break;
	case 'q':window_z++; break;
	case 'e':window_z--; break;

	case 'z':window_a++; break;
	case 'c':window_a--; break;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	
	glTranslatef(window_x, window_y, window_z);
	glRotatef(window_a, 1.0, 0.0, 0.0);
	
//	gluLookAt(20, 20, 20, 0, 0, 0, 1, 1, -1);	//指定照相机的位置	
	//绘制太阳
	glPushMatrix();
	glRotatef(rot0, 0.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, sun->texID);
	gltDrawSphere(2.0, 32, 32);
	glPopMatrix();

	//绘制地球
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	// 绘制辅助轨道
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.02, 5.0, 10, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	// 设置地球公转速度
	glRotatef(rot0, 0.0, 1.0, 0.0);
	// 设置地球半径
	glTranslatef(5.0, 0.0, 0.0);
	// 设置地球自转速度
	glRotatef(rot1, 0.0, 1.0, 0.0);
	// 绘制地球
	glBindTexture(GL_TEXTURE_2D, earth->texID);
	gltDrawSphere(0.4, 32, 32);
	// 绘制地球的卫星-月亮
	glColor3f(0.5, 0.6, 0.5);
	// 抵消地球自转影响
	glRotatef(-rot1, 0.0, 1.0, 0.0);

	// 绘制辅助轨道
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.02, 1.0, 10, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	// 设置月亮公转速度
	glRotatef(rot9, 0.0, 1.0, 0.0);
	// 设置月亮公转半径
	glTranslatef(1.0, 0.0, 0.0);
	// 绘制月亮
	glBindTexture(GL_TEXTURE_2D, moon->texID);
	gltDrawSphere(0.1, 10, 8);
	glPopMatrix();

	// 绘制水星
	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	// 绘制辅助轨道
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.02, 2.5, 10, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	// 设置水星公转速度
	glRotatef(rot1, 0.0, 1.0, 0.0);
	// 设置水星公转半径
	glTranslatef(2.5, 0.0, 0.0);
	// 设置水星自传
	glRotatef(rot3, 0.0, 1.0, 0.0);
	// 绘制水星
	glBindTexture(GL_TEXTURE_2D, mercury->texID);
	gltDrawSphere(0.2, 32, 32);
	glPopMatrix();

	//绘制金星
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	//绘制辅助轨道
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.02, 3.4, 10, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	// 设置金星公转速度
	glRotatef(rot2, 0.0, 3.0, 0.0);
	// 设置金星公转半径
	glTranslatef(3.4, 0.0, 0.0);
	// 设置金星自传
	glRotatef(rot0, 0.0, 1.0, 0.0);
	// 绘制金星
	glBindTexture(GL_TEXTURE_2D, venus->texID);
	gltDrawSphere(0.3, 32, 32);
	glPopMatrix();

	//绘制火星
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	//绘制辅助轨道
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.02, 6.6, 10, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	// 设置火星公转速度
	glRotatef(rot3, 0.0, 4.0, 0.0);
	// 设置火星公转半径
	glTranslatef(6.6, 0.0, 0.0);
	// 设置火星自传
	glRotatef(rot7, 0.0, 2.0, 0.0);
	// 绘制火星
	glBindTexture(GL_TEXTURE_2D, mars->texID);
	gltDrawSphere(0.5, 32, 32);
	glPopMatrix();


	//绘制木星
	glPushMatrix();
	glColor3f(2.0, 0.1, 1.0);
	//绘制辅助轨道
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.02, 8.5, 10, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	// 设置木星公转速度
	glRotatef(rot4, 0.0, 0.4, 0.0);
	// 设置木星公转半径
	glTranslatef(8.5, 0.0, 0.0);
	// 设置木星自传
	glRotatef(rot3, 0.0, 0.3, 0.0);
	// 绘制木星
	glBindTexture(GL_TEXTURE_2D, jupiter->texID);
	gltDrawSphere(1.0, 32, 32);

	glPushMatrix();
	// 绘制木星卫星
	glColor3f(0.4, 0.3, 0.5);
	// 抵消地球自转影响
	//glRotatef(-rot1,0.0,1.0,0.0);

	// 绘制辅助轨道-木卫1-木卫2
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.02, 1.3, 10, 64);
	glutSolidTorus(0.02, 1.8, 10, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	// 设置木卫1公转速度
	glRotatef(rot10, 0.0, 1.0, 0.0);
	// 设置木卫1公转半径
	glTranslatef(1.3, 0.0, 0.0);
	// 绘制木卫1
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, moon->texID);
	gltDrawSphere(0.1, 10, 8);

	glPopMatrix();
	// 设置木卫2公转速度
	glRotatef(rot11, 0.0, 1.0, 0.0);
	// 设置木卫2公转半径
	glTranslatef(1.8, 0.0, 0.0);
	// 绘制木卫2
	glBindTexture(GL_TEXTURE_2D, moon->texID);
	gltDrawSphere(0.08, 10, 8);
	glPopMatrix();



	//绘制土星
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	//绘制辅助轨道
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.02, 12.5, 10, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	// 设置土星公转速度
	glRotatef(rot5, 0.0, 0.4, 0.0);
	// 设置土星公转半径
	glTranslatef(12.5, 0.0, 0.0);
	// 设置土星自传
	glRotatef(rot3, 0.0, 0.3, 0.0);
	// 绘制土星
	glBindTexture(GL_TEXTURE_2D, saturn->texID);
	gltDrawSphere(0.85, 32, 32);

	//绘制土星光环
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(90, 1.0, 0, 0.0);
	gluDisk(quadric, 1.25, 1.5, 32, 32);
	glRotatef(-90, 1.0, 0, 0.0);
	glRotatef(90, 1.0, 0, 0.0);
	glColor3f(1.0, 1.0, 1.0);

	glPopMatrix();

	//绘制天王星
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 1.0f);
	//绘制辅助轨道
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.02, 15.5, 10, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	// 设置天王星公转速度
	glRotatef(rot6, 0.0, 0.4, 0.0);
	// 设置天王星公转半径
	glTranslatef(15.5, 0.0, 0.0);
	// 设置天王星自传
	glRotatef(rot1, 0.0, 0.3, 0.0);
	// 绘制天王星
	glBindTexture(GL_TEXTURE_2D, uranus->texID);
	gltDrawSphere(0.25, 32, 32);
	glPopMatrix();

	//绘制海王星
	glPushMatrix();
	glColor3f(0.0f, 0.0, 8.0f);
	//绘制辅助轨道
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.02, 17.5, 10, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	// 设置海王星公转速度
	glRotatef(rot7, 0.0, 0.4, 0.0);
	// 设置海王星公转半径
	glTranslatef(17.5, 0.0, 0.0);
	// 设置海王星自传
	glRotatef(rot3, 0.0, 0.3, 0.0);
	// 绘制海王星
	glBindTexture(GL_TEXTURE_2D, neptune->texID);
	gltDrawSphere(0.245, 32, 32);
	glPopMatrix();

	//绘制冥王星
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	//绘制辅助轨道
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.02, 19.5, 10, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	// 设置冥王星公转速度
	glRotatef(rot8, 0.0, 0.4, 0.0);
	// 设置冥王星公转半径
	glTranslatef(19.5, 0.0, 0.0);
	// 设置冥王星自传
	glRotatef(rot2, 0.0, 0.3, 0.0);
	// 绘制冥王星
	glBindTexture(GL_TEXTURE_2D, pluto->texID);
	gltDrawSphere(0.145, 32, 32);
	glPopMatrix();


	glutSwapBuffers();
	glFlush();

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);				//指定视口大小
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, (GLdouble)w / (GLdouble)h, 1.0, 100.0);		//透视投影

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

}

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("sol");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
