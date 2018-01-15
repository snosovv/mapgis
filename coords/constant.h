#ifndef CONSTANT_H
#define CONSTANT_H

const double _PI_ = 3.1415926535897932384626433832795;

const double _PI_2 = _PI_/2.0;

const double _PI2_ = _PI_*2.0;

const double CGR =_PI_/180.0; //константа для преобразования градусов в радианы

const double CRG = 180.0/_PI_; //константа для преобразования радиан в градусы

const double CGM = 60.0; //количество минут в одном градусе 
						 
const double CGS = 3600.0; //количество секунд в одном градусе 

const double CMG = 1.0/CGM; //константа для преобразования минут в градусы

const double CSG = 1.0/CGS; //константа для преобразования секунд в градусы

const double MMtoMetr = 1852; //метров в одной морской миле

const double SecHour = 3600.0; //количество секуд в часе

const double KMtoM = 1000.0; //количество метров в километре

const double _G = 9.81; //ускорение свободного падения
 
const double FutInMetr= 3.28; //количество футов в одном метре

#endif //CONSTANT_H
