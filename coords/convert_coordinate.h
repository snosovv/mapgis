#ifndef  _CONVERT_COORDINATE_H
#define  _CONVERT_COORDINATE_H

#include <QString>
//-----------------------------------------------------------------------

//������������ ��� �������������� � ������� spheroid GEO_SYSTEM_CONVERT
typedef enum {mWGS_84 = 0,
			  mPZ_90 = 1,
              mCK_42 = 2,			 
			  mCK_95 = 3,
	      mPZ_90_02 = 4}eGeodeticSystem;//������ ����� 

//��������� �������� ����
typedef struct sAngle  
{
  int grad;     // �������
  int min;      // ������
  double sec;   // �������
  int sign;     // ���� (+1 - ����� ��� ������ ��� -1 - �� ��� �����)
  sAngle ():grad(0),sec(0.0),sign(1){grad=0;min=0;sec=0.0;sign=1; };
}sAngle;

//��������� �������� ���������� ��������/������ �����
typedef struct _spheroid
{
    double a;   //a (�������������� ������ ��������)
    double e2;  //e (������� 1-��� ��������������� ��������������� �������)

    //�������� ������ � ������, �������� �������� ����������������� ������������ WGS-84
	//delta = �������� ������������ ������ ����� - �������� WGS_84   
	double dX;  //   
    double dY;  //
    double dZ;  //

    //���� �������� � ������� �������� ������������ WGS-84 � ������� ��������
	//Ang = ���� �������� + ���� �������� WGS_84
	double AngX;//omega_x 
    double AngY;//omega_y
    double AngZ;//omega_z

	double M; //���������������� �������� �������� ��������� ������������ WGS-84

	char name[10];//�������� ������� ���������
}spheroid;

//-----------------------------------------------------------------------
/*								���������								*/

const unsigned int _KOL_GEO_SYS = 5; //���������� ������ ���������

//-----------------------------------------------------------------------
/*							���������� ����������						*/

extern spheroid GEO_SYSTEM_CONVERT[_KOL_GEO_SYS]; //������ ���������� ������ ��������

//-----------------------------------------------------------------------

//����������: XYZ - ������������� ����������, �����
//			  BLH - ������������� ����������, �������

//������� �������������� ��������� �� BLH � XYZ
extern void ConvertBLHtoXYZ(double B, double L, double H, 
							double *X, double *Y, double *Z, 
							double a, double e2);

extern void ConvertBLHtoXYZ(double B, double L, double H, 
							double *X, double *Y, double *Z, 
							eGeodeticSystem sys);

//������� �������������� ��������� �� XYZ � BLH
extern void ConvertXYZtoBLH(double X, double Y, double Z, 
							double *B, double *L, double *H, 
							double a, double e2);

extern void ConvertXYZtoBLH(double X, double Y, double Z, 
							double *B, double *L, double *H,
							eGeodeticSystem sys);

//������� �������������� ��������� XYZ �� WGS_84 � ������ ������� �����.
extern void ConvertWGS84_XYZtoUser_XYZ(double X, double Y, double Z, 
								double *UX, double *UY, double *UZ, eGeodeticSystem sys);

//������� �������������� ��������� XYZ �� ������ ������� �����. � WGS_84
extern void ConvertUserXYZ_to_WGS84_XYZ(double X, double Y, double Z, 
								double *UX, double *UY, double *UZ, eGeodeticSystem sys);

//������� �������������� ��������� �� XYZ (�������������) � BLH (�������������)
extern void ConvertUserXYZ_to_UserBLH(double X, double Y, double Z, eGeodeticSystem sys_from,
					   double *B, double *L, double *H, eGeodeticSystem sys_to);

//������� �������������� ��������� �� BLH (�������������) � XYZ (�������������)
extern void ConvertUserBLH_to_UserXYZ(double B, double L, double H, eGeodeticSystem sys_from,
					   double *X, double *Y, double *Z, eGeodeticSystem sys_to);

//������� �������������� ��������� XYZ (�������������, �����) �� 
//������ ������� � �����������
extern void ConvertXYZ(double X, double Y, double Z, eGeodeticSystem sys_from,
					   double *UX, double *UY, double *UZ, eGeodeticSystem sys_to);

//������� �������������� ��������� BLH (�������������, �������) 
//�� ������ ������� � �����������
extern void ConvertBLH(double B, double L, double H, eGeodeticSystem sys_from,
					   double *UB, double *UL, double *UH, eGeodeticSystem sys_to);

//������� �������������� ��������� �� ������ � �������, 
//���������� �������
extern double RadianToDegree(double rad);

//������� �������������� ��������� �� �������� � �������, 
//���������� �������	
extern double DegreeToRadian(double degree);

//������� �������������� �������� � ��������� Angle	
extern void DegreeToAngle(double degree, sAngle *angle);

//������� �������������� ������ � ��������� Angle
extern void RadianToAngle(double radian, sAngle *angle);

// ������� �������������� ��������� Angle � �������					  
extern double AngleToDegree(sAngle *angle);

// ������� �������������� ��������� Angle � �������					  
extern double AngleToRadian(sAngle *angle);

// ������� �������������� �� ��������, �����, ������ � �������
extern double get_radians_from_gms(char c,int grad, double min, double sec=0.0);

extern int AngleToInt(sAngle *angle);
extern double IntToRadian(int str);

//������� �������������� ��������� � ���������� ����
extern QString TextCoord(double *rad);
//-----------------------------------------------------------------------

#endif //CONVERT_COORDINATE_H
