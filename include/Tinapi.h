/****** TINAPI.H *************** Gorbunov A.V. ******** 10/01/06 ***
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
*                          TIN-������                              *
*                                                                  *
*  ��������� ��������                      (TINBUILD)              *
*  �������� �������� TIN-������            (TINDESCRIBE)           *
*  ��������� ������ ������� ������         (TINVERTEX)             *
*  ��������� ������ ������� �������������  (TINTRIANGLE)           *
*  �������� ������� ������� � TIN-������                           *
*                                                                  *
********************************************************************
*                                                                  *
*    �������������� ������� � Windows :                            *
*                                                                  *
*    // �������� ����������                                        *
*    HINSTANCE libInst = ::LoadLibrary("gisacces.dll");            *
*                                                                  *
*    // ����� �������                                              *
*    HMAP (WINAPI * lpfn_OpenTin)(const char*, long int);          *
*    (FARPROC)lpfn_OpenTin = GetProcAddress(libInst, "OpenTin");   *
*    HMAP hMap = (*lpfn_OpenTin)("Noginsk.tin",0);                 *
*                                                                  *
*    // �������� ����������                                        *
*    ::FreeLibrary(libInst);                                       *
*                                                                  *
*******************************************************************/

#ifndef TINAPI_H
#define TINAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

//------------------------------------------------------------------
//  ��������� �������� TIN-������
//------------------------------------------------------------------
typedef struct TINBUILD     // ������ ��������� 320 ����
{
  long int  Length;         // ������ ������ ���������: sizeof(TINBUILD)

  long int  UserLabel;      // ���������������� ������������� -
                            // ������������ �����, �����������
                            // � ����������� �������

  long int  ModelType;      // ��� ������
                            //  ��������: 1 - ������ ������� ���������
                            //            2 - ������ ������

  long int  Method;         // ����� ���������� ������
                            //  ��������: 1 - � ��������������
                            //                ������������ ������

  DFRAME    FrameMeters;    // �������� ������ � ����� (�����)

  MAPREGISTEREX
      ModelRegister;  // ���������� ������ ������
                      // ��������a MAPREGISTEREX ������a � MAPCREAT.H
                      // ��� �������� TIN-������ ������������
                      // �������� ��������� ����� :
                      //  Name - �������� ��� ������,
                      //  Scale - ����������� ��������,
                      //  EllipsoideKind - ��� ���������� (��������
                      //    � ������������ � ELLIPSOIDKIND, ���� MAPCREAT.H),
                      //  HeightSystem - ������� ����� (��������
                      //    � ������������ � HEIGHTSYSTEM, ���� MAPCREAT.H),
                      //  MaterialProjection - �������� ��������� ���������
                      //    (�������� � ������������ � MAPPROJECTION, ���� MAPCREAT.H),
                      //  CoordinateSystem - ������� ��������� (��������
                      //    � ������������ � COORDINATESYSTEM, ���� MAPCREAT.H),
                      //  MapType - ���������� ��� ����� (��������
                      //    � ������������ � MAPTYPE, ���� MAPCREAT.H),
                      //  FirstMainParallel - ������ ������� ���������,
                      //  SecondMainParallel - ������ ������� ���������,
                      //  AxisMeridian - ������ ��������,
                      //  MainPointParallel - ��������� ������� �����.

  HOBJ Border;        // ������������� ���������� ������� �����,
                      // �� �������� ��������������� ����� �����������
                      // TIN-������ (���� ������ ���������� ��� ���������
                      // ������, ������������ ���������� ���� FrameMeters
                      // ������ ���������, �� ����� �� ���������������)

  char      Reserve[60];    // ������ ���� ����
}
  TINBUILD;

