/****** NETAPI.H ************* Tarakanova I.R.  ******* 25/06/07 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2007              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*           �������� ������� ������� � ���� ��������               *
*        ��������� ��� �������� �� ������ C, PASCAL, BASIC         *
*                                                                  *
********************************************************************
*                                                                  *
*    �������������� ������� � Windows :                            *
*                                                                  *
*    // �������� ����������                                        *
*    HINSTANCE libInst = ::LoadLibrary("objnet.dll");              *
*                                                                  *
*    // ����� �������                                              *
*    HSITE (WINAPI * lpfn_CrtObjNet)(HMAP hmap,                    *
*                                    TASKPARMEX * parm);           *
*    (FARPROC)lpfn_CrtObjNet = GetProcAddress(libInst,             *
*                                             "onCreateNetDlg");   *
*    HSITE sit =(*lpfn_CrtObjNet)(hmap,parm);                      *
*    ...                                                           *
*                                                                  *
*    long int (WINAPI * lpfn_SeekPathD)(HMAP hmap, HSITE site,     *
*                                       TASKPARMEX * parm,         *
*                                    HOBJ infobegin,HOBJ infoend); *
*    (FARPROC)lpfn_SeekPathD = GetProcAddress(libInst,             *
*                                             "onSeekPathDlg");    *
*    long int ret =(*lpfn_SeekPathD)(hmap,sit,parm,info1,info2);   *
*                                                                  *
*    ...                                                           *
*    // �������� ����������                                        *
*    ::FreeLibrary(libInst);                                       *
*                                                                  *
*******************************************************************/

#ifndef NETAPI_H
#define NETAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

// ���� �������� ��� ���������� ������ ����� ��������� ����:
#define SEMNETRIB       32812  // ����� �������-����� (��� ����)
#define SEMNETKNOTFIRST 32813  // ����� �������-���� ������ ����� (��� �����)
#define SEMNETKNOTLAST  32814  // ����� �������-���� ��������� ����� (��� �����)
#define SEMNETNUMBER    32815  // ����� ����
#define SEMNETTOOBJECT  32816  // ������ �� ������ �����
#define SEMNETVDIRECT   32817  // �������� ������ (��� �����)
#define SEMNETVUNDIRECT 32818  // �������� �������� (��� �����)
#define SEMNETCOSTRIB   32819  // ��������� �����
#define SEMNETRANKRIB   32820  // ���� �����


