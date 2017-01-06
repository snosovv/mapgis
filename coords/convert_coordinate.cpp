/* ���������������� ������������ ����� */
#include "convert_coordinate.h"
#include "_math_.h"
#include "constant.h"
//-----------------------------------------------------------------------
/*							���������� ����������						*/

//������ ���������� ������ ��������
spheroid GEO_SYSTEM_CONVERT[_KOL_GEO_SYS]=
{
	{ 6378137.0,6.69437999014E-3,
	  0.0,0.0,0.0,
	  0.0,0.0,0.0,
	  0.0,"WGS_84"}, 
	{ 6378136.0,6.694385E-3,
	  1.1,0.3,0.9, 
	  0.0,0.0,0.2,
          0.12E-6,"PZ_90"}, // �� ����� 
	{ 6378245.0,6.6934216E-3,
	  -25.0,141.0,80.9, 
	  0.0,0.35,0.86,// AngZ = 0.66 + 0.2
	  0.12E-6,"CK_42"}, // M = 0 + 0.12
	{ 6378245.0,6.6934216E-3,
	  -24.8,131.21,82.66,//dX=-25.9+1.1, dY=130.94+0.3,dZ=81.76+0.9 
	  0.0,0.0,0.2,//AngZ=0+0.2
	  0.12E-6,"CK_95"},// M = 0 + 0.12 
	/*{6378136.0,0.6,6.694385E-3,
	 0.36,-0.08,-0.18,
	 0,"PZ_90_02"},
*/

};

//-----------------------------------------------------------------------
//const spheroid CK_95 ={6378136.0,6.694385E-3,25.90,-130.94,-81.76,0.0,0.0,0.0};
//const spheroid WGS_84={6378137.0,6.69437999014E-3,-1.1,-0.3,-0.9,0.0,0.0,0.82E-6};
//const spheroid CK_42 ={6378245.0,6.6934216E-3,25.0,-141.0,-80.0,0,-3.3E-6,-1.8E-6};
//const spheroid PZ_90 ={6378136.0,6.694385E-3,0.0,0.0,0.0,0.0,0.0,0.0};
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
/* ������� �������������� ��������� �� BLH � XYZ
   ���������:
	B	- ������, �������
	L	- �������, �������
	H	- ������, �����	
	*X	- ������, �����
	*Y  - �������, �����
	*Z  - ������, �����
	a	- ������� �������, �����
	e2	- ������� �������������
 */
//-----------------------------------------------------------------------
/*
	��������: Datum Transformations of GPS Positions, 5th July 1999

	�������������� BLH (�������) � XYZ (�����)    
    X = (N + h) cos(lat) cos(long)
	Y = (N + h) cos(lat) sin (long)
    Z = ( (b^2/a^2) * N + h) sin(lat),
	��� 
	lat - ������, �������
	lon - �������, �������
	h - ������ ��� �����������, �����
	N - ������ ��������, �����
	N = a / (sqrt( 1 - e^2 * sin(lat)^2 ))
	a - ������� ������� � ������ 
	b - ������� ������� � ������, ����� ���� ���������, ��� b = a (1-f)
	e - ���������������, e = sqrt( (a^2-b^2) / a^2 ) 
   
*/
//-----------------------------------------------------------------------
void ConvertBLHtoXYZ(double B, double L, double H, 
					 double *X, double *Y, double *Z, double a, double e2)
{
  double cos_lat = cos(B);

  double sin_lat = sin(B);
  
  double cos_long = cos(L);
  
  double sin_long = sin(L);
  
  double N = a/sqrt(1.0E0-e2*sin_lat*sin_lat); // N = a / (sqrt( 1 - (e * sin(lat))^2 ))
  
  double nph = N + H;
  
  *X = nph*cos_lat*cos_long; // X = (N + h) cos(lat) cos(long)
  
  *Y = nph*cos_lat*sin_long; // Y = (N + h) cos(lat) sin (long)
  
  // ��� �����, ��� b^2/a^2 ���, ��� 1 - e^2 = 1 - (a^2-b^2) / a^2 = 1 - 1 + b^2/a^2
  double ome2 = 1 - e2; 
  
  *Z = (ome2*N + H)*sin_lat; // Z = ( (b^2/a^2) * N + h) sin(lat)
}

