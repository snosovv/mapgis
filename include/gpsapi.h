/****** gpsapi.h *************** Belenkov  O.V. ******* 08/07/08 ***
******* gpsapi.h *************** Shabakov  D.A. ******* 19/02/07 ***
******* gpsapi.h *************** Dishlenko S.G. ******* 03/08/05 ***
******* gpsapi.h *************** Vitsko    D.A. ******* 12/04/06 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2008              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*             ������ ������ � GPS, ������ � COM-������ ��� USB     *
*                                                                  *
*******************************************************************/

#ifndef GPSAPI_H
#define GPSAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifdef LINUXAPI // 03/08/05
  // ���������� ����������
  #include <termios.h>
#endif

typedef long int HCOMPORT;

typedef struct TIMEDATA    // 05/09/06
{
  double Time;                // ����� UTC
  long int Day;               // ���� (01-31)
  long int Month;             // ����� (01-12)
  long int Year;              // ���
  long int ZoneForHours;      // ������� ����, �������� �� GMT (0+- 13 �����)
  long int ZoneForMinutes;    // ������� ����, �������� �� GMT (������)
  char Rez[20];               // ������
}
  TIMEDATA;

// ��������� ��������
typedef struct SATELLITEPARM  // 29/01/07
{
  char SatelliteNumber[4];    // PRN ����� ��������
  long int Height;            // ������, �������(90 - ��������)
  long int Azimuth;           // ������ ��������, �������(0-359)
  long int SignalNoise;       // ��������� ������/��� �� 0-99 ��, ����-��� �������
}
  SATELLITEPARM;


extern "C"
{

// ������� COM ��� USB ���� ��� ������ GPS - ��������� � ������� NMEA O183
// ��� Windows:
// portname - ��� COM-����� (��������, "COM1:" ��� ���� � USB-�����)
// baudrate - ������� ������ � ������ (��������, 9600 ��� 0)
// ��� Linux:
//   portname - ��� COM-����� (��������, "/dev/ttyS0"("COM1:" � Windows))
//   baudrate - ������� ������ � ������ (��������, B9600 ��� B4800)
// ��� ������ ���������� 0
_MAPIMP HCOMPORT _MAPAPI gpsOpen(LPTSTR portname, long int baudrate);

// ������� COM-����
_MAPIMP void _MAPAPI gpsClose(HCOMPORT hcomport);

// ������� COM-���� ��� ������/������
// portname - ��� COM-����� (��������, "COM1:")
// baudrate - ������� ������ � ������ (��������, 4800)
// ��� ������ ���������� 0
_MAPIMP HCOMPORT _MAPAPI gpsOpenComPort(LPTSTR portname, long int baudrate);
_MAPIMP HCOMPORT _MAPAPI gpsOpenComPortUn(const WCHAR * portname, long int baudrate);

// ������� COM-����
_MAPIMP void _MAPAPI gpsCloseComPort(HCOMPORT hcomport);

// ��������� - ���������� �� ���������� �����
// ��� ����� ������ �� �������, ��������, ������ �������
_MAPIMP long int _MAPAPI gpsIsUpdate(HCOMPORT hcomport);

// ��������� ���������� ������� ����� � �������� � ������� GPS (WGS-84)  // 19/02/07
// ������� ���������� ��������� ������������
_MAPIMP long int _MAPAPI gpsGetPoint(HCOMPORT hcomport, DOUBLEPOINT * point,
                                     double * height);

// ��������� ���������� ������� ����� � �������� � ������� GPS (WGS-84)
// ������� ���������� ��������� ������������
_MAPIMP long int _MAPAPI gpsGetSourcePoint(HCOMPORT hcomport, DOUBLEPOINT * point,
                                           double * height);

// ��������� ����� � ���� ����������� �������������� // 05/09/06
// timedata - ���������, ����������� ����������� ������� � ����
_MAPIMP long int _MAPAPI gpsCurrentTime(HCOMPORT hcomport, TIMEDATA * timedata);

// ��������� ����� ������������ ���������
_MAPIMP long int _MAPAPI gpsSatelliteCount(HCOMPORT hcomport);

//  ��������� ����� ������� ���������   // 04/02/05
_MAPIMP long int _MAPAPI gpsVisibleSatelliteCount(HCOMPORT hcomport);

// ��������� �������� ��� ������������, ��/�     // 30/08/06
_MAPIMP long int _MAPAPI gpsSpeed(HCOMPORT hcomport, double * speed);

// ��������� �������������� ������ PDOP // 25/01/07
// PDOP = 1   - ��������� ������������ ���������
// PDOP < 6.0 - �������� ��� ���������
_MAPIMP long int _MAPAPI gpsFactorPDOP(HCOMPORT hcomport, double * factor);

// ��������� �������������� �������������� ������ HDOP // 25/01/07
// PDOP = 1   - ��������� ������������ ���������
// PDOP < 4.0 - �������� ��� ���������
_MAPIMP long int _MAPAPI gpsFactorHDOP(HCOMPORT hcomport, double * factor);

// ��������� ������������ �������������� ������ HDOP // 25/01/07
// PDOP = 1   - ��������� ������������ ���������
// PDOP < 4.5 - �������� ��� ���������
_MAPIMP long int _MAPAPI gpsFactorVDOP(HCOMPORT hcomport, double * factor);

// ��������� ����� ���������������� ���������� // 29/01/07
// ����������: 1-�������������� �� ����������, 2 - 2D, 3 - 3D
// ��� ������ ���������� 0
_MAPIMP long int _MAPAPI gpsDeviceMode3D(HCOMPORT hcomport);

// ��������� ���������� ���������, ��� ������� �������� ��������� // 29/01/07
// (PRN ����� ��������; ������, �������; ������ ��������; ��������� ������/���)
// ��������� ����������� �������� gpsSatelliteParam()
// ��� ������ ���������� 0
_MAPIMP long int _MAPAPI gpsSatelliteParamCount(HCOMPORT hcomport);

// ��������� ��������� ��������� ��� ��������� // 29/01/07
// (PRN ����� ��������; ������, �������; ������ ��������; ��������� ������/���)
// parm  - ��������� �� ��������� SATELLITEPARM
// (����������� ���������� ��������� ��������� ����������� �������� gpsSatelliteParamCount() )
// count - ���������� ����������� ��������� ��������� SATELLITEPARM
// ��� ������ ���������� 0
_MAPIMP long int _MAPAPI gpsSatelliteParam(HCOMPORT hcomport, SATELLITEPARM* parm,  long int count);

// ��������� PRN ������ ���������, ������������ ��� ������� ������������� ������ // 30/01/07
// ��������� ��������� GPS - $GPGGA
// numbers - ��������� �� ������, � ������� ����� �������� PRN ������ ���������
// size    - ������ ������� (���������� ��������� �������)
// ������������� ��������� ������� ��� 12-�� ���������.
// ��� ������ ���������� 0
_MAPIMP long int _MAPAPI gpsSatelliteNumbers(HCOMPORT hcomport, long int * numbers, long int size);

// �������� ������������ ��������� �������� ������ // 06/02/05
_MAPIMP long int _MAPAPI gpsCreateFileProtocol(HCOMPORT hcomport, char *fileName, long int sizeFileName);

// ��������� �������� �������� ������ // 06/02/05
_MAPIMP long int _MAPAPI gpsCloseFileProtocol(HCOMPORT hcomport);

// ��������� �������� ������ ������
_MAPIMP long int _MAPAPI gpsQuality(HCOMPORT hcomport);

// ��������� ��� ��������� COM-�����
_MAPIMP LPTSTR _MAPAPI gpsPortName(HCOMPORT hcomport);
_MAPIMP long int _MAPAPI gpsPortNameUn(HCOMPORT hcomport, WCHAR * name, long int size);

// ��������� ������������� ��������� COM-�����
// ���� ���� ������ - ���������� ����
_MAPIMP HANDLE _MAPAPI gpsPortHandle(HCOMPORT hcomport);

// ��������� ������� ������ � ������
// ���� ���� ������ - ���������� ����
_MAPIMP long int _MAPAPI gpsBaudrate(HCOMPORT hcomport);

// ��������� ���������� ��������� ������ �� GPS
// buffer - ����� ������ ��� ���������� ����������
// size   - ������ ������
// ��� ������ ���������� ����
_MAPIMP long int _MAPAPI gpsGetRecord(HCOMPORT hcomport, char * buffer, long int size);
_MAPIMP long int _MAPAPI gpsGetRecordUn(HCOMPORT hcomport, WCHAR * buffer, long int size);

// �������� ������ � ���� (��������� GPS-���������� ��������������
// ����� ��������� �������)
// buffer - ����� ������ � ������������ �������
// size   - ������ ������������ ������
// ��� ������ ���������� ����
_MAPIMP long int _MAPAPI gpsPutRecord(HCOMPORT hcomport, char * buffer, long int size);

#ifdef WIN32API     // 03/08/05
// ��������� ��� ������ ��������� ��������
// ��� ���������� ������ ���������� ����
_MAPIMP long int _MAPAPI gpsGetLastError(HCOMPORT hcomport);


// ���������� ������� ��������� ������  // 15/02/05
// mask - �������(��������� ����������), ��������������� ���������� �������
// call - ����� ���������� ������� (��. maptype.h),
// parm - ��������, ������� ����� ������� ���������� �������.
// ��� ������ ���������� ����
_MAPIMP long int _MAPAPI gpsSetMask(HCOMPORT hcomport,
                            const char * mask, MASKCALL call, long int parm);
#endif

#ifdef WINCE
// ���������� ��� ���������� COM-����� ��� ����������� � GPS-���������
// �������� � ����� Windows Mobile 5.� � ����
// ��� ������ ���������� ����
_MAPIMP long int _MAPAPI gpsGetDefaultGPSPort(WCHAR * portname, long int size);
#endif

} // extern "C"

#endif  // MAPPORT_H
