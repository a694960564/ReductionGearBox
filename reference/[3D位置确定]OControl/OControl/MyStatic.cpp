#include "stdafx.h"
#include "MyStatic.h"
#include <GL\glu.h>

CMyStatic::CMyStatic()
{
}


CMyStatic::~CMyStatic()
{
}
BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CMyStatic::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//GLDraw();   //定时器中调用这个函数
	GLSHOWSTL();
	CStatic::OnTimer(nIDEvent);
}


void CMyStatic::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	InitGL();
	GLREADSTL();
	CStatic::PreSubclassWindow();
}


// OpenGL绘制
void CMyStatic::GLDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(-0.0f, 0.0f, -10.0f);

	static int RotateDegTriangle = 1;
	glRotatef(RotateDegTriangle++, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);

	glEnd();
#ifdef TWO_OBJS 
	glLoadIdentity();
	glTranslatef(5.0f, 0.0f, -15.0f);

	RotateDegQuad += 3.0f;
	glRotatef(RotateDegQuad, 1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glEnd();
#endif 
	SwapBuffers(hdc); //利用双缓冲
}


// OpenGl初始化
bool CMyStatic::InitGL()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24 ,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32 ,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};


	int pixelformat;
	hdc = ::GetDC(this->GetSafeHwnd());
	if (!(pixelformat = ChoosePixelFormat(hdc, &pfd)))
	{
		MessageBox("ChoosePixelFormat failed!");
		return false;
	}


	if (!SetPixelFormat(hdc, pixelformat, &pfd))
	{
		MessageBox("SetPixelFormat failed!");
		return false;
	}


	if (!(hglrc = wglCreateContext(hdc)))
	{
		MessageBox("CreateContext failed!");
		return false;
	}


	if (!wglMakeCurrent(hdc, hglrc))
	{
		MessageBox("MakeCurrent failed!");
		return false;
	}


	CRect rect; //在这个矩形中画图
	GetClientRect(rect);


	//glViewport(0, 0, rect.Width()/2, rect.Height()/2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*gluPerspective(45.0f , rect.Width()/rect.Height() , 0.1f , 100.0f);// 计算窗口的外观比例*/
	gluPerspective(45, 1.3/ 1, 0.1f, 1000.0f);// 计算窗口的外观比例
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);


	SetTimer(1, 50, NULL);
	return true;
}

//求数组最大值最小值
float max_value(float arr[], int size)
{
	float max = arr[0];
	for (int i = 1; i<size; i++)
		if (max < arr[i]) max = arr[i];
	return max;
}

float min_value(float arr[], int size)
{
	float min = arr[0];
	for (int i = 1; i<size; i++)
		if (min > arr[i]) min = arr[i];
	return min;
}

