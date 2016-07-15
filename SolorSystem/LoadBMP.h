#define BITMAP_ID 0x4D42
#define PI 3.1415926

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl\glut.h>

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

//---------- �������ݽṹ
typedef struct {
	int width;				//������
	int height;				//����߶�
	unsigned int texID;		//������� ID
	unsigned char * data;	//ʵ����������
}texture;


static float year = 0, month = 0, day = 0, angle = 30;
static bool first = false;

texture * sun, *earth, *moon, *mercury, *venus, *mars, *jupiter, *saturn, *uranus, *neptune, *pluto;//����ָ��

										//---------- ����λͼ��Ϊ��������
unsigned char * LoadBmpFile(char * filename, BITMAPINFOHEADER * bmpInfoHeader) {

	FILE * file;
	BITMAPFILEHEADER bmpFileHeader;
	unsigned char * image;
	unsigned int imageIdx = 0;
	unsigned char tempRGB;

	fopen_s(&file,filename, "rb");

	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, file);			// ��ȡ BMP �ļ�ͷ

	fread(bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, file);			// ��λͼ��Ϣͷ
	fseek(file, bmpFileHeader.bfOffBits, SEEK_SET);					// ���ļ�ָ���Ƶ�λͼ���ݵĿ�ʼ��
	image = (unsigned char *)malloc(bmpInfoHeader->biSizeImage);	// �����ڴ��λͼ����

	fread(image, 1, bmpInfoHeader->biSizeImage, file);					// ��ȡλͼ����

	// ��ת R �� B ֵ�Եõ� RGB����Ϊλͼ��ɫ��ʽ�� BGR
	for (imageIdx = 0; imageIdx < bmpInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = image[imageIdx];
		image[imageIdx] = image[imageIdx + 2];
		image[imageIdx + 2] = tempRGB;
	}

	fclose(file);
	return image;

}

//---------- ���������ļ�
texture * LoadTexFile(char * filename) {

	BITMAPINFOHEADER texInfo;
	texture * thisTexture;

	thisTexture = (texture *)malloc(sizeof(texture));

	thisTexture->data = LoadBmpFile(filename, &texInfo);	// �����������ݲ������Ч��

	thisTexture->width = texInfo.biWidth;				// ��������Ŀ�͸�
	thisTexture->height = texInfo.biHeight;

	glGenTextures(1, &thisTexture->texID);				// �������������

	return thisTexture;
}

//---------- ��ʼ�������������ݺ�����
BOOL LoadAllTextures() {

	sun = LoadTexFile("image\\sun.bmp");
	if (sun == NULL)
		return FALSE;

	glBindTexture(GL_TEXTURE_2D, sun->texID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, sun->width, sun->height, GL_RGB, GL_UNSIGNED_BYTE, sun->data);


	earth = LoadTexFile("image//earth.bmp");
	if (earth == NULL)
		return FALSE;

	glBindTexture(GL_TEXTURE_2D, earth->texID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, earth->width, earth->height, GL_RGB, GL_UNSIGNED_BYTE, earth->data);


	moon = LoadTexFile("image//moon.bmp");
	if (moon == NULL)
		return FALSE;

	glBindTexture(GL_TEXTURE_2D, moon->texID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, moon->width, moon->height, GL_RGB, GL_UNSIGNED_BYTE, moon->data);

	mercury = LoadTexFile("image//mercury.bmp");
	if (mercury == NULL)
		return FALSE;

	glBindTexture(GL_TEXTURE_2D, mercury->texID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, mercury->width, mercury->height, GL_RGB, GL_UNSIGNED_BYTE, mercury->data);

	venus = LoadTexFile("image//venus.bmp");
	if (venus == NULL)
		return FALSE;

	glBindTexture(GL_TEXTURE_2D, venus->texID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, venus->width, venus->height, GL_RGB, GL_UNSIGNED_BYTE, venus->data);

	mars = LoadTexFile("image//mars.bmp");
	if (mars == NULL)
		return FALSE;

	glBindTexture(GL_TEXTURE_2D, mars->texID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, mars->width, mars->height, GL_RGB, GL_UNSIGNED_BYTE, mars->data);

	jupiter = LoadTexFile("image//jupiter.bmp");
	if (jupiter == NULL)
		return FALSE;

	glBindTexture(GL_TEXTURE_2D, jupiter->texID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, jupiter->width, jupiter->height, GL_RGB, GL_UNSIGNED_BYTE, jupiter->data);

	saturn = LoadTexFile("image//saturn.bmp");
	if (saturn == NULL)
		return FALSE;

	glBindTexture(GL_TEXTURE_2D, saturn->texID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, saturn->width, saturn->height, GL_RGB, GL_UNSIGNED_BYTE, saturn->data);

	uranus = LoadTexFile("image//uranus.bmp");
	if (uranus == NULL)
		return FALSE;

	glBindTexture(GL_TEXTURE_2D, uranus->texID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, uranus->width, uranus->height, GL_RGB, GL_UNSIGNED_BYTE, uranus->data);

	neptune = LoadTexFile("image//neptune.bmp");
	if (neptune == NULL)
		return FALSE;

	glBindTexture(GL_TEXTURE_2D, neptune->texID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, neptune->width, neptune->height, GL_RGB, GL_UNSIGNED_BYTE, neptune->data);

	pluto = LoadTexFile("image//pluto.bmp");
	if (pluto == NULL)
		return FALSE;

	glBindTexture(GL_TEXTURE_2D, pluto->texID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, pluto->width, pluto->height, GL_RGB, GL_UNSIGNED_BYTE, pluto->data);

	return TRUE;
}

void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)
{
	GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat)iStacks;
	GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat)iSlices;
	GLfloat ds = 1.0f / (GLfloat)iSlices;
	GLfloat dt = 1.0f / (GLfloat)iStacks;
	GLfloat t = 1.0f;
	GLfloat s = 0.0f;
	GLint i, j;

	for (i = 0; i < iStacks; i++)
	{
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));


		glBegin(GL_TRIANGLE_STRIP);
		s = 0.0f;
		for (j = 0; j <= iSlices; j++)
		{
			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));

			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;

			glTexCoord2f(s, t);
			glNormal3f(x, y, z);
			glVertex3f(x * fRadius, y * fRadius, z * fRadius);

			x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;
			glTexCoord2f(s, t - dt);
			s += ds;
			glNormal3f(x, y, z);
			glVertex3f(x * fRadius, y * fRadius, z * fRadius);
		}
		glEnd();

		t -= dt;
	}
}

void drawCircle(GLfloat r)
{
	int j = 0;
	glBegin(GL_POINTS);
	for (j = 0; j<100; j++)
	{
		GLfloat theta = j * 2 * PI / 100;
		glVertex3f(r*cos(theta), 0.0f, r*sin(theta));
	}
	glEnd();
}