/****** PICEXPRM.H ************* Shabakov D.A.   ****** 01/11/05 ***
*                                                                  *
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2004              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*                  FOR  WINDOWS95 & WINDOWS NT                     *
*                                                                  *
********************************************************************
*                                                                  *
*      �������� ��������� ���������� ��������������� ������        *
*                                                                  *
*******************************************************************/

#ifndef PICEXPRM_H
#define PICEXPRM_H

#include "maptype.h"

#define WM_PCX2RST               0x590       // ���������  PCX � RST
#define WM_PCX2RST_PROGRESS      0x591
#define WM_PCX2RST_ERROR         0x592

#define WM_RSTCOMPRESS           0x593       // ������ ������
#define WM_RSTCOMPRESS_ERROR     0x594

// ��������� ��� �������� ���������� � ����������� ������ ������� �� ����������
typedef struct DATAINFORMATION
       {
       unsigned long int InputFileLength ;  // ����� ����� ������������ �����������
       long int Width           ;  // ������ �����������
       long int Height          ;  // ������ �����������
       long int BitPerPixel     ;  // ���-�� ��� �� ������
       double   Precision       ;  // ����������� ����������� ����������� (�\�)
       char PaletteType[4]      ;  // ���������� ����. ������      // 25/10/04

       long int BlockCount      ;  // ���-�� ������ � ������
       double   RswFileLength   ;  // ������������� ����� ����� *.rsw
       char CompressImage[16]   ;  // ������ �����������  // 26/01/01
       }
          DATAINFORMATION;


// ��������� ��� �������� ���������� � GeoTIFF-������
typedef struct GEOTIFFINFORMATION   // 20/03/03
       {
        unsigned long int StructSize;  // ����� ���������
        unsigned long int TypeCS;      // ��� ������������ �������

        unsigned long int Spheroid;    // Geographic CS
        unsigned long int Datum;       // Geographic CS
        unsigned long int PrimeMeridian;//Geographic CS

        unsigned long int Projection;  //
        unsigned long int Zone;        //

        unsigned long int Units;       // ������� ��������� (�����, ������� ...)


        DFRAME FrameImage;             // �������� ����������� � ������
        double UnitsInElement_X;       // ������ �������� � �������� ��������� �� ��� X
        double UnitsInElement_Y;       // ������ �������� � �������� ��������� �� ��� Y
        double UnitsInElement_Z;       // ������ �������� � �������� ��������� �� ��� Z
        char Information[256]  ;       // ���������� � ��������, ����� ��������� � �.�.
        double PrecisionInch;          // ����������� ����������� ����������� (�\�) // 01/11/05
        double PrecisionMet;           // ����������� ����������� ����������� (�\�) // 01/11/05
        char Reserv[248];
       }
          GEOTIFFINFORMATION;

 // ��������� ��� �������� ��������� �� ������� ������� �� ����������
typedef struct ERRORINFORMATION
       {
       char * MessageR    ;  // ��������� �� ������ �� ������� �����
       char * MessageE    ;  // ��������� �� ������ �� ���������� �����
       }
           ERRORINFORMATION;

// ��� ��������� (0 - INTEL, 1 - MOTOROLA)    // 09/07/03
#define INTEL    0
#define MOTOROLA 1

// ��������� ����������� TIFF (0 - BLOCK, 1- STRIP, 2 - NONFRAG)
#define BLOCK    0
#define STRIP    1
#define NONFRAG  2


#endif  //PICEXPRM_H