//-----------------------------------------------------------------------
/* ������� �������������� ��������� �� BLH � XYZ
   ���������:
	B	- ������, �������
	L	- �������, �������
	H	- ������, �����	
	*X	- ������, �����
	*Y  - �������, �����
	*Z  - ������, �����
	sys - ��� ������ �����
 */
//-----------------------------------------------------------------------
void ConvertXYZtoBLH(double X, double Y, double Z, 
					 double *B, double *L, double *H,eGeodeticSystem sys)
{
	spheroid *sp;
	sp = &GEO_SYSTEM_CONVERT[sys];	
	ConvertXYZtoBLH(X, Y, Z, B, L, H, sp->a, sp->e2);
}

//-----------------------------------------------------------------------
/* ������� �������������� ��������� �� XYZ � BLH
	X	- ������, �����
	Y	- �������, �����
	Z	- ������, �����
	*B	- ������, �������
	*L	- �������, �������
	*H	- ������, �����
	a	- ������� �������, �����
	e2	- ������� ����������������
*/
//-----------------------------------------------------------------------
/*
	��������: Datum Transformations of GPS Positions, 5th July 1999

	�������������� XYZ (�����) � BLH (�������)  
    ����� ���� ����������, ��������� ���� �� ��������� �������: 
	- ������������ ��� ������ � ������
	 lon = arctan (y/x);
     lat = atctan (Z / (p(1-e^2)))
	 ���� �� lat, h
        N[i] = a / sqrt (1-e^2*sin(lat[i])^2)
		h[i+1] = p / cos(lat[i]) - N[i]
		lat[i+1] = arctan(Z/(p(1-e^2(N[i]/(N[i]+h[i+1]))))) 
	  ��� 
		lat - ������, �������
		lon - �������, �������
		h - ������ ��� �����������, �����
		a	- ������� �������, �����
	    e	- ���������������
		p = sqrt( lat^2 + lon^2 )
	- ������� �������������� ��� h<<N ������������ � h0 = 0.
*/
//-----------------------------------------------------------------------
void ConvertXYZtoBLH(double X, double Y, double Z, double *B, double *L, double *H, double a, double e2)
{
	double rho = sqrt( X*X + Y*Y );

	double eps = 1.0E-13;

	double dpi2 = 1.570796326794897E0;

	if( rho <= eps )// �� ������
	{
		*B = dpi2;
		if( Z < 0.0 ) *B = - (*B);
		*L = 0.0E0;
		*H = fabs(Z)-a*sqrt((1-e2)); // sqrt(a*a*(1-e2)) = b
		return;
	}
	
	*L = atan2(Y,X);

	*B = atan2(Z,rho*(1.0-e2));

	double N = 0.0; //a / sqrt(1-e2*sin(*B)*sin(*B));

	*H = 0;

	double latold = *B + 1.0E0;

	double hold = *H + 1.0E0;

	int step = 20;
   
	while(fabs(*B-latold)>=eps || fabs(*H-hold)>=0.01)
	{
		latold = *B;

		hold = *H;	

		N = a / sqrt(1-e2*sin(*B)*sin(*B));

		*H = rho/cos(*B)-N;

        *B = atan2(Z,rho*(1.0-e2*N/(N+*H)));
	
		if(--step) continue;

		*B=*L=*H=0.0;
	} 
}

//-----------------------------------------------------------------------
/* ������� �������������� ��������� �� XYZ � BLH
   ���������:
	B	- ������, �������
	L	- �������, �������
	H	- ������, �����	
	*X	- ������, �����
	*Y  - �������, �����
	*Z  - ������, �����
	sys - ��� ������ �����
 */
