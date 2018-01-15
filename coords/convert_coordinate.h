#ifndef  _CONVERT_COORDINATE_H
#define  _CONVERT_COORDINATE_H

#include <QString>
//-----------------------------------------------------------------------

//Перечисление для индексирования в массиве spheroid GEO_SYSTEM_CONVERT
typedef enum {mWGS_84 = 0,
			  mPZ_90 = 1,
              mCK_42 = 2,			 
			  mCK_95 = 3,
	      mPZ_90_02 = 4}eGeodeticSystem;//модель Земли 

//структура описания угла
typedef struct sAngle  
{
  int grad;     // градусы
  int min;      // минуты
  double sec;   // секунды
  int sign;     // знак (+1 - север или восток или -1 - юг или запад)
  sAngle ():grad(0),sec(0.0),sign(1){grad=0;min=0;sec=0.0;sign=1; };
}sAngle;

//структура описания параметров сфероида/модели Земли
typedef struct _spheroid
{
    double a;   //a (экваториальный радиус сфероида)
    double e2;  //e (квадрат 1-ого эксцентреситета меридионального сечения)

    //смещение центра в метрах, линейные элементы трансформирования относительно WGS-84
	//delta = смещение относительно центра земли - смещение WGS_84   
	double dX;  //   
    double dY;  //
    double dZ;  //

    //угол поворота в угловых секундах относительно WGS-84 в угловых секундах
	//Ang = угол поворота + угол поворота WGS_84
	double AngX;//omega_x 
    double AngY;//omega_y
    double AngZ;//omega_z

	double M; //дифференциальное различие линейных масштабов относительно WGS-84

	char name[10];//название системы координат
}spheroid;

//-----------------------------------------------------------------------
/*								Константы								*/

const unsigned int _KOL_GEO_SYS = 5; //количество систем координат

//-----------------------------------------------------------------------
/*							Глобальные переменные						*/

extern spheroid GEO_SYSTEM_CONVERT[_KOL_GEO_SYS]; //массив параметров систем кординат

//-----------------------------------------------------------------------

//Примечание: XYZ - прямоугольные координаты, метры
//			  BLH - геодезические координаты, радианы

//Функция преобразования координат из BLH в XYZ
extern void ConvertBLHtoXYZ(double B, double L, double H, 
							double *X, double *Y, double *Z, 
							double a, double e2);

extern void ConvertBLHtoXYZ(double B, double L, double H, 
							double *X, double *Y, double *Z, 
							eGeodeticSystem sys);

//Функция преобразования координат из XYZ в BLH
extern void ConvertXYZtoBLH(double X, double Y, double Z, 
							double *B, double *L, double *H, 
							double a, double e2);

extern void ConvertXYZtoBLH(double X, double Y, double Z, 
							double *B, double *L, double *H,
							eGeodeticSystem sys);

//Функция преобразования координат XYZ из WGS_84 в данную систему коорд.
extern void ConvertWGS84_XYZtoUser_XYZ(double X, double Y, double Z, 
								double *UX, double *UY, double *UZ, eGeodeticSystem sys);

//Функция преобразования координат XYZ из данной системы коорд. в WGS_84
extern void ConvertUserXYZ_to_WGS84_XYZ(double X, double Y, double Z, 
								double *UX, double *UY, double *UZ, eGeodeticSystem sys);

//Функция преобразования координат из XYZ (прямоугольные) в BLH (геодезические)
extern void ConvertUserXYZ_to_UserBLH(double X, double Y, double Z, eGeodeticSystem sys_from,
					   double *B, double *L, double *H, eGeodeticSystem sys_to);

//Функция преобразования координат из BLH (геодезические) в XYZ (прямоугольные)
extern void ConvertUserBLH_to_UserXYZ(double B, double L, double H, eGeodeticSystem sys_from,
					   double *X, double *Y, double *Z, eGeodeticSystem sys_to);

//Функция преобразования координат XYZ (прямоугольные, метры) из 
//данной системы в необходимую
extern void ConvertXYZ(double X, double Y, double Z, eGeodeticSystem sys_from,
					   double *UX, double *UY, double *UZ, eGeodeticSystem sys_to);

//Функция преобразования координат BLH (геодезические, радианы) 
//из данной системы в необходимую
extern void ConvertBLH(double B, double L, double H, eGeodeticSystem sys_from,
					   double *UB, double *UL, double *UH, eGeodeticSystem sys_to);

//Функция преобразование координат из радиан в градусы, 
//возвращает градусы
extern double RadianToDegree(double rad);

//Функция преобразования координат из градусов в радианы, 
//возвращает радаины	
extern double DegreeToRadian(double degree);

//Функция преобразования градусов к структуре Angle	
extern void DegreeToAngle(double degree, sAngle *angle);

//Функция преобразования радиан к структуре Angle
extern void RadianToAngle(double radian, sAngle *angle);

// Функция преобразования структуры Angle в градусы					  
extern double AngleToDegree(sAngle *angle);

// Функция преобразования структуры Angle в радианы					  
extern double AngleToRadian(sAngle *angle);

// Функция преобразования из градусов, минут, секунд в радианы
extern double get_radians_from_gms(char c,int grad, double min, double sec=0.0);

extern int AngleToInt(sAngle *angle);
extern double IntToRadian(int str);

//функция преобразования координат к текстовому виду
extern QString TextCoord(double *rad);
//-----------------------------------------------------------------------

#endif //CONVERT_COORDINATE_H
