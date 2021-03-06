/*
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2004              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
*                 �������� ����������� �����                       *
*                                                                  *
*******************************************************************/

// ��������� �������� MAPREGISTER � LISTREGISTER �� ����������� !

#if !defined(MAPCREAT_H)
#define MAPCREAT_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ������� ����� ����������� �����  +++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  // ���� ����� "�������� ��������� ���������"
  typedef enum MAPPROJECTION
  {
// UNDEFINED          = -1, // �� �����������
   GAUSSCONFORMAL      = 1, // ������������� ������-�������
   CONICALORTHOMORPHIC = 2, // ���������� �������������
   CYLINDRICALSPECIAL  = 3, // �������������� �����������
   LAMBERT             = 4, // ������������ ���������� ��������
   STEREOGRAPHIC       = 5, // �����������������
   POSTEL              = 6, // (����������) ������������������
                            // ������������ �������� �������
   AZIMUTHALOBLIQUE    = 7, // ������������ ������������������ �����
   MERCATORMAP         = 8, // �������������� ������ ������������� ���������
   URMAEV              = 9, // �������������� ������������(����.�������)
   POLYCONICAL         =10, // �������������� �������� ��������
   SIMPLEPOLYCONICAL   =11, // ������� �������������� ��������������
   PSEUDOCONICAL       =12, // ���������������� ������������
   STEREOGRAPHICPOLAR  =13, // ����������������� ��������
   CHEBISHEV           =14, // ������������� ��������
   GNOMONIC            =15, // �������������
   CYLINDRICALSPECIALBLANK =16, // �������������� �����������
                                // ��� ��������� �����
   UTM                 =17,  // UTM
                             // 28/06/01 --------------------------------
   KAVRAJSKY           =18,  // �������������������� ������������
                             // �������������� �������� �����������
   MOLLWEIDE           =19,  // �������������������� ������������
                             // ������������� �������� ���������
   CONICALEQUIDISTANT  =20,  // (������) ������������������ ���������� ��������
   CONICALEQUALAREA    =21,  // (������) ������������ ���������� ��������
   CONICALDIRECTORTHOMORPHIC   =22, // (������) ������������� ���������� ��������
   AZIMUTHALORTHOMORPHICPOLAR  =23, // �������� ������������� ������������
                                    // (�����������������) ��������
   LAMBERTAZIMUTHALEQUALAREA   =24, // (����������) ������������
                                    // ������������ �������� ��������
   URMAEVSINUSOIDAL            =25, // �������������������� ��������������
                                    // �������� ������� ��� ����
                                    // �������(������ � ����������)
   AITOFF                      =26, // ����������� ������������
                                    // �������� ������-������
   CYLINDRICALEQUALSPACED      =27, // ������������������ �������������� ��������
   LAMBERTCYLINDRICALEQUALAREA =28, // ������������ ��������������
                                    // �������� ��������
   MODIFIEDPOLYCONICAL         =29, // �������������� ������� ��������������
                                    // �������� (�������������)
   LAMBERTOBLIQUEAZIMUTHAL     =30, // ����� ������������ ������������
                                    // �������� ��������
   TRANSVERSECYLINDRICAL       =31, // ������������� ���������-��������������
                                    // ��������       //28/01/03
   GAUSSCONFORMAL_SYSTEM_63    =32  // ������� ��������� 63 ����  //22/08/03
  }
    MAPPROJECTION;

  // ���� ����� "��� ����������"
  typedef enum ELLIPSOIDKIND
  {
   UNDEFINED   = -1,       // �� �����������
   KRASOVSKY42 =  1,       // ����������� 1942�.
   WGS_76      =  2,       // ������������� 1976�.
   HEFORD      =  3,       // �������� 1909�.
   CLARKE_80   =  4,       // ������ 1880�.
   CLARKE_66   =  5,       // ������ 1866�.
   EVEREST_57  =  6,       // �������� 1857�.
   BESSEL      =  7,       // ������� 1841�.
   AIRY        =  8,       // ��� 1830�.
   WGS_84      =  9        // ������������� 1984�.
  }
   ELLIPSOIDKIND;

  // ���� ����� "������� �����"
  typedef enum HEIGHTSYSTEM
  {
// UNDEFINED   = -1,       // �� �����������
   BALTIC      =  1,       // ���������� ������� �����
   LAMANSH     =  6,       // ������� ������� ���� � ������� ������
   NORMALNULL  = 16,       // ������� ������� C�������� ���
   MARSEL      = 22,       // ������� ������� ������������ ���� � �������
   USAKANADA   = 24,       // ������� ������� ����� � �������,��������� ��� � ������
   BALTIC77    = 25,       // ���������� ������� 1977 �.
   OKHOTSK     = 26,       // ������� ������� ��������� ���� � ������ ������
   PEACEOCEAN  = 27        // ������� ������� �������� ������
  }
   HEIGHTSYSTEM;

  // ���� ����� "������� ���������"
  typedef enum COORDINATESYSTEM
  {
// UNDEFINED          = -1, // �� �����������
   ORTHOGONAL          = 1, // ������� ��������� 42 ����
   UNIVERSALMERCATOR   = 2, // ������� �������� ���������
   NATIONALGRID        = 3, // ������������ ������������� ����� ��������������
   AREAORTHOGONAL      = 4, // ������������� ������� ������� ���������
   SYSTEM_63           = 5, // ������� ��������� 63 ����
   CONDITION           = 6, // ������������� �������� ��� �������� ����
   GEOCOORDINATE       = 7, // ������������� ���������� � ��������
   GEOCOORDINATEGRADUS = 8  // ������������� ���������� � ��������
  }
   COORDINATESYSTEM;

  // ���� ����� "��� �����"
  typedef enum MAPTYPE
  {
// UNDEFINED   = -1,      // �� �����������
   TOPOGRAPHIC  = 1,      // ���������������
   GEOGRAPHIC   = 2,      // �������-��������������
   GLOBE        = 3,      // ������������������ (������)
   CITYPLAN     = 4,      // ��������������� ���� ������
   LARGESCALE   = 5,      // ���������������� ���� ���������
   AERONAUTIC   = 6,      // �����������������
   SEANAUTIC    = 7,      // ������� �������������
   AVIATION     = 8,      // �����������
   BLANK        = 9,      // ���������
   UTMNAD27     = 10,     // UTM �� North American Datum 1927
//18/09/02
   UTMWGS84     = 11,
   UTMTYPE      = 12,      // UTM   04/11/02
   CK_63         = 13       // ������� ��������� 63 ����  // 09/09/03
  }
   MAPTYPE;

  // ���� ����� "��� �����"
  typedef enum FRAMEKIND
  {
// UNDEFINED    = -1,     // �� �����������
   TRAPEZE      = 1,      // �������������� ��� ����� ������
   TRAPEZECURVE = 2,      // �������������� � ������� ������
   RECTANGULAR  = 3,      // �������������
   CIRCLE       = 4       // ��������
  }
   FRAMEKIND;