//------------------------------------------------------------------
//  �������� �������� TIN-������
//------------------------------------------------------------------
typedef struct TINDESCRIBE   // ������ ��������� 1024 �����
{
  char    Name[260];         // ��� ����� ������

  long    Length;            // ����� �����
  long    UserLabel;         // ���������������� �������������
  long    ModelType;         // ��� ������
  long    Method;            // ����� ���������� ������
  long    VertexCount;       // ���������� ������
  long    TriangleCount;     // ���������� �������������
  long    View;              // ������� ��������������

  DFRAME  FrameMeters;       // �������� ������ � ����� (�����)

  double  MinHeightValue;    // ����������� �������� ������ ����������� (�����)
  double  MaxHeightValue;    // ������������ �������� ������ ����������� (�����)

  MAPREGISTEREX
      ModelRegister;  // ���������� ������ ������
                      // ��������a MAPREGISTEREX ������a � MAPCREAT.H
                      // �������� TIN-������ �������� ��������
                      // ��������� ����� :
                      //  Name - �������� ��� ������,
                      //  Scale - ����������� ��������,
                      //  EllipsoideKind - ��� ����������,
                      //  HeightSystem - ������� �����,
                      //  MaterialProjection - �������� ��������� ���������,
                      //  CoordinateSystem - ������� ���������,
                      //  MapType - ���������� ��� �����,
                      //  FirstMainParallel - ������ ������� ���������,
                      //  SecondMainParallel - ������ ������� ���������,
                      //  AxisMeridian - ������ ��������,
                      //  MainPointParallel - ��������� ������� �����.

  double  ModelSquare;       // ������� ������ (��.�����) 

  char    Reserve[472];      // ������

}
  TINDESCRIBE;

//------------------------------------------------------------------
// ��������� ������ ������� TIN-������
//------------------------------------------------------------------
typedef struct TINVERTEXFLAG   // ������ ��������� 8 ����
{
  char   Cancel;         // ���� ��������
  char   PolygonBorder;  // ���� �������������� ���������
                         // ����� �������� ������������
  char   StructLine;     // ���� �������������� ����������� �����
  char   FaultLine;      // ���� �������������� ����� �������
  char   FillingSquare;  // ���� �������������� ������� �������
                         // ����������
  char   Reserve[3];
}
  TINVERTEXFLAG;

//------------------------------------------------------------------
// ��������� ������ ������� ������ TIN-������
//------------------------------------------------------------------
typedef struct TINVERTEX     // ������ ��������� 40 ����
{
  double X;                  // ���������� ������� � �������������
  double Y;                  // ������� � �������� �������� (�����)
  double H;
                             // ��� ������, �������� � ������ ����� �������
  long   UpperVertexNumber;  // ����� ������� �������� ������
  long   UnderVertexNumber;  // ����� ������� ������� ������

  TINVERTEXFLAG Flag;        // ����� �������
}
  TINVERTEX;

//------------------------------------------------------------------
// ��������� ������ ������������ TIN-������
//------------------------------------------------------------------
typedef struct TINTRIANGLEFLAG   // ������ ��������� 16 ����
{
  char Cancel;           // ���� ��������

  char Location;         // ���� ��������� ������������ � ����
                         // (0 - ���������� ����������� ����,
                         //  1 - ������� ����������� ����)

  char FillingSquare;    // ���� �������������� ������� ������������
                         // ������� ����������

  char AB;               // ���� ����� "AB"
  char BC;               // ���� ����� "BC"
  char CA;               // ���� ����� "CA"
                         // (0 - ����� �� ������ � ������
                         //      ����������� �����,
                         //  1 - ����� ������ � ������ �����������
                         //      ����� �������� ��������,
                         //  2 - ����� ������ � ������ �����������
                         //      ����� ���������� ��������,
                         //  3 - ����� ������ � ������ �����������
                         //      ����� �������,
                         //  4 - ����� ������ � ������ �������
                         //      �������� ���������� ������������)
  char Reserve[10];

}
  TINTRIANGLEFLAG;
  
