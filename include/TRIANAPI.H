/******  TRIANAPI.H  **********  Demidenko A.G. ******  01/09/2000 *
*******  TRIANAPI.H  **********  Shishkova L.A. ******  12/05/2003 *
*******  TRIANAPI.H  **********  Tarakanova I.R.******  27/06/2005 *
*******  TRIANAPI.H  **********  Gorbunov A.V.  ******  16/01/2006 *
*                                                                  *
********************************************************************
*                                                                  *
*                  FOR  WINDOWS95 & WINDOWS NT                     *
*                                                                  *
********************************************************************
*                                                                  *
*            ������� ���������� (GIS\GSS)DELONE.DLL                *
*                                                                  *
*******************************************************************/

#include "mapsyst.h"
#include "maptype.h"
#include "tritype.h"   //12/05/03

#ifndef TRIANAPI_H
#define TRIANAPI_H

extern "C"
{

// ������� ��������� ���������� ������������ ������ �� ������� �����.
// ������� ���������: points - ��������� �� ������ �����, ��� ����������
// ������������, � ������� �� ������ ���� ������������� �����;
// count- ���������� ����� �� ������� �������;
// frame - ��������� �� ������, ��������� �������������� ������ ����� 
// ������������, ��� �������� ������������ � ��������� �������
// ����� ������� ������ CreateDeloneTtiangle ������ ���� �����
// DeleteDeloneTtiangle
// ����� ����� ����� (����� � �������� �������) ������ ���� ������ ����,
// ����� ����������� ���������� ����� ������������ (�������� �������������)
// ���������� ��������� �� ����������� ������������

// ������ ������� �������� ������������
// �� ��������� ����������� �������� �����
HTRIANG _export
CreateDeloneTriangle(HWND parent,
                    XYDOUBLE* points,
                    unsigned long count,
                    HOBJ frame=0);

// �������� ������� ������������ � ��������������� ����������� �����
HTRIANG _export
CreateDeloneTriangleSort(HWND parent,
                    XYDOUBLE* Points,
                    unsigned long count,
                    HOBJ frame=0);

// ������ ������� �������� ������������.
// �� ���������� ����������� �������� �����
HTRIANG   _export
CreateDeloneTriangleXYH(HWND parent,
                     XYHDOUBLE* points,
                     unsigned long count,
                     HOBJ frame=0);

// �������� ������� ������������ � ������ ����� �����
// � � ��������������� ����������� �����
HTRIANG   _export
CreateDeloneTriangleXYHSort(HWND parent,
                     XYHDOUBLE* Points,
                     unsigned long count,
                     HOBJ frame=0);

// ���������� ������������ (������� ������������� � ������� ����)
// �� ������� ���������� �����
// parent - ������������� ���� �������, �������� ����������
// ��������� � ���� �������� :
//   0x3000 - ��������� � �������� ����������� ����� (� WPARAM),
//   ���� ������� ������ ���� ������������� ��������, � �����
//   ������ ��������� �������� 0x3000.
// ���� parent = 0 - ��������� �� ����������.
// points - ������ �������� ����� (��������� VERTEX ������� � tritype.h)
// count - ���������� ����� � �������� �������
// indexEdge - ���� ���������� ���������� ���� �����������
// ������������ (0 - �� ���������, 1 - ���������).
// ���� indexEdge = 0, �� ���������� ������������ �����������
// �������, �� ������ ���� �� �������� ������ �� ������������ - ����
// LTri,RTri ��������� EDGE (��������� EDGE ������� � tritype.h)
// frame - ������������� ���������� ������� �����, ���������������
// ������������. ���������� ��������� �� ����������� ������������
// (HTRIANG ������ � tritype.h)
// � ������ ������ ���������� 0
HTRIANG   _export
BuildDeloneTriangulation(HWND parent,
                         VERTEX* points,
                         unsigned long count,
                         long int indexEdge = 1,
                         HOBJ frame = 0);


// ���������� ������������ (������� ����)
// �� ������� ���������� �����
// parent - ������������� ���� �������, �������� ����������
// ��������� � ���� �������� :
//   0x3000 - ��������� � �������� ����������� ����� (� WPARAM),
//   ���� ������� ������ ���� ������������� ��������, � �����
//   ������ ��������� �������� 0x3000.
// ���� parent = 0 - ��������� �� ����������.
// points - ������ �������� ����� (��������� VERTEX ������� � tritype.h)
// count - ���������� ����� � �������� �������
// frame - ������������� ���������� ������� �����, ���������������
// ������������. ���������� ��������� �� ����������� ������������
// (HTRIANG ������ � tritype.h)
// � ������ ������ ���������� 0

HTRIANG   _export
BuildDeloneEdges(HWND parent,
                 VERTEX* points,
                 unsigned long count,
                 HOBJ frame = 0);


// �������� ������� ������������
// HTRIANG htriangle - ��������� �� ����������� ������������
long int  _export
DeleteDeloneTriangle(HTRIANG htriangle);

// �������� ����� ������������, �������� �����������  �����
// HTRIANG htriangle - ��������� �� ����������� ������������
// XYDOUBLE point - ���������� �����
// ��������� ������������� ���������� � 0.
// � ������ ������ ���������� -1.
long int  _export
GetNumberTriangle(HTRIANG htriangle, XYDOUBLE point);

// �������� ����� ������������, �������� �����������  �����
// HTRIANG htriangle - ��������� �� ����������� ������������
//   (������������ ������ ���� ��������� �������� BuildDeloneTriangulation)
// XYDOUBLE point - ���������� �����
// ��������� ������������� ���������� � 0.
// � ������ ������ ���������� -1.
long int  _export
GetNumberTriangleAdd(HTRIANG htriangle, XYDOUBLE point);  // 23/12/05

// �������� ���������� � ������������ �� ��� ������ � �������
// HTRIANG htriangle - ��������� �� ����������� ������������
// TRIANGLE triangle - ���������� � ������������ � ������� number
// long int number - ����� ������������ � ������� ������������
// ��������� ������������� ���������� � 0.
// � ������ ������ ���������� 0.
long int  _export
GetTriangle(HTRIANG htriangle, TRIANGLE* triangle, long int number);

// �������� ���������� � ����� AB,BC,CA ������������ numTriangle
// HTRIANG htriangle - ��������� �� ����������� ������������
// edge - ���������� � ����� AB,BC,CA ������������ numTriangle
// (��������� EDGE ������� � tritype.h)
// � ������ ������ ���������� 0.
long int  _export
GetTriangleEdgeAB(HTRIANG htriangle, EDGE* edge, long int numTriangle);

long int  _export
GetTriangleEdgeBC(HTRIANG htriangle, EDGE* edge, long int numTriangle);

long int  _export
GetTriangleEdgeCA(HTRIANG htriangle, EDGE* edge, long int numTriangle);

// �������� ���������� � ����� �� ��� ������ � �������
// HTRIANG htriangle - ��������� �� ����������� ������������
// EDGE edge - ���������� � ����� � ������� number
// long int number - ����� ������������ � ������� ������������
// ��������� ����� ���������� � 0.
// � ������ ������ ���������� 0.
long int  _export
GetEdge(HTRIANG htriangle, EDGE* edge, long int number);


// �������� ���������� � ������� ������������ �� �� ������ � �������
// HTRIANG htriangle - ��������� �� ����������� ������������
// XYDOUBLE vertex - ���������� � ������� ������������ � ������� number
// long int number - ����� ������� ������������ � ������� �������� �����
// ��������� ������ ������������� ���������� � 0.
// � ������ ������ ���������� 0.
long int  _export
GetVertex(HTRIANG htriangle, XYDOUBLE* vertex, long int number);

// �������� ���������� � ������� ������������ �� �� ������ � �������
// htriangle - ��������� �� ����������� ������������
// vertex - ���������� � ������� ������������ � ������� number
// (��������� VERTEX ������� � tritype.h)
// number - ����� ������� ������������ � ������� �������� �����
// ��������� ������ ������������� ���������� � 0.
// � ������ ������ ���������� 0.
long int  _export
GetVertexXYH(HTRIANG htriangle, VERTEX* vertex, long int number);

// �������� ���������� � �������������� ������� ������������ (�������
// ����������) �� �� ������ � ������� �������� �����
// HTRIANG htriangle - ��������� �� ����������� ������������
// double heigth - �������� �������������� ������� ������������ � ������� number
// long int number - ����� ������� ������������ � ������� �������� �����
// ��������� ������ ������������� ���������� � 0.
// � ������ ������ ���������� 0.
long int  _export
GetHeigth(HTRIANG htriangle, double* heigth, long int number);

// �������� ���������� � �������������� ������� ������������ (�������
// ����������) �� �� ������ � ������� �������� �����
// HTRIANG htriangle - ��������� �� ����������� ������������
//   (������������ ������ ���� ��������� �������� BuildDeloneTriangulation)
// double heigth - �������� �������������� ������� ������������ � ������� number
// long int number - ����� ������� ������������ � ������� �������� �����
// ��������� ������ ������������� ���������� � 0.
// � ������ ������ ���������� 0.
long int  _export
GetHeigthAdd(HTRIANG htriangle, double* heigth, long int number);

// �������� ����� �������������.
// HTRIANG htriangle - ��������� �� ����������� ������������
// ���������� ����� ������������� � ������� ������������
// � ������ ������ ���������� 0.
long int  _export
GetQuantTriangle(HTRIANG htriangle);

// �������� ����� ������.
// HTRIANG htriangle - ��������� �� ����������� ������������
// ���������� ����� ������ � ������� ������������
// � ������ ������ ���������� 0.
long int  _export
GetQuantVertex(HTRIANG htriangle); 

// �������� ����� �����.
// HTRIANG htriangle - ��������� �� ����������� ������������
// ���������� ����� ����� � ������� ������������
// � ������ ������ ���������� 0.
long int  _export
GetQuantEdges(HTRIANG htriangle);

// ��������� �������� ������������
// HTRIANG htriangle - ��������� �� ����������� ������������
// � ������ ������ ���������� 0.
long int  _export
ThickenTriangle(HTRIANG htriangle);

// ��������� ���������� ������������
// HTRIANG htriangle - ��������� �� ����������� ������������
// � ������ ������ ���������� 0.
long int  _export
FacrtorizationTriangle(HTRIANG htriangle);

// �������� �������� ���������� �����
// ���������� ���������� ����������� �����
long int GetControlTriangle(HTRIANG htriangle, int* control);


// ���������� � ������������ ����������� ����� (����� ��������)
// HTRIANG htriangle - ��������� �� ����������� ������������  27/06/05
// � ������ ������ ���������� 0.
long int  _export
 AddBreakLinesInTriangle(HTRIANG htriangle,HOBJ info);

// ����������� ������������ � ������ ����������� �����    27/06/05
// HTRIANG htriangle - ��������� �� ����������� ������������
// � ������ ������ ���������� 0.
long int  _export
 RebuildTriangle(HTRIANG htriangle,HOBJ info);

// �������� � ������ �������� ����� ����� ����������� �������� �������
// ����������� ����� info � ������ ����� ����������� ������������ htriangle
long int  _export
 AddPointsByLine(HTRIANG htriangle, HOBJ info);

// ��������� ���� "����������� �����" ����� ������������ htriangle,
// ������� �� �������� ����������� ����� info
long int  _export
 MarkEdgesByLine(HTRIANG htriangle, HOBJ info);

} // extern "C"
#endif




