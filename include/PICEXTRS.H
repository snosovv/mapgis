/****  PICEXTRS.H    **********  Gustinovich N.A.*****  23/04/03 ***
*****  PICEXTRS.H    **********  Shabakov D.A.   *****  28/09/05 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2005              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
*                   FOR  WINDOWS95 & WINDOWS NT                    *
*                                                                  *
********************************************************************
*                                                                  *
*            �������� ������� ��������� ������                     *
*        ��������� ��� �������� �� ������ C, PASCAL, BASIC         *
*                                                                  *
*******************************************************************/
#if !defined(PICEXTRS_H)
#define PICEXTRS_H

#ifndef MACPICEX_H
  #include "macpicex.h"
#endif


#define WM_RSTROTATE        0x500       // ������� ������
#define RSTTRANS_DIAL       0x501       // ����� ������� ������-� ������
#define RSTTRANS_NEWPARM    0x502       // ���������� ���������� ���.������
#define RSTTRANS_END        0x503       // ���������� ������

#ifdef WIN32API                  // 18/06/02
   #define HMESSAGE HWND
#else
   #define HMESSAGE MSGHANDLER
#endif


extern "C"
{
 typedef long int  HTFCR;    // ������������� �������� �������� TIFF

 // *********************************************************
 // ����� ������� �������� �������� TIFF:
 // =============
 // HTFCR hTiffCreate = picexCreateTiffFile(handle,tiffname,
 //                               width, height,
 //                               nbits,
 //                               palette, colorcount,
 //                               precision,
 //                               flagCompress,
 //                               platform,
 //                               flagCMYK};
 // if (hTiffCreate)
 //    {
 //     long int stripCount         = picexGetTiffStripCount(hTiffCreate);
 //     long int stringCountByStrip = picexGetTiffstringCountByStrip(hTiffCreate);
 //     for (int i = 0; i < stripCount, i++)
 //        {
 //         if (picexPutTiffStrip(hTiffCreate, numberStrip,
 //                              bits, sizeBits) == 0)
 //            break;
 //        }
 //     picexSaveTiffFile(hTiffCreate);
 //     picexFreeTFCRProcess(hTiffCreate);
 //    }
 // **********************************************************


 //    ��������� ����������� ������ � ����� ������� TIFF  (�����������)
 //    handle     - ������ ����������� ������������� �������� ���������.
 //    tiffname   - ��� TIFF-�����;
 //    width      - ������ ����������� � ��������
 //    height     - ������ ����������� � ��������
 //    nbits      - ������ ������� (��� �� �������)
 //    palette    - ����� ��������������� �������
 //                 ���� palette == 0, � colorcount != 0, �� �������� ����������
 //                 ������� ����� �������� Load_SetTiffPalette()
 //    colorcount - ����� ��������� � ����� �������
 //    precision  - ���������� ����������� (����� �� ����)
 //    platform - ��� ��������� (0 - INTEL, 1 - MOTOROLA)             (������������� �������� - 0)
 //    compressMethod - ���� ������ ����������� (0- �� ��������� ������, 1 - ������ PackBit) (������������� �������� - 0)
 //    flagCMYK - ����� �������� ������:
 //                     0 - �������� ������ RGB 24 ��� �� ������
 //                     1 - �������� ������ CMYK 32 ��� �� ������
 //                     ����� �������������� ������ ���  ������� 24,32 ��� �� ������.
 //    flagIntergraphTIFF - ���� ������ ������� ����������������� ��� ����������� TIFF ��� ������������� � Intergraph // 28/09/05
 //                     ����� �������������� ������ ���  ������� 1 ��� �� ������.
 //    dframe           - �������� ����������� � ������ � ������ ��� ������ ������� ����������������� ��� ����������� TIFF  // 28/09/05
 //                     ����� �������������� ������ ���  ������� 1 ��� �� ������.
 //    ���������� ������������� �������� �������� TIFF
 //    ��� ������ ���������� 0
 //    ������� ����������� ������������� �������� ��������� ����������
 //    ���������:
 //    -  (WM_ERROR) ��������� �� ������
 //       LPARAM - ��������� �� ��������� ERRORINFORMATION
 //       ��������� ERRORINFORMATION ������� � picexprm.h, WM_ERROR - � maptype.h
 HTFCR WINAPI _export picexCreateTiffFile(HMESSAGE handle,
                                          const char * tiffname,
                                          long int width, long int height,
                                          long int nbits,
                                          COLORREF* palette, long int colorcount,
                                          double precision,
                                          long int compressMethod,
                                          long int platform,
                                          int flagCMYK);

 HTFCR WINAPI _export picexCreateTiffFileEx(HMESSAGE handle,
                                          const char * tiffname,
                                          long int width, long int height,
                                          long int nbits,
                                          COLORREF* palette, long int colorcount,
                                          double precision,
                                          long int compressMethod,
                                          long int platform,
                                          long int flagCMYK,
                                          long int flagIntergraphTIFF,  // 28/09/05
                                          DFRAME * dframe);             // 28/09/05



 //    ��������� ���������� ������� (����� �����������)
 //    ��� ������ ���������� 0
 long int WINAPI _export picexGetTiffStripCount(HTFCR hTiffCreate);

 //    ��������� ���������� ����� ����������� � ������
 //    ��� ������ ���������� 0
 long int WINAPI _export picexGetTiffStringCountByStrip(HTFCR hTiffCreate);

 //    �������� ����� � ������� numberStrip � ����
 //    ��� ������ ����� ���������� ������, �� ����������� ����������
 //    ��������� � ������ ������� ������-����
 //    ���� flagCompress == 1, ����� ������������ ������ �� ������ PackBit
 //    ��� ������ ���������� 0
 long int WINAPI _export picexPutTiffStrip(HTFCR hTiffCreate, long int numberStrip,
                                           char*bits, long int sizeBits);

 //    �������� ����� � ������� numberStrip � ����   // 06/02/04
 //    �������� ������ ����������� - CMYK(flagCMYK = 1),  32 ��� �� ������ (nbits = 32)
 //    ����� �������� ���������������(�� �� ����������).
 //    ��� ������ ����� ���������� ������, �� ����������� ����������
 //    ��������� � ������ ������� ������-����
 //    ���� flagCompress == 1, ����� ������������ ������ �� ������ PackBit
 //    numberStrip - ������� � ����
 //    ��� ������ ���������� 0
 long int WINAPI _export picexPutTiffStrip_CMYK(HTFCR hTiffCreate, long int numberStrip,
                                                 char*bitsCMYK, long int sizeBitsCMYK);

 // �������� ������� � ����
 // ��� ����������� � 4 � 8 ��� �� ������
 //    ��� ������ ���������� 0
 long int WINAPI _export picexSetTiffPalette(HTFCR hTiffCreate, COLORREF* palette,
                                                             long int colorCount);

 // �������� ��������� � ���������� ���� � ����
 // ��� ������ ���������� 0
 long int WINAPI _export picexSaveTiffFile(HTFCR hTiffCreate);


 // ������������ ������ (����������)
 // ��� ������ ���������� 0
 long int WINAPI _export picexFreeTFCRProcess(HTFCR hTiffCreate);

 // ����������� �������� ����������� � ������ ����� ������  // 10/07/03
 // rect - �� ������ rect ������������ �������� ����� ������ � ��������� ������
 // ��� ������ ���������� ����
 long int WINAPI _export picexSizeImageDefinition(HMAP hMap, long int rstNumber, RECT* rect);

 // ������� ������ ����� TIFF-����� � ���� *.tls   // 25/05/05
 //    Map - �����,���������� ��������� ������;
 //    TifName - ��� TIF-�����;
 //    FileName - ��� ����� *.tls;
 long int WINAPI _export picexSaveTiffTagsIntoFile(HMESSAGE Handle, char * TiffName, char * FileName);



//========================================================================
//    ����������������� ������
// (���������� ������������� ��������� ��������� ������� ���������� ���������)
//
//    map        - �����,���������� ��������� ������;
//    RstParm    - ��������� ����������������� ������
//    handle     - ������ ����������� ������������� �������� ���������.
//========================================================================
/*long int WINAPI _export RstTransform(HMAP map,
                        RSTPARM * RstParm,
                        HMESSAGE handle);


//========================================================================
//    ����������������� ������ �� ����� � ������� �������
//                 (��������� ������ ������)
// (���������� ������������� ��������� ��������� ������� ���������� ���������)
//
//    map        - �����,���������� ��������� ������;
//    RstParm    - ��������� ����������������� ������
//    handle     - ������ ����������� ������������� �������� ���������.
//========================================================================
long int WINAPI _export RstSomeTransform(HMAP map,
                            RSTPARM * RstParm,
                            HMESSAGE handle);

//========================================================================
//    ����������������� ������
// (���������� ������������� ��������� ��������� �� ������ ������)
//
//    map        - �����,���������� ��������� ������;
//    RstParm    - ��������� ����������������� ������
//    handle     - ������ ����������� ������������� �������� ���������.
//========================================================================
long int WINAPI _export RstTriangle(HMAP map,
                            RSTPARM * RstParm,
                            HMESSAGE handle);
//========================================================================
//    ����������������� ������ �� ��������� �������� ��������������
//
//    map        - �����,���������� ��������� ������;
//    RstParm    - ��������� ����������������� ������
//    handle     - ������ ����������� ������������� �������� ���������.
//========================================================================
long int WINAPI _export RstTransEvo(HMAP map,
                       RSTPARM * RstParm,
                       HMESSAGE handle);
*/

}       // extern "C"


#endif  // PICEXTRS_H