//------------------------------------------------------------------
// ��������� ������ ������� ������������� TIN-������
//------------------------------------------------------------------
typedef struct TINTRIANGLE  // ������ ��������� 40 ����
{
  long A;     // ����� ������� "A" � ������� ������
  long B;     // ����� ������� "B" � ������� ������
  long C;     // ����� ������� "C" � ������� ������

  long AB;    // ����� ��������� ������������ �� ����� "AB"
              // � ������� �������������
  long BC;    // ����� ��������� ������������ �� ����� "BC"
              // � ������� �������������
  long CA;    // ����� ��������� ������������ �� ����� "CA"
              // � ������� �������������
              // (���� ��������� ������������ ���, ����� ����� -1)

  TINTRIANGLEFLAG Flag;  // ����� ������������
}
  TINTRIANGLE;


  
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ �������� ������� ������� � TIN-������ +++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{
  // ��������� ����� �������� TIN-������
  // ��� ������ ���������� 0

  long int _MAPAPI mapGetTinCount(HMAP hMap);

  // ������� TIN-������
  // ���������� ������������� �������� ������ (TMapAccess*)
  // ��� ������ ���������� 0

  HMAP _MAPAPI mapOpenTin(const char * tinname,
                          long int mode);

  // ������� TIN-������ � �������� ������ ����� (�������� � �������)
  // ���������� ����� ����� � �������
  // ��� ������ ���������� 0

  long int _MAPAPI mapOpenTinForMap(HMAP hMap,
                                    const char * tinname,
                                    long int mode);

  // ������� TIN-������
  // number - ����� ����������� ������
  // ���� number == 0, ����������� ��� ������ � ����

  void _MAPAPI mapCloseTin(HMAP hMap, long int number);

  // ������� TIN-������ � �������� ������ �����
  // number - ����� ����� ������ � �������
  // ���� number == 0, ����������� ��� ������
  // ��� ������ ���������� 0

  long int _MAPAPI mapCloseTinForMap(HMAP hMap, long int number);

  // ������� TIN-������
  // ���������� ������������� �������� ������ (TMapAccess*)
  // ��������a TINBUILD ������a � TINAPI.H
  // ��� ������ ���������� 0

  HMAP _MAPAPI mapCreateTin(const char * name,
                            const TINBUILD * parm);

  // ������� ���� TIN-������
  // hMap -  ������������� �������� ��������� �����
  // tinname - ������ ��� ����� ������
  // parm - ��������� �������� ������
  // ��������a TINBUILD ������a � TINAPI.H
  // ����������  ����� ����� � ������� TIN-�������
  // ��� ������ ���������� 0

  long int _MAPAPI mapCreateAndAppendTin(HMAP hMap,
                                         const char * tinname,
                                         const TINBUILD * parm);

  // �������� ��������� TIN-������ � ����
  // number - ����� ����� � �������
  // ��� ������ ���������� 0

  long int _MAPAPI mapSaveTin(HMAP hMap, long int number);

  // ��������� �������� ����� TIN-������
  // number - ����� ����� � �������
  // describe - ����� ���������, � ������� ����� ���������
  //            �������� TIN-������
  // ��������a TINDESCRIBE ������a � TINAPI.H
  // ��� ������ ���������� 0

  long int _MAPAPI mapGetTinDescribe(HMAP hMap, long int number,
                                     TINDESCRIBE * describe);

  // ��������� ���������� ������ TIN-������
  // number - ����� TIN-����� � �������
  // data - ����� ���������, � ������� ����� ��������� ����������
  // ������ TIN-������
  // ��������a MAPREGISTEREX ������a � MAPCREAT.H
  // ���������� ������ TIN-������ �������� �������� ��������� ����� :
  //  Name - �������� ��� ������,
  //  Scale - ����������� ��������,
  //  EllipsoideKind - ��� ����������,
  //  HeightSystem - ������� �����,
  //  MaterialProjection - �������� ��������� ���������,
  //  CoordinateSystem - ������� ���������,
  //  MapType - ���������� ��� �����,
  //  FirstMainParallel - ������ ������� ���������,
  //  SecondMainParallel - ������ ������� ���������,
  //  AxisMeridian - ������ ��������,
  //  MainPointParallel - ��������� ������� �����.
  // ��� ������ ���������� 0

  long int _MAPAPI mapGetTinRegister(HMAP hMap, long int number,
                                     MAPREGISTEREX* data);
                                     
  // ������ ������� � ������ ������ TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� ������
  // ��������a TINVERTEX ������a � TINAPI.H
  // ��� ������ ���������� 0

  long int _MAPAPI mapPutTinVertex(HMAP hMap, long int number,
                                   const TINVERTEX * vertex, long int index);

  // ������ ������� �� ������� ������ TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� ������
  // ��������a TINVERTEX ������a � TINAPI.H
  // ��� ������ ���������� 0

  long int _MAPAPI mapGetTinVertex(HMAP hMap, long int number,
                                   TINVERTEX* vertex, long int index);

  // ����� �������� ������ ����������� TIN-������ � �������� �����
  // ������ ����������� ������������� �� TIN-������ � �������
  // ������� ����� � �������.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ������� TIN-������ ���������� ERRORHEIGHT.

  double _MAPAPI mapGetSurfaceHeight(HMAP hMap, double x, double y);

  // ����� �������� ������ ����������� TIN-������ � �������� �����
  // �� ����� � ������� number � �������.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ������� TIN-������ ���������� ERRORHEIGHT.

  double _MAPAPI mapGetTinSurfaceHeight(HMAP hMap, long int number,
                                        double x, double y);

  // ��������� ������ ������� TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� ������
  // flag - ����� ���������, ���������� ��������������� ��������
  //        ������ �������
  // ��������a TINVERTEXFLAG ������a � TINAPI.H
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetTinVertexFlags(HMAP hMap, long int number,
                                        long int index, const TINVERTEXFLAG* flag);

  // ������ ������ ������� TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� ������
  // flag - ����� ���������, ���������� �������� ������ �������
  // ��������a TINVERTEXFLAG ������a � TINAPI.H
  // ��� ������ ���������� 0

  long int _MAPAPI mapGetTinVertexFlags(HMAP hMap, long int number,
                                        long int index, TINVERTEXFLAG* flag);


  // ��������� ������ ������������ TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� �������������
  // flag - ����� ���������, ���������� ��������������� ��������
  //        ������ ������������
  // ��������a TINTRIANGLEFLAG ������a � TINAPI.H
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetTinTriangleFlags(HMAP hMap, long int number,
                                          long int index, const TINTRIANGLEFLAG* flag);

  // ������ ������ ������������ TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� �������������
  // flag - ����� ���������, ���������� �������� ������ ������������
  // ��������a TINTRIANGLEFLAG ������a � TINAPI.H
  // ��� ������ ���������� 0

  long int _MAPAPI mapGetTinTriangleFlags(HMAP hMap, long int number,
                                          long int index, TINTRIANGLEFLAG* flag);

  // ������ ������������ �� ������� ������������� TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� �������������
  // ��������a TINTRIANGLE ������a � TINAPI.H
  // ��� ������ ���������� 0

  long int _MAPAPI mapGetTinTriangle(HMAP hMap, long int number,
                                     TINTRIANGLE* triangle, long int index);

  // ������ ������������ � ������ ������������� TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� �������������
  // ��������a TINTRIANGLE ������a � TINAPI.H
  // ��� ������ ���������� 0

  long int _MAPAPI mapPutTinTriangle(HMAP hMap, long int number,
                                     const TINTRIANGLE* triangle, long int index);



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  �������� ������� ��������� ���������� TIN-������  +++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  // ���������� ���������� ������ TIN-������
  // number - ����� TIN-����� � �������
  // data - ����� ���������, ���������� ���������� ������ TIN-������
  // ��������a MAPREGISTEREX ������a � MAPCREAT.H
  // ���������� ������ TIN-������ �������� �������� ��������� ����� :
  //  Name - �������� ��� ������,
  //  Scale - ����������� ��������,
  //  EllipsoideKind - ��� ���������� (��������
  //    � ������������ � ELLIPSOIDKIND, ���� MAPCREAT.H),
  //  HeightSystem - ������� ����� (��������
  //    � ������������ � HEIGHTSYSTEM, ���� MAPCREAT.H),
  //  MaterialProjection - �������� ��������� ���������
  //    (�������� � ������������ � MAPPROJECTION, ���� MAPCREAT.H),
  //  CoordinateSystem - ������� ��������� (��������
  //    � ������������ � COORDINATESYSTEM, ���� MAPCREAT.H),
  //  MapType - ���������� ��� ����� (��������
  //    � ������������ � MAPTYPE, ���� MAPCREAT.H),
  //  FirstMainParallel - ������ ������� ���������,
  //  SecondMainParallel - ������ ������� ���������,
  //  AxisMeridian - ������ ��������,
  //  MainPointParallel - ��������� ������� �����.
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetTinRegister(HMAP hMap, long int number,
                                     const MAPREGISTEREX* data);

  // ���������� ���������������� ������������� TIN-������
  // userLabel - ������������� ������
  // number  - ����� TIN-����� � �������
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetTinUserLabel(HMAP hMap, long int number,
                                      long int userLabel);

  // ���������� ��� TIN-������
  // number - ����� TIN-����� � �������
  // type - ��� ������
  //   (�������� � ������������ � TINBUILD, ���� TINAPI.H)
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetTinModelType(HMAP hMap, long int number,
                                      long int type);

  // ���������� ����� ���������� TIN-������
  // number  - ����� TIN-����� � �������
  // method - ����� ����������  ������
  //   (�������� � ������������ � TINBUILD, ���� TINAPI.H)
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetTinMethod(HMAP hMap, long int number,
                                   long int method);
                                      
  // ���������� �������� TIN-������ � ������
  // frame - �������� ������ � ������ (�����)
  // ��������a DFRAME ������a � MAPTYPE.H
  // number  - ����� TIN-����� � �������
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetTinFrameMeters(HMAP hMap, long int number,
                                        const DFRAME* frame);

  // ���������� �������� �������� ������ ����������� TIN-������
  // number  - ����� TIN-����� � �������
  // minimum - ����������� �������� ������ ����������� (�����)
  // maximum - ������������ �������� ������ ����������� (�����)
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetTinHeightDiapason(HMAP hMap, long int number,
                                           double minimum,
                                           double maximum);

  // ���������� ������� �������������� TIN-������
  // number - ����� TIN-����� � �������
  // view - ������� ��������������
  //   (0 - ������ �� ������������, 1 - ������ ������������)
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetTinView(HMAP hMap, long int number,
                                 long int view);
                                 
  // ���������� �������� �������� ������ � �������
  // ������ ��������� TIN-������
  // number - ����� TIN-����� � �������
  // bottomScale - ����������� �������� ������ ������� ���������
  // topScale - ����������� �������� ������� ������� ���������
  // ���� �� ����������� ������� bottomScale <= topScale, ���������� 0
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetTinRangeScaleVisible(HMAP hMap, long int number,
                                              long int bottomScale,
                                              long int topScale);

  // ��������� �������� �������� ������ � �������
  // ������ ��������� TIN-������
  // number - ����� TIN-����� � �������
  // �� ������ bottomScale ������������ ����������� ��������
  // ������ ������� ���������
  // �� ������ topScale ������������ ����������� ��������
  // ������� ������� ���������
  // ��� ������ ���������� 0

  long int _MAPAPI mapGetTinRangeScaleVisible(HMAP hMap, long int number,
                                              long int *bottomScale,
                                              long int *topScale);

}

#endif // TINAPI_H