typedef struct COORDINATES
{
  double Coord[4];
}
  COORDINATES;

// ����� ��������� � ������� ���������
enum COUNTSCALE
{
  COUNTTOPO      = 9,        // ���������������     02/10/02
  COUNTGEOG      = 5,        // �������-��������������
  COUNTAERO      = 2,        // �����������������
  COUNTCITYPLAN  = 3,        // ��������������� ���� ������     // 14/06/06
  COUNTLARGE     = 5,        // ���������������� ����
  COUNTSCALENONE = 16        // ��� ���� �� ����������          // 14/06/06
};

// ���� ��������� ��� �������-�������������� ����
enum GEOGRAPHICCODE     // 02/10/09
{
// UNDEFINED    = -1,     // �� �����������
  EUROPE           = 1,    // ���� ������
  ASIA             = 2,    // ���� ����
  PACIFICOCEAN     = 3,    // ����� �����
  AMERICANORTH     = 4,    // �������� �������
  ATLANTICOCEAN    = 5,    // ������������� �����
  NORTHPOLARSYSTEM = 6,    // �������� �������� ����������
  SOUTHPOLARSYSTEM = 7,    // ����� �������� ����������
  EQUATORIALSYSTEM = 8     // �������������� ����������
};

#ifdef __cplusplus