#ifdef __cplusplus
extern "C"
{
#endif

// -----------------------------------------------------------------------------
// ���������� �������������� ���� ��������
// hmap - ������������� �������� ��������� �����
// parm - �������� ���������� ������ (��.maptype.h)
// �� ����� �������������� ������ ���� �������� ������������ ����������
// (����. �������� mapSetSiteSeekSelect(...)) ������� ��� ���������� ����
// (����. �������� ����)
// � ������� ���������� ������ "���������� ����", � ������� ��������:
// ��� ��������� �����, ������������� (service.rsc),��� ��������
// �������������  service.rsc �������� �������: ���� ����, ����� ���� �
// ������������ ���������, ����������� ��� ������ � �����  (SEMNETRIB ...)
// �� ������� ���������� ��� ���������� ��������� �������� ���������� ������
// "��������� ���������� ��� ���������� ����", ������� �������������� ��
// ��������������� ������
//   ������ ������������ ��� ���������� ��������� ����� � ������������ �����
//   ������� � ���������� � ������ ���������� ��������, �� ������� �������� ����
//   ��������� ����� �������� ����������� ������������� ��������� ����������
//   ��������  �������� ����� ������� �� ������ �������� ������������� ���������
//   �������  ��� ������ � ����������
// ��� �������� ���������� ���������� ������������� ���������������� �����
// � ����������� �����
// ��� ������ ���������� 0
// -----------------------------------------------------------------------------
HSITE _export WINAPI onCreateNetDlg(HMAP hmap, TASKPARMEX * parm);


// -----------------------------------------------------------------------------
// ���������� �������������� ���� ��������
// hmap - ������������� �������� ��������� �����
// parm - �������� ���������� ������ (��.maptype.h)
// namesit - ��� ��������� �����
// namersc - ������������� (������ ��������� �������: ���� ����, ����� ���� �
// ������������ ��������� (SEMNETRIB, SEMNETKNOTFIRST ...) )
// flag - ���������� ��������  "���������� ����" (0- �� �������� ������, 1 - ��������)

HSITE _export WINAPI onCreateNetDlgEx(HMAP hmap, TASKPARMEX * parm,
                                     char * namesit, char * namersc, int flag);


// -----------------------------------------------------------------------------
// ����������� ����������� ���������� ����� ����� ������ ����
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����, �.�. �� ����� ������ ����
// ������� ���� ���� � ������������� �����������: ����� ���� � ������ �� �����
// ����, � ����� � �����������: ����� ������� � ���������� ����� ��� �������
// �����, ������ �� ������ ����� � ����� ����
// pointbegin - ��������� ���� (������������� ������� ����� � ������)
// pointend - �������� ���� (������������� ������� ����� � ������)
// � ������� ���������� ������ "��������� ���������� ������������ ����", � �������
// ��������������� ����� ���������� (����� ��� �����,� ��������� ������ �����
// ������ ����� ��������� "��������") � ������ �� ���������� �����
// �� ��������� ������ ������� �������� �������������� ������ "������ ��������",
// � ������� ������������ �������� ������� ����� � ������������� ���� �� ������� �������
// �� ���������������� ����e ����� �������� �����,������� ���������� ����������� �������
// ����� ���������� �������� ������������ �������� mapTotalSeekObjectCount(seekapi.h)
// �������� ������������� ����������� ������� ����� ��������� ������� mapTotalSeekObject(seekapi.h)
// ����������: ����� ������� (mapObjectKey), ���� ������ ������� ����������
//            - 1, ���� ������ ������� �� ����������
//              0, ��� ������
// -----------------------------------------------------------------------------
long int _export WINAPI onSeekPathDlg(HMAP hmap, HSITE site, TASKPARMEX * parm,
                                      HOBJ infobegin,HOBJ infoend);


// -----------------------------------------------------------------------------
// ����������� ����������� ���������� ����� ����� ������ ���� ��� ������ ��������
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����, �.�. �� ����� ������ ����
// ������� ���� ���� � ������������� �����������: ����� ���� � ������ �� �����
// ����, � ����� � �����������: ����� ������� � ���������� ����� ��� �������
// �����, ������ �� ������ ����� � ����� ����
// pointbegin - ��������� ����(������������� ������� ����� � ������)
// pointend - �������� ����(������������� ������� ����� � ������)
// methodseek - ����� ���������� (0 - �����, 1- �����)
// speed - ������� �������� (��/�)(���� methodseek = 1 � �������� ���������
// "��������" �� �����������)
// �� ���������������� ����e ����� �������� �����,������� ���������� ����������� �������
// ����� ���������� �������� ������������ �������� mapTotalSeekObjectCount(seekapi.h)
// �������� ������������� ����������� ������� ����� ��������� ������� mapTotalSeekObject(seekapi.h)
// ����������: ����� ������� (mapObjectKey), ���� ������ ������� ����������
//            - 1, ���� ������ ������� �� ����������
//              0, ��� ������
// -----------------------------------------------------------------------------
long int _export WINAPI onSeekPath(HMAP hmap, HSITE site, TASKPARMEX * parm,
                                   HOBJ infobegin,HOBJ infoend,
                                   long int methodseek, double speed);


// -----------------------------------------------------------------------------
// ����������� ����������� ���������� ����� ����� ������ ���� ��� ������ ��������
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����, �.�. �� ����� ������ ����
// ������� ���� ���� � ������������� �����������: ����� ���� � ������ �� �����
// ����, � ����� � �����������: ����� ������� � ���������� ����� ��� �������
// �����, ������ �� ������ ����� � ����� ����
// object - ������������� ������� � ������,
//        �������������� ���������� �������� mapCreateObject()
//        ��� mapCreateSiteObject(),
//        � ������� ����� �������� ��������� - ����������� ����.
// pointbegin - ��������� ����(������������� ������� ����� � ������)
// pointend - �������� ����(������������� ������� ����� � ������)
// methodseek - ����� ���������� (0 - �����, 1- �����)
// speed - ������� �������� (��/�)(���� methodseek = 1 � �������� ���������
// "��������" �� �����������)
// ����������: -1, ���� ���� ������
//              0, ��� ������
// -----------------------------------------------------------------------------
long int _export WINAPI onSeekPathCreateObject(HMAP hmap, HSITE site,
                                               TASKPARMEX * parm,HOBJ object,
                                               HOBJ infobegin,HOBJ infoend,
                                               long int methodseek, double speed);

// -----------------------------------------------------------------------------
// ���������� � ���� �����, ������������� �� ���������� ����� ��������� ��
// ���������� ���� (���������� ����� �����������)
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����, �.�. �� ����� ������ ����
// ������� ���� ���� � ������������� �����������: ����� ���� � ������ �� �����
// ����, � ����� � �����������: ����� ������� � ���������� ����� ��� �������
// �����, ������ �� ������ ����� � ����� ����
// info -  ���� ���� (������������� ������� ����� � ������)
// distance - ���������� � ������
// �� ���������������� ����� ����� �������� �����, �������������  �� ����������,
// ����� distance �� info
// ����� ���������� �������� ������������ �������� mapTotalSeekObjectCount(seekapi.h)
// �������� ������������� ������� ����� ��������� ������� mapTotalSeekObject(seekapi.h)
// ��� ������ ���������� 0
// -----------------------------------------------------------------------------
long int _export WINAPI onDistFromKnot(HMAP hmap, HSITE site, TASKPARMEX * parm,
                                       HOBJ info, double distance);

// -----------------------------------------------------------------------------
// �������� ��������� ���� ���� � ��������� �����
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����
// info - ������������� ������� ����� � ������
// point - ���������� ����� � ������  � ������� �����
// ������ �������������:
//  - ������� ������
//    HOBJ hobj = mapCreateSiteObject(hmap,site,IDDOUBLE2,0);
//  - ������� ��������� ���� � ����� point � ���������� � hobj
//    long int ret = onGetNodeByPoint(hmap,site,hobj, point);
//  - �������� ������� ������ � �����
//    if (ret)
//        onDistFromKnot(hmap,site,parm,hobj,20);
// ��� ������ ���������� 0
// -----------------------------------------------------------------------------
long int _export WINAPI onGetNodeByPoint(HMAP hmap, HSITE site,
                                         HOBJ info,
                                         DOUBLEPOINT * point);
// -----------------------------------------------------------------------------
// ���������� ������������ ���� ����� ������� (������ ����)
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����
// parm - �������� ���������� ������ (��.maptype.h)
// array - ����� ������� ��������� ������� �����,
//         ������ ������� ����� count
// count - ���������� ����� ��� ���������� ������������ ����
// ������� ������������ �� ��������� � ������ ����� ����
// � ������� ���������� ������ "��������� ���������� ������������ ����", � �������
// ��������������� ����� ���������� (����� ��� �����,� ��������� ������ �����
// ������ ����� ��������� "��������") � ������ �� ���������� �����
// �� ��������� ������ ������� �������� �������������� ������ "������� ������ �����",
// � ������� ������������ ������ ����� � ��� �������, � ������� ���� ����������� �� ��� ���������,
// ������������� �������� ����� �������� ����� �����, ����� ����� ����.  
// ��� ������ ���������� 0
// -----------------------------------------------------------------------------
long int _export WINAPI onMinimalPath(HMAP hmap, HSITE site, TASKPARMEX * parm,
                                      DOUBLEPOINT * arraypoint,long int count);
#ifdef __cplusplus
}       // extern "C"
#endif

#endif  // NETAPI_H
