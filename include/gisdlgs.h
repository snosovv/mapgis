/**** GISDLGS.H *************** Belenkov O.V. ********* 06/06/07 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2007              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*      ����� ������� ��� ����� 2005 ��� ���������� �� GIS ToolKit  *
*                                                                  *
*                 �������������� ������� :                         *
*                                                                  *
*   // �������� ����������                                         *
*   HINSTANCE libInst = ::LoadLibrary("gisdlgs.dll");              *
*                                                                  *
*   // ����� �������                                               *
*   long int (WINAPI * tedInsertPoints)(HMAP hMap,                 *
*                                        TASKPARMEX* parm,         *
*                                        HOBJ info,                *
*                                        RECT * rect);             *
*   (FARPROC)tedInsertPoints =                                     *
*                   GetProcAddress(libInst, "tedInsertPoints");    *
*   long int Rezult = (*tedInsertPoints)(hMap, parm, info, 0);     *
*                                                                  *
*   // �������� ����������                                         *
*   ::FreeLibrary(libInst);                                        *
*                                                                  *
*******************************************************************/

#ifndef GISDLGS_H
#define GISDLGS_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

extern "C"
{

 // ������ "�������������� ������� �������"
 // hmap    - ������������� �������� �����
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // info    - ������������� �������������� �������
 // rect    - �������������� ������������ ������� ��� 0
 // ��� ������ ���������� ����

 long int WINAPI tedInsertPoints(HMAP hmap, TASKPARMEX *parm, HOBJ info, RECT *rect);

 // ������ "�������������� ��������� �������"
 // hmap    - ������������� �������� �����
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // info    - ������������� �������������� �������
 // ��� ������ ���������� ����

 long int WINAPI tedEditSemantic(HMAP hmap, TASKPARMEX *parm, HOBJ info);

 // ������ "������ ����������"
 // hmap    - ������������� �������� �����
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // ��� ������ ���������� ����

 long int WINAPI tedUndoOperation(HMAP hmap, TASKPARMEX *parm);

 // ������ "������� ����� ����"
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // name    - ��� ����� ������ ����, ������� ����������� ��� ���������
 // ��� ������ ���������� ����

 long int WINAPI tedOpenAtlas(TASKPARMEX *parm, char* name, long int size);

 // ������ "������� ����� �� ������"
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // item    - ��������� �� ������ ��������� ������, ��������� � ������� �����
 // count   - ����� ��������� � ������
 // ���������� ����� ���������� ������������� ��������
 // ��� ������ ���������� ����

 long int WINAPI tedAtlasList(TASKPARMEX *parm, ALSITEM* item, long int count);

 // ������ "������� � �������� ����� �� �����������"
 // hmap    - ������������� �������� �����
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // place   - ������ ������������ � ������� ���������:
 // PLANEPOINT      = 1,  � ������ �� ���������
 // MAPPOINT        = 2,  � �������� �������� ����� (���������)
 // PICTUREPOINT    = 3,  � �������� �������� ������� �����������
 //                       ��������� ����������� 1942�.
 // GEORAD          = 4,  � �������� � ������������ � ���������
 // GEOGRAD         = 5,  � �������� ...
 // GEOGRADMIN      = 6,  � ��������, �������, �������� ...
 //                       ���������� ��������� WGS84
 // GEORADWGS84     = 7,  � �������� � ������������ � ���������
 // GEOGRADWGS84    = 8,  � �������� ...
 // GEOGRADMINWGS84 = 9,  � ��������, �������, �������� ...
 // PLANE42POINT    = 10, � ������ �� ��������� �� ��������� ����
 // GEORADPZ90      = 11, � �������� � ������������ � ���������
 // GEOGRADPZ90     = 12, � �������� ...
 // GEOGRADMINPZ90  = 13, � ��������, �������, �������� ...
 // point  - ���������� ������� ����� � ������ �� �����
 // ��� �������� ���������� ���������� ���������� ��������� ����� � ������
 // �� �����
 // ��� ������ ���������� ����

 long int WINAPI tedGoPoint(HMAP hmap, TASKPARMEX *parm, long int place,
                            DOUBLEPOINT * point);

 // ������ "���������� � �������� ������ �� ��������"
 // ����� ���� ��������� ��, Mtw, Rsw, Mtl, Mtq, Tin
 // hmap    - ������������� �������� �����
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // title   - ��������� �� ����� ��������� ������� ��� 0
 // flagSit - ���� ������� ���������� ��  (0-���������/1-���������)
 // flagMtw - ���� ������� ���������� Mtw (0-���������/1-���������)
 // flagRsw - ���� ������� ���������� Rsw (0-���������/1-���������)
 // flagMtl - ���� ������� ���������� Mtl (0-���������/1-���������)
 // flagMtq - ���� ������� ���������� Mtq (0-���������/1-���������)
 // flagTin - ���� ������� ���������� Tin (0-���������/1-���������)
 // ��� ������ ���������� ����

 long int WINAPI tedAddDataFormDirEx(long int hmap, TASKPARMEX * parm, char * title,
                                     long int flagSit, long int flagMtw, long int flagRsw,
                                     long int flagMtl, long int flagMtq, long int flagTin);

} // extern "C"

#endif  // GISDLGS_H
