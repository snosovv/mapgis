/******  XCONTEXT.H **********  Dishlenko S.G.  ***** 29/11/02 ****
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2001              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*                FOR      XWindow                                  *
*                                                                  *
********************************************************************
*                                                                  *
*            �������� ����� ����������                             *
*                                                                  *
*******************************************************************/

#ifndef XCONTEXT_H           // 29/11/02
#define XCONTEXT_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

typedef struct XCONTEXT  // ������ Windows HDC ��� XWindow
{
  Display * xcDisplay;   // ����� � X-��������
  Window    xcWindow;    // ������������� ����
  GC        xcContext;   // ����������� �������� ����
  DRAWPOINT xcPoint;     // ������������ ������������ ������� � ����
                         // (����� ������� ���� � ��������)
}
  XCONTEXT;

#define XHDC       XCONTEXT*

#endif  // XCONTEXT_H