typedef struct REGISTERTYPES
{
  // ���� ����� ������������ ��������
  enum PROJECTION
  {
	  NOADEQUACY = 0,   // ������ �� ������������� ��������
   ADEQUACY   = 1    // ������ ������������� ��������
  };

  // ���� ����� "�������� ��������� ���������"
  enum MAPPROJECTION
  {
// UNDEFINED          = -1, // �� �����������
   GAUSSCONFORMAL      = 1, // ������������� ������-�������
   CONICALORTHOMORPHIC = 2, // ���������� �������������
   CYLINDRICALSPECIAL  = 3, // �������������� �����������
   LAMBERT             = 4, // ������������ ���������� ��������
   STEREOGRAPHIC       = 5, // �����������������
   POSTEL              = 6, // (����������) ������������������
                            // ������������ �������� �������
   AZIMUTHALOBLIQUE    = 7, // ������������ ������������������ �����
   MERCATORMAP         = 8, // �������������� ������ ������������� ���������
   URMAEV              = 9, // �������������� ������������(����.�������)
   POLYCONICAL         =10, // �������������� �������� ��������
   SIMPLEPOLYCONICAL   =11, // ������� �������������� ��������������
   PSEUDOCONICAL       =12, // ���������������� ������������
   STEREOGRAPHICPOLAR  =13, // ����������������� ��������
   CHEBISHEV           =14, // ������������� ��������
   GNOMONIC            =15, // �������������
   CYLINDRICALSPECIALBLANK =16, // �������������� �����������
                                // ��� ��������� �����
   UTM                 =17,     // UTM
                             // 28/06/01 --------------------------------
   KAVRAJSKY           =18,  // �������������������� ������������
                             // �������������� �������� �����������
   MOLLWEIDE           =19,  // �������������������� ������������
                             // ������������� �������� ���������
   CONICALEQUIDISTANT  =20,  // (������) ������������������ ���������� ��������
   CONICALEQUALAREA    =21,  // (������) ������������ ���������� ��������
   CONICALDIRECTORTHOMORPHIC   =22, // (������) ������������� ���������� ��������
   AZIMUTHALORTHOMORPHICPOLAR  =23, // �������� ������������� ������������
                                    // (�����������������) ��������
   LAMBERTAZIMUTHALEQUALAREA   =24, // (����������) ������������
                                    // ������������ �������� ��������
   URMAEVSINUSOIDAL            =25, // �������������������� ��������������
                                    // �������� ������� ��� ����
                                    // �������(������ � ����������)
   AITOFF                      =26, // ����������� ������������
                                    // �������� ������-������
   CYLINDRICALEQUALSPACED      =27, // ������������������ �������������� ��������
   LAMBERTCYLINDRICALEQUALAREA =28, // ������������ ��������������
                                    // �������� ��������
   MODIFIEDPOLYCONICAL         =29, // �������������� ������� ��������������
                                    // �������� (�������������)
   LAMBERTOBLIQUEAZIMUTHAL     =30, // ����� ������������ ������������
                                    // �������� ��������
   TRANSVERSECYLINDRICAL       =31, // ������������� ���������-��������������   //04/09/03
                                    // ��������       //28/01/03
   GAUSSCONFORMAL_SYSTEM_63    =32  // ������� ��������� 63 ����  //22/08/03
  };

  // ���� ����� "��� ����������"
  enum ELLIPSOIDKIND
  {
   UNDEFINED   = -1,       // �� �����������
   KRASOVSKY42 =  1,       // ����������� 1942�.
   WGS_76      =  2,       // ������������� 1976�.
   HEFORD      =  3,       // �������� 1909�.
   CLARKE_80   =  4,       // ������ 1880�.
   CLARKE_66   =  5,       // ������ 1866�.
   EVEREST_57  =  6,       // �������� 1857�.
   BESSEL      =  7,       // ������� 1841�.
   AIRY        =  8,       // ��� 1830�.
   WGS_84      =  9        // ������������� 1984�.
  };


  // ���� ����� "������� �����"
  enum HEIGHTSYSTEM
  {
// UNDEFINED   = -1,       // �� �����������
   BALTIC      =  1,       // ���������� ������� �����
   LAMANSH     =  6,       // ������� ������� ���� � ������� ������
   NORMALNULL  = 16,       // ������� ������� C�������� ���
   MARSEL      = 22,       // ������� ������� ������������ ���� � �������
   USAKANADA   = 24,       // ������� ������� ����� � �������,��������� ��� � ������
   BALTIC77    = 25,       // ���������� ������� 1977 �.
   OKHOTSK     = 26,       // ������� ������� ��������� ���� � ������ ������
   PEACEOCEAN  = 27        // ������� ������� �������� ������
  };

  // ���� ����� "������� ���������"
  enum COORDINATESYSTEM
  {
// UNDEFINED          = -1, // �� �����������
   ORTHOGONAL          = 1, // ������� ��������� 42 ����
   UNIVERSALMERCATOR   = 2, // ������� �������� ���������
   NATIONALGRID        = 3, // ������������ ������������� ����� ��������������
   AREAORTHOGONAL      = 4, // ������������� ������� ������� ���������
   SYSTEM_63           = 5, // ������� ��������� 63 ����
   CONDITION           = 6, // ������������� �������� ��� �������� ����
   GEOCOORDINATE       = 7, // ������������� ���������� � ��������
   GEOCOORDINATEGRADUS = 8  // ������������� ���������� � ��������
  };

  // ���� ����� "������� ���������"
  enum UNIT
  {
// UNDEFINED     = -1,   // �� �����������
   KILOMETRE     = 5,    // ���������
   METRE05       = 4,    // 0.5 �
   METRE         = 0,    // �����
   DECIMETRE     = 1,    // ���������
   CENTIMETRE    = 2,    // ����������
   MILLIMETRE    = 3,    // ����������
   SECOND01      = 66,   // 0.1 ���
   RADIAN        = 64,   // �������
   RADIAN8       = 67,   // 10e-8 ���
   DEGREE        = 65,   // �������
   FOOT          = 16    // ����
  };


  // ���� ����� "��� �����"
  enum FRAMEKIND
  {
// UNDEFINED    = -1,     // �� �����������
   TRAPEZE      = 1,      // �������������� ��� ����� ������
   TRAPEZECURVE = 2,      // �������������� � ������� ������
   RECTANGULAR  = 3,      // �������������
   CIRCLE       = 4       // ��������
  };

  // ���� ����� "��� �����"
  enum MAPTYPE
  {
// UNDEFINED   = -1,      // �� �����������
   TOPOGRAPHIC  = 1,      // ���������������
   GEOGRAPHIC   = 2,      // �������-��������������
   GLOBE        = 3,      // ������������������ (������)
   CITYPLAN     = 4,      // ��������������� ���� ������
   LARGESCALE   = 5,      // ���������������� ���� ���������
   AERONAUTIC   = 6,      // �����������������
   SEANAUTIC    = 7,      // ������� �������������
   AVIATION     = 8,      // �����������
   BLANK        = 9,      // ���������
   UTMNAD27     = 10,     // UTM �� North American Datum 1927  //18/09/02
//18/09/02
   UTMWGS84     = 11,
   UTMTYPE      = 12,      // UTM  04/11/02
   CK_63        = 13       // ������� ��������� 63 ����  // 09/09/03
  };

  // ���� ��������� ���������
  // ��� ��������� ����������
  enum MAPINITKIND
  {
    MAP     = 1,           // ����������������
    PHOTO   = 2,           // ��������
    IMAGE   = 3,           // ����������
    GRAM    = 4            // �������������������
  };

  // ��� ��������� ����/�������������
  enum MAPINITTYPE
  {
   MAPRUN     = 1,        // �������� ������
   FINAL      = 2,        // ������������ ��������
   MANUSCRIPT = 3,        // ��������������� ��������
   UPDATE     = 4,        // �������� ���������
   SPECIAL    = 5,        // ����������� ��������
   CONSTANT   = 6,        // ���������� ����������� ��������
  };

  // ��� ��������� �������������
  enum PHOTOINITKIND
  {
   FGM        = 7,        // ������������������� ��������
   FGMMAPRUN  = 8,        // ��� � �������� ������
   FGMMANUSCRIPT = 9,     // ��� � ��������������� ��������
   FGMFINAL      = 10,    // ��� � ������������ ��������
   FGMCONSTANT   = 11,    // ��� � ���������� ����������� ��������
   FGMSPECIAL    = 12,    // ��� � ����������� ��������
   SPACE         = 64,    // �����������
   AERO          = 65,    // ����������
   PHOTOGRAM     = 66     // ��������������� ������
  };


  // ���� ��������� ��� ������������� �������� ������-�������
  enum SCALEGAUSS
  {
   FGKSCALEMLN = 1,
   FGKSCALE500 = 2,
   FGKSCALE200 = 3,
   FGKSCALE100 = 4,
   FGKSCALE50  = 5,
   FGKSCALE25  = 6,
   FGKSCALE10  = 7,
   FGKSCALE5   = 8,
   FGKSCALE2   = 9
  };

  // ���� ��������� ��� �������-�������������� ����
  enum SCALEGEOG
  {
   FGEOSCALE10MLN = 1,
   FGEOSCALE5MLN  = 2,
   FGEOSCALE2MLN  = 3,
   FGEOSCALEMLN   = 4,
   FGEOSCALE500   = 5
  };

  // ���� ��������� ����������������� ����
  enum SCALEAERO
  {
   FARSCALE4MLN = 1,
   FARSCALE2MLN = 2
  };

  // ���� ��������� ��� ���� ��������������� ���� ������
  enum SCALECITYPLAN
  {
   FCPSCALE25 = 1,
   FCPSCALE10 = 2
  };

  // ���������� ����� ��� ������ ������������
  enum TABLEVALUETYPE
  {
   COUNTMAPTYPE = 14,             // ��� �����   //16/09/03
   COUNTUNIT    = 12,             // ������� ���������
   COUNTUNITHEIGHT = 8,           // ������� ��������� �� ������
   COUNTELL     = 10,             // ��� ����������
   COUNTHEIGHT  =  9,             // ������� �����
   COUNTCOORD   =  8,             // ������� ���������
   COUNTPROJ    = 33,             // ��������    // 14/07/03 //16/09/03
   COUNTMAPINITKIND = 5,          // ��� ��������� ���������
   COUNTMAPINITTYPE = 7,          // ��� ���
   COUNTPHOTO   = 10,             // ��� �������
   COUNTFRAME   = 5,              // ��� �����
   COUNTGEOGRAPHICCODE = 9        // ���� ��� �������-�������������� ����
  };

}
  REGISTERTYPES;