//-----------------------------------------------------------------------
void ConvertBLHtoXYZ(double B, double L, double H, double *X, double *Y, double *Z,eGeodeticSystem sys)
{
	spheroid *sp;
	sp = &GEO_SYSTEM_CONVERT[sys];	
	ConvertBLHtoXYZ( B, L, H, X, Y, Z, sp->a, sp->e2);
}

//-----------------------------------------------------------------------
/* ������� �������������� ��������� XYZ �� �����������/��� WGS_84 
  � WGS_84/����������� ������� ��������� � ����������� �� ���������� ��������
  X	- ������, �����
  Y	- �������, �����
  Z	- ������, �����
  *UX - ������, �����
  *UY - �������, �����
  *UZ - ������, �����
  *sp - ��������� ��������, 
        ���� ��������� �� ���������������� � WGS_84, �� ��������� �������������
*/
//-----------------------------------------------------------------------
void convert(double X, double Y, double Z, 
								double *UX, double *UY, double *UZ, spheroid *sp)
{
	double CSR = CGR * CSG; //��� �������������� ������  � �������
	double wx =  sp->AngX * CSR; 
	double wy =  sp->AngY * CSR;
	double wz =  sp->AngZ * CSR;
	*UX = sp->dX + (X + wz*Y - wy*Z)*(1+sp->M);
	*UY = sp->dY + (Y - wz*X + wx*Z)*(1+sp->M);
	*UZ = sp->dZ + (Z + wy*X - wx*Y)*(1+sp->M);
}

//-----------------------------------------------------------------------
/*	������� �������������� ��������� XYZ �� WGS_84 � ������ ������� �����.
	X - ������ WGS_84, �����
    Y - ������� WGS_84, �����
    Z - ������ WGS_84, �����
    *UX	- ������, �����
    *UY - �������, �����
    *UZ - ������, �����
	sys - ������� ���������, � ������� �����������
*/
//-----------------------------------------------------------------------
void ConvertWGS84_XYZtoUser_XYZ(double X, double Y, double Z, 
								double *UX, double *UY, double *UZ, eGeodeticSystem sys)
{
	spheroid *sp;
	sp = &GEO_SYSTEM_CONVERT[sys];	
    convert(X, Y, Z,UX, UY, UZ, sp);
}

//-----------------------------------------------------------------------
/*	������� �������������� ��������� XYZ �� ������ ������� �����. � WGS_84
	X	- ������, �����
    Y  - �������, �����
    Z  - ������, �����
    *UX	- ������ WGS_84, �����
    *UY  - ������� WGS_84, �����
    *UZ  - ������ WGS_84, �����
	sys - ������� ���������, �� ������� �����������					*/
//-----------------------------------------------------------------------
void ConvertUserXYZ_to_WGS84_XYZ(double X, double Y, double Z, 
								double *UX, double *UY, double *UZ, eGeodeticSystem sys)
{
	spheroid *sp; 
	sp = &GEO_SYSTEM_CONVERT[sys];
	//��� ��������� �������������� ��������, 
	//������� ������������� �������� ���������� ��������
    sp->dX *= (-1);
	sp->dY *= (-1);
	sp->dZ *= (-1);
	sp->M *= (-1);
	sp->AngX *= (-1);
	sp->AngY *= (-1);
	sp->AngZ *= (-1);
    convert(X, Y, Z,UX, UY, UZ, sp);	
}

//-----------------------------------------------------------------------
/*	������� �������������� ��������� �� XYZ (�������������) � BLH (�������������)
	X  - ������ � ������� sys_from, �����
    Y  - ������� � ������� sys_from, �����
    Z  - ������ � ������� sys_from, �����
	sys_from - �������, �� ������� ���������� ���������
	B	- ������ � ������� sys_to, �������
	L	- ������� � ������� sys_to, �������
	H	- ������ � ������� sys_to, �����	
	sys_to - �������, � ������� ����� ���������						   */