// 读取STL
void CMyStatic::GLREADSTL()
{
	int max = 0;
	bool isbegin = false;
	long size = 0;
	int nlines = 0;
	int count1 = 0;
	int count2 = 0;
	FILE* file = fopen("2.stl", "r");
	fseek(file, 0L, SEEK_END);
	size = ftell(file);
	fclose(file);
	file = fopen("2.stl", "r");
	for (int i = 0; i < size; i++)
	{
		if (getc(file) == '\n')
		{
			nlines++;
		}
	}
	num = nlines / 7;
	rewind(file);
	while (getc(file) != '\n');
	verts = new float[9 * num];
	vnorms = new float[9 * num];
	for (int i = 0; i < num; i++)
	{
		char x[200] = "";
		char y[200] = "";
		char z[200] = "";
		if (3 != fscanf(file, "%*s %*s %80s %80s %80s\n", x, y, z))
		{
			break;
		}
		vnorms[count1] = vnorms[count1 + 3] = vnorms[count1 + 6] = atof(x);
		count1++;
		vnorms[count1] = vnorms[count1 + 3] = vnorms[count1 + 6] = atof(y);
		count1++;
		vnorms[count1] = vnorms[count1 + 3] = vnorms[count1 + 6] = atof(z);
		count1 += 7;
		fscanf(file, "%*s %*s");
		if (3 != fscanf(file, "%*s %80s %80s %80s\n", x, y, z))
		{
			break;
		}
		if (isbegin == false)
		{
			isbegin = true;
			max = atof(z);
		}
		verts[count2] = atof(x);
		count2++;
		verts[count2] = atof(y);
		count2++;
		verts[count2] = atof(z);
		count2++;
		if (3 != fscanf(file, "%*s %80s %80s %80s\n", x, y, z))
		{
			break;
		}
		verts[count2] = atof(x);
		count2++;
		verts[count2] = atof(y);
		count2++;
		verts[count2] = atof(z);
		count2++;
		if (3 != fscanf(file, "%*s %80s %80s %80s\n", x, y, z))
		{
			break;
		}
		verts[count2] = atof(x);
		count2++;
		verts[count2] = atof(y);
		count2++;
		verts[count2] = atof(z);
		count2++;
		fscanf(file, "%*s");
		fscanf(file, "%*s");
	}

	//求数组最大值最小值
	float max1 = verts[0];
	float min1 = verts[0];
	for (int i = 0; i < 9 * num; i = i + 3)
	{
		if (max1 < verts[i]) max1 = verts[i];
		if (min1 > verts[i]) min1 = verts[i];
	}
	m_fmaxmin[0] = max1;
	m_fmaxmin[1] = min1;

	max1 = verts[1];
	min1 = verts[1];
	for (int i = 1; i < 9 * num; i = i + 3)
	{
		if (max1 < verts[i]) max1 = verts[i];
		if (min1 > verts[i]) min1 = verts[i];
	}
	m_fmaxmin[2] = max1;
	m_fmaxmin[3] = min1;

	max1 = verts[2];
	min1 = verts[2];
	for (int i = 2; i < 9 * num; i = i + 3)
	{
		if (max1 < verts[i]) max1 = verts[i];
		if (min1 > verts[i]) min1 = verts[i];
	}
	m_fmaxmin[4] = max1;
	m_fmaxmin[5] = min1;
}


// 显示STL
void CMyStatic::GLSHOWSTL()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	glPushMatrix();
	glTranslatef(-0.0f, 0.0f, -200.0f);
	glRotatef(180,1,0,0);
	static int RotateDegTriangle = 1;
	glRotatef((RotateDegTriangle++)*20, 0, 1, 0.0f);
	int m_div = 1;
	for (int i = 0; i < 9 * num; i++)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(24/255.0f, 174/255.0f, 136/255.0f);
		glNormal3f(vnorms[i] / m_div, vnorms[i + 1] / m_div, vnorms[i + 2] / m_div);
		glVertex3f((-verts[i]) / m_div + (m_fmaxmin[0]+ m_fmaxmin[1])/2, (-verts[i + 1]) / m_div + (m_fmaxmin[2] + m_fmaxmin[3]) / 2, (-verts[i + 2]) / m_div + (m_fmaxmin[4] + m_fmaxmin[5]) / 2);
		i += 3;
		glColor3f(24 / 255.0f, 174 / 255.0f, 136 / 255.0f);
		glNormal3f(vnorms[i] / m_div, vnorms[i + 1] / m_div, vnorms[i + 2] / m_div);
		glVertex3f((-verts[i]) / m_div + (m_fmaxmin[0] + m_fmaxmin[1]) / 2, (-verts[i + 1]) / m_div + (m_fmaxmin[2] + m_fmaxmin[3]) / 2, (-verts[i + 2]) / m_div + (m_fmaxmin[4] + m_fmaxmin[5]) / 2);
		i += 3;
		glColor3f(24 / 255.0f, 174 / 255.0f, 136 / 255.0f);
		glNormal3f(vnorms[i] / m_div, vnorms[i + 1] / m_div, vnorms[i + 2] / m_div);
		glVertex3f((-verts[i]) / m_div + (m_fmaxmin[0] + m_fmaxmin[1]) / 2, (-verts[i + 1]) / m_div + (m_fmaxmin[2] + m_fmaxmin[3]) / 2, (-verts[i + 2]) / m_div + (m_fmaxmin[4] + m_fmaxmin[5]) / 2);
		i += 2;
		glEnd();
	}
	glPopMatrix();
	
	SwapBuffers(hdc); //利用双缓冲
}