#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ��������� �������� ����������� �����  ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct CONSTPROJ
{
  double FirstMainParal    ; // ������ ������� ���������
  double SecondMainParal   ; // ������ ������� ���������
  double AxisMeridian      ; // ������ ��������
  double MainPointParallel ; // ��������� ������� �����
  double PoleLatitude      ; // ������ ������ ��������
  double PoleLongitude     ; // ������� ������ ��������
}
  CONSTPROJ;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  �������� ����� ����������� �����  ++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct LISTREGISTER
{
long        Length                 ;  // ������ ������ ���������

char        Nomenclature[32]       ;  // ������������ �����
char        ListName[32]           ;  // �������� �����

char        FileName[260]          ;  // ��� ����� �� �������� � ������ �����
                                      // ������ ���� � ������ ������
                                      // � ������������ HDR, DAT, SEM, DRW

// ������������� ���������� ����� � ������
double      XSouthWest             ;  // X �-�
double      YSouthWest             ;  // Y �-�
double      XNorthWest             ;  // X �-�
double      YNorthWest             ;  // Y �-�
double      XNorthEast             ;  // X �-�
double      YNorthEast             ;  // Y �-�
double      XSouthEast             ;  // X �-�
double      YSouthEast             ;  // Y �-�

// ������������� ���������� ����� � ��������
double      BSouthWestCoordinate   ;  // B �-�
double      LSouthWestCoordinate   ;  // L �-�
double      BNorthWestCoordinate   ;  // B �-�
double      LNorthWestCoordinate   ;  // L �-�
double      BNorthEastCoordinate   ;  // B �-�
double      LNorthEastCoordinate   ;  // L �-�
double      BSouthEastCoordinate   ;  // B �-�
double      LSouthEastCoordinate   ;  // L �-�

long        MaterialKind           ;  // ��� ��������� ���������
long        MaterialType           ;  // ��� ���
long        ReliefHeight           ;  // ������ ������� ������� � ����������
char        Date[12]               ;  // ���� ������ "��������"

double      MagneticAngle          ;  // ��������� ���������
double      YearMagneticAngle      ;  // ������� ��������� ���������
double      MeridianAngle          ;  // ������� ��������� ����������
char        DateAngle[12]          ;  // ���� ��������� "��������"

long        Reserv2[3]             ;  // = 0

DOUBLEPOINT BorderSW               ;  // ��������� ���� (������ 0 !)
}
  LISTREGISTER;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++ "�������� ������ �����" ++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct MAPREGISTER
{
long        Length                 ; // ������ ������ ���������

char        Name[32]               ; // ��� ������
long        Scale                  ; // ����������� ��������
long        ProjectionFlag         ; // ���� ������������ ��������
long        EllipsoideKind         ; // ��� ����������
long        HeightSystem           ; // ������� �����
long        MaterialProjection     ; // �������� ���. ���������
long        CoordinateSystem       ; // ������� ���������
long        PlaneUnit              ; // ������� ��������� � �����
long        HeightUnit             ; // ������� ��������� �� ������
long        FrameKind              ; // ��� �����
long        MapType                ; // ���������� ��� �����
long        DeviceCapability       ; // ����������� ����������� �������
long        DataProjection         ; // ������� ������ � ��������
long        OrderViewSheetFlag     ; // ������� ����������� ������
long        FlagRealPlace          ; // ������� �������� ���������
long        ZoneNumber             ; // ����������� �������� ��� �������
                                     // ��������� - ����� ���� ���������

                                     // � ��������
double      FirstMainParallel      ; // ������ ������� ���������
double      SecondMainParallel     ; // ������ ������� ���������
double      AxisMeridian           ; // ������ ��������
double      MainPointParallel      ; // ��������� ������� �����
}
  MAPREGISTER;