//-----------------------------------------------------------------------
void ConvertUserXYZ_to_UserBLH(double X, double Y, double Z, eGeodeticSystem sys_from,
					   double *B, double *L, double *H, eGeodeticSystem sys_to)
{
  //XYZ   sys_to -> XYZ  sys_from 
  double x_user=0.0, y_user=0.0, z_user=0.0;
  ConvertXYZ(X, Y, Z, sys_from,&x_user, &y_user, &z_user, sys_to);

  
  //XYZ sys_to -> BLH sys_to
  ConvertXYZtoBLH(x_user, y_user, z_user, B, L, H, sys_to);

}

//-----------------------------------------------------------------------
/*	������� �������������� ��������� �� BLH (�������������) � XYZ (�������������)
	B	- ������ � ������� sys_from, �������
	L	- ������� � ������� sys_from, �������
	H	- ������ � ������� sys_from, �����
	sys_from - �������, �� ������� ���������� ���������
	X  - ������ � ������� sys_to, �����
    Y  - ������� � ������� sys_to, �����
    Z  - ������ � ������� sys_to, �����	
	sys_to - �������, � ������� ����� ���������							*/
//-----------------------------------------------------------------------
void ConvertUserBLH_to_UserXYZ(double B, double L, double H, eGeodeticSystem sys_from,
					   double *X, double *Y, double *Z, eGeodeticSystem sys_to)
{
  //BLH sys_from -> XYZ sys_from
  double x_user=0.0, y_user=0.0, z_user=0.0;
  ConvertBLHtoXYZ(B, L, H, &x_user, &y_user, &z_user, sys_from);

  //XYZ   sys_to -> XYZ  sys_from  
  ConvertXYZ(x_user, y_user, z_user, sys_from,X, Y, Z, sys_to);
}

//-----------------------------------------------------------------------
/* ������� �������������� ��������� XYZ (�������������, �����) �� 
   ������ ������� � �����������
   X  - ������ � ������� sys_from, �����
   Y  - ������� � ������� sys_from, �����
   Z  - ������ � ������� sys_from, �����	
   sys_from - �������, �� ������� ���������� ���������
   *UX  - ������ � ������� sys_to, �����
   *UY  - ������� � ������� sys_to, �����
   *UZ  - ������ � ������� sys_to, �����	
   sys_to - �������, � ������� ����� ���������							*/
//-----------------------------------------------------------------------
void ConvertXYZ(double X, double Y, double Z, eGeodeticSystem sys_from,
					   double *UX, double *UY, double *UZ, eGeodeticSystem sys_to)
{
  //sys_from -> WGS84
  double x_wgs=0.0, y_wgs=0.0, z_wgs=0.0;
  ConvertUserXYZ_to_WGS84_XYZ(X, Y, Z, &x_wgs, &y_wgs, &z_wgs, sys_from); 

  //WGS84 -> sys_to
  ConvertWGS84_XYZtoUser_XYZ(x_wgs, y_wgs, z_wgs, UX, UY, UZ, sys_to);
}

//-----------------------------------------------------------------------
/*	������� �������������� ��������� BLH (�������������, �������) 
	�� ������ ������� � �����������
	B	- ������ � ������� sys_from, �������
	L	- ������� � ������� sys_from, �������
	H	- ������ � ������� sys_from, �����	
	sys_from - �������, �� ������� ����� ���������	
	B	- ������ � ������� sys_to, �������
	L	- ������� � ������� sys_to, �������
	H	- ������ � ������� sys_to, �����	
	sys_to - �������, � ������� ����� ���������	*/
//-----------------------------------------------------------------------
void ConvertBLH(double B, double L, double H, eGeodeticSystem sys_from,
					   double *UB, double *UL, double *UH, eGeodeticSystem sys_to)
{
  double X=0.0, Y =0.0, Z=0.0;
  //BLH sys_from -> XYZ sys_from
  ConvertBLHtoXYZ(B, L, H, &X, &Y, &Z, sys_from);

   //XYZ   sys_to -> XYZ  sys_from 
  double x_user=0.0, y_user=0.0, z_user=0.0;
  ConvertXYZ(X, Y, Z, sys_from,&x_user, &y_user, &z_user, sys_to);
  
  //XYZ sys_to -> BLH sys_to
  ConvertXYZtoBLH(x_user, y_user, z_user, UB, UL, UH, sys_to);

}

