/**** GISGPS.H ***************** Shabakov D.A. ******** 02/02/06 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2006              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*                  FOR  WINDOWS95 & WINDOWS NT                     *
*                                                                  *
********************************************************************
*                                                                  *
*          ��������� ������ � GPS ��������� ����� COM-����         *
*                                                                  *
*******************************************************************/

//---------------------------------------------------------------------------
#ifndef GISGPS_H
#define GISGPS_H

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

extern "C"
{

  // ������� ������ ���������� �� ���������� ��������� � ��������� ������
  long int _export WINAPI GisDialogGpsTest(long int hmap,TASKPARMEX * parm);


  
//---------------------------------------------------------------------------
//      ������� ��� ����������� ������� � ����������� ������
//---------------------------------------------------------------------------

  // ������� ������ ���������� �� ���������� ���������
  long int WINAPI _export gisGpsOpenMonitor(HMAP hmap, TASKPARMEX *parm);

  // �������  ������ ���������� �� ���������� ���������
  long int WINAPI _export gisGpsCloseMonitor();

  // ��������� ������ �� ��������� ����� ���������
  long int WINAPI _export gisGpsChangeLanguage(long int code);

  // ��������� ������ �� ��������� ������� ������
  long int WINAPI _export gisGpsChangeData();

} // extern "C"

#endif