typedef struct MAPREGISTEREX
{
long        Length                 ; // ������ ������ ���������

char        Name[32]               ; // ��� ������
long        Scale                  ; // ����������� ��������
long        ProjectionFlag         ; // ���� ������������ ��������
long        EllipsoideKind         ; // ��� ����������
long        HeightSystem           ; // ������� �����
long        MaterialProjection     ; // �������� ���. ���������
long        CoordinateSystem       ; // ������� ���������
long        PlaneUnit              ; // ������� ��������� � �����
long        HeightUnit             ; // ������� ��������� �� ������
long        FrameKind              ; // ��� �����
long        MapType                ; // ���������� ��� �����
long        DeviceCapability       ; // ����������� ����������� �������
                                     // ������ ����� 20 000
                                     // ��� ���� ���������� ��������:  // 26/12/06
                                     // -1 - ������������ ��������
                                     // -2 - ������� ���������� � �����������
                                     // -3 - ������� ���������� � �����������
long        DataProjection         ; // ������� ������ � ��������
long        OrderViewSheetFlag     ; // ������� ����������� ������
long        FlagRealPlace          ; // ������� �������� ���������
long        ZoneNumber             ; // ����������� �������� ��� �������
                                     // ��������� - ����� ���� ���������

                                     // � ��������
double      FirstMainParallel      ; // ������ ������� ���������
double      SecondMainParallel     ; // ������ ������� ���������
double      AxisMeridian           ; // ������ ��������
double      MainPointParallel      ; // ��������� ������� �����
double      PoleLatitude           ; // ������ ������ ��������
double      PoleLongitude          ; // ������� ������ ��������
double      Reserv2[8]             ; // ������ = 0

}
  MAPREGISTEREX;

#endif