//-----------------------------------------------------------------------
/*	������� �������������� ��������� �� ������ � �������, 
	���������� �������													*/
//-----------------------------------------------------------------------
double RadianToDegree(double rad)
{
    return rad*CRG;
}

//-----------------------------------------------------------------------
/*	������� �������������� ��������� �� �������� � �������, 
	���������� �������													*/
//-----------------------------------------------------------------------
double DegreeToRadian(double degree)
{
	return degree*CGR;
}

//-----------------------------------------------------------------------
/* ������� �������������� �������� � ��������� Angle					*/
//-----------------------------------------------------------------------
void DegreeToAngle(double degree, sAngle *angle)
{
	if( degree < 0.0) 
	{ 
		angle->sign = -1; 
		degree *= angle->sign; 
	}
	else angle->sign = 1; 
	angle->grad = static_cast<int>(Int(degree));
	angle->min  = static_cast<int>(Int((degree - angle->grad)*CGM));
	angle->sec  = (degree - angle->grad - angle->min*CMG)*CGS;
}

//-----------------------------------------------------------------------
/* ������� �������������� ������ � ��������� Angle					   */
//-----------------------------------------------------------------------
void RadianToAngle(double radian, sAngle *angle)
{
	double degree = RadianToDegree(radian);
    DegreeToAngle(degree, angle);
}

//----------------------------------------------------------------------
/* ������� �������������� ��������� Angle � �������, ���������� �������*/
//----------------------------------------------------------------------
double AngleToDegree(sAngle *angle)
{
	return (angle->grad + angle->min*CMG + angle->sec*CSG)*angle->sign;
}

//----------------------------------------------------------------------
/* ������� �������������� ��������� Angle � �������					  */
//-----------------------------------------------------------------------
double AngleToRadian(sAngle *angle)
{
	return DegreeToRadian(AngleToDegree(angle)); 
}


//-----------------------------------------------------------------------
/* ������� �������������� �� ��������, �����, ������ � �������*/
//-----------------------------------------------------------------------
double get_radians_from_gms(char c,int grad, double min, double sec)
{
	
	double rad;// = 0.0;
	rad = DegreeToRadian((double)grad + min/60.0 + sec/3600.0);
	if( c=='S' || c=='W' )//��, ����� 
		rad *=(-1);
	return rad;
}
//-----------------------------------------------------------------------
int AngleToInt(sAngle *angle)
{
	 return angle->sign*(angle->grad*1e+6+angle->min*1e+4+Int(angle->sec*1e+2));
	
}
//-----------------------------------------------------------------------
double IntToRadian(int str)
{
	sAngle angle;
	if(str<0) {angle.sign=-1; str*=(-1);}
	else angle.sign=1;
	angle.grad = (int)Int((double)str*1e-6);
	angle.min = (int)Int((double)((str-angle.grad*1e+6)*1e-4));
	angle.sec = (str-angle.grad*1e+6-angle.min*1e+4)*1e-2;
	return AngleToRadian(&angle);
}

//---------------------------------------------------------------------------
/*	������� �������������� ��������� � ����������� �� ���������� ������� ���������
    ������� ���������: rad - ���������� � ��������
				
*/
//---------------------------------------------------------------------------
QString TextCoord(double *rad)
{
	QString data, stype;
	sAngle angle;
	RadianToAngle(*rad, &angle);
	if(*rad >= 0.0) stype.append(data.sprintf("%03d",angle.grad));
	else stype.append(data.sprintf("-%03d",angle.grad));
	int sec =static_cast<int>(Int( (angle.sec - static_cast<int>(Int(angle.sec))) *10));
	data.sprintf("�%02d'%02d.%02d\"",angle.min,static_cast<int>(Int(angle.sec)),sec);		
	data.insert(0,stype);
	return data;
}
//-----------------------------------------------------------------------
