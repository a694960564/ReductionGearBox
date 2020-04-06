#pragma once
#include "afxwin.h"
class CMyStatic :
	public CStatic
{
public:
	CMyStatic();
	~CMyStatic();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void PreSubclassWindow();
	// OpenGL绘制
	void GLDraw();
	// OpenGl初始化
	bool InitGL();
	HGLRC hglrc;
	HDC hdc;
	// 读取STL
	void GLREADSTL();
	// 显示STL
	void GLSHOWSTL();
	int num;
	float* verts;
	float* vnorms;
	//数组最大值最小值
	float m_fmaxmin[6];
};

