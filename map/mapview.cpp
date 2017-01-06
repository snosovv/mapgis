#include <QMessageBox>
#include <QLayout>
#include <QApplication>
#include <QMenuBar>
#include <QStatusBar>
#include <QFiledialog>
#include <QPainter>
#include <QTextCodec>
#include <QMainWindow>
#include <QPaintDevice>
#include <QScrollBar>
#include <QImage>
#include <QPixmap>
#include <QPicture>
#include <QPaintEvent>
#include "mapview.h"
#include "coords/convert_coordinate.h"
#include <math.h> 
#include "coords/constant.h"

#ifdef WIN32API
#define LIBMAPACCESNAME "gisacces.dll"
#define LIBMAPACCESFREE "MYDLL.DLL"
#else
#define LIBMAPACCESNAME "libqdmapacces.so"
#endif

//=======================================================================================
MapGIS::MapGIS(QWidget * parent)
          :QWidget(parent)
{
    MainCodec = QTextCodec::codecForName("CP1251");
    hMap = 0;
    LibInst = 0;
	LibInstFree = 0;
	scribbling = false;
	setMouseTracking(true);
    setWindowTitle("ГИС Карта");
	x_center =0;
	y_center =0;
	panel();
   // setMinimumSize(600, 400);
}
//=======================================================================================
// Деструктор
//=======================================================================================
MapGIS::~MapGIS()
{
	if (hMap)
	{
		void (WINAPI * lpmapfn)(int);
		(FARPROC&) lpmapfn = ::GetProcAddress(LibInst,"mapCloseData");
		(*lpmapfn)(hMap);
		hMap = 0;
	}
	if (LibInst != 0)
	{
		::FreeLibrary(LibInst);
		LibInst = 0;
	}

	if (LibInstFree != 0)
	{
		::FreeLibrary(LibInstFree);
		LibInstFree = 0;
	}
}
//=======================================================================================
void  MapGIS::paintEvent( QPaintEvent * event)
{
	QPainter p;
    p.begin(this);
    drawContents(&p, ((QPaintEvent *)event)->rect().left(), ((QPaintEvent *)event)->rect().top(),
                 ((QPaintEvent *)event)->rect().right() - ((QPaintEvent *)event)->rect().left() + 1, 
		 ((QPaintEvent *)event)->rect().bottom() - ((QPaintEvent *)event)->rect().top() + 1);
    p.end();    
}
//=======================================================================================
// Перерисовка окна
//=======================================================================================
void MapGIS::drawContents( QPainter* p, int cx, int cy, int cw, int ch)
{
   if (hMap)
   {
      RectDraw.left = x_center - cw / 2 ;
      RectDraw.top  = y_center - ch / 2 ;
      RectDraw.right  = x_center + cw / 2;
      RectDraw.bottom = long(y_center) + ch / 2;
      
	  int dibsize = sizeof(BITMAPINFOHEADER) +
                   (long)sizeof(RGBQUAD)*256L;
 
	  char *lpImage = (char *)::AllocateTheMemory(cw * ch * 4 + dibsize);
      memset(lpImage, 0xff, cw * ch * 4 + dibsize);

	  BITMAPINFOHEADER *lpDibInfo = (BITMAPINFOHEADER *)lpImage;
	  lpDibInfo->biSize          = sizeof(BITMAPINFOHEADER);
      lpDibInfo->biWidth         = cw;
      lpDibInfo->biHeight        = ch;
      lpDibInfo->biPlanes        = 1;
      lpDibInfo->biBitCount      = (unsigned short)(8 * 4);
      lpDibInfo->biCompression   = BI_RGB;
      lpDibInfo->biSizeImage     = (long)cw*(long)ch*4;
      lpDibInfo->biXPelsPerMeter = 0;
      lpDibInfo->biYPelsPerMeter = 0;
      lpDibInfo->biClrUsed       = 256;
      lpDibInfo->biClrImportant  = 0; 
	  char *lpBits = lpImage + dibsize;

	  long int (WINAPI * lpmapfn2)(HMAP, BITMAPINFOHEADER *,
                                       char *, RECT *);
      (FARPROC&) lpmapfn2 = ::GetProcAddress(LibInst,"mapPaintToDib");
      (*lpmapfn2)(hMap, lpDibInfo, lpBits, &RectDraw);

	  char *string = (char *)AllocateTheMemory(cw * 4);
      for (int i = 0; i < ch/2; i++)
	  {
		char *pointE  = lpBits + (ch - i - 1) * cw * 4;
        char *pointB  = lpBits + i * cw * 4;


		memcpy(string, pointB, cw * 4);
        memcpy(pointB, pointE, cw * 4);
        memcpy(pointE, string, cw * 4);
	  }
      FreeTheMemory(string);

	  QImage img((uchar *) lpBits, cw, ch, QImage::Format_RGB32);	  
      p->drawImage(cx, cy, img, 0, 0, cw, ch);
	  FreeTheMemory(lpImage);

	  drawObjects(p);
	  drawPanel(p);
   }
   else
   {	
	    int border = 5;
		QRectF rectangle(border, border, cw-border*2, ch-border*2);	
		QBrush brush(palette().color(QWidget::backgroundRole())); //цвет фона 
		p->fillRect (0,0,cw,ch,brush);		
		p->drawRect(rectangle);
        p->drawText(rectangle, Qt::AlignCenter, err.toLatin1().data());
   }
};
//=======================================================================================
//открытие карты
//=======================================================================================
int MapGIS::mapOpen(  const char *name )
{
  char        drive[10];
  char        dir[MAX_PATH];
  char        namefile[MAX_PATH];
  char        extname[10];
  
   if (hMap)
   {	  
			void (WINAPI * lpmapfn)(int);
			(FARPROC&) lpmapfn = ::GetProcAddress(LibInst,"mapCloseData");
			(*lpmapfn)(hMap);
			hMap = 0;
	 
   }

  SplitThePath(name, drive, dir, namefile, extname);

  if ((stricmp(extname,".map") == 0) || (stricmp(extname,".sit") == 0) || 
      (stricmp(extname,".rsw") == 0) || (stricmp(extname,".mtw") == 0))
  {
		HMAP (WINAPI * lpmapfn)(const char *, int);
	#ifdef UNICODE
		TCHAR tname[MAX_PATH];
		StringToUnicode(LIBMAPACCESNAME,tname,sizeof(tname));

		TCHAR tnamefree[MAX_PATH];
		StringToUnicode(LIBMAPACCESFREE,tnamefree,sizeof(tnamefree));
	#endif

		if (LibInst == 0)
	#ifdef UNICODE
		  LibInst = ::LoadLibrary(tname);
		  LibInstFree = ::LoadLibrary(tnamefree);
	#else
		  LibInst = ::LoadLibrary(LIBMAPACCESNAME);
          LibInstFree = ::LoadLibrary(LIBMAPACCESFREE);
	#endif
		if (LibInstFree == 0) 
		{
			char mess[MAX_PATH];

			sprintf(mess, "Библиотека %s не найдена!",  LIBMAPACCESFREE);
			QMessageBox::critical(0, MainCodec->toUnicode("Ошибка!"), MainCodec->toUnicode(mess), MainCodec->toUnicode("Да"));
			return 0;
		}
		
		void (WINAPI * lpfreefn)();
        (FARPROC&) lpfreefn = ::GetProcAddress(LibInstFree,"_MapWorkSetFree");
		(*lpfreefn)();
		
		
		if (LibInst == 0) 
		{
		   char mess[MAX_PATH];

		   sprintf(mess, "Библиотека %s не найдена!",  LIBMAPACCESNAME);
		   QMessageBox::critical(0, MainCodec->toUnicode("Ошибка!"), MainCodec->toUnicode(mess), MainCodec->toUnicode("Да"));
		   return 0;
		}
		//hMap = mapOpenData("WMTS#Type=UTMS&IP=http://khm.google.com/kh/v=145&hl=ru&ID1=GoogleSat&Name1=GoogleSat&Matrix=urn:ogc:def:wkss:OGC:1.0:GoogleMapsCompatible",0);
		(FARPROC&) lpmapfn = ::GetProcAddress(LibInst, "mapOpenData");
		hMap = (*lpmapfn)(name, /*GENERIC_READ*/0);
  }

   if (hMap)
   {

	    LISTREGISTER  sheet;
		//Запросить паспортные данные векторной карты
		mapGetMapInfo(hMap,1,&map, &sheet);  
		if( map.EllipsoideKind != KRASOVSKY42 && map.EllipsoideKind != WGS_84 && map.EllipsoideKind!= 45/*на шаре WGS84*/)
		{
            QMessageBox::critical(0,"Предупреждение",
            "Система координат карты не поддерживается.\nМестоположение может быть отображено неточно.", "ОК");
		}
		setAttribute(Qt::WA_NoBackground);		
  }
  else 
  {
	  err = QString("Не удалось открыть файл: %1.\n Файл поврежден или имеет неверный формат.").arg(name);
	  file_name.clear();
   }

 //  update();
   return 0;
};
//=======================================================================================
//открытие дополнительной карты
//=======================================================================================
int MapGIS::mapAddMap(  const char *name )
{
	 if (!hMap) return -1;
	char        drive[10];
	char        dir[MAX_PATH];
	char        namefile[MAX_PATH];
	char        extname[10];
	SplitThePath(name, drive, dir, namefile, extname);

	if ((stricmp(extname,".sit") == 0) || (stricmp(extname,".rsw") == 0) || (stricmp(extname,".mtw") == 0))
	{
		
		if(mapAppendData(hMap, name, /*GENERIC_READ*/0)==0)	
		{
            QMessageBox::critical(0,"Ошибка",
            "Добавить дополнительную карту не удалось.", "ОК");
		}
		
	}
	//update();
	return 0;
}
//=======================================================================================
bool MapGIS::check_compatibility(const char *name1,const char *name2)
{
	MAPREGISTER  map1;
	LISTREGISTER sheet1;
	mapGetMapInfoByName(name1, 0, &map1, &sheet1);
	MAPREGISTER  map2;
	LISTREGISTER sheet2;
	mapGetMapInfoByName(name2, 0, &map2, &sheet2);
	if(map1.MaterialProjection == map2.MaterialProjection)
	{
		return true;
	}
	return false;
}
//=======================================================================================
QString  MapGIS::get_file_name()
{
	return file_name;
}
//=======================================================================================
void  MapGIS::closeMap()
{
	if (hMap!=0)
	{
		void (WINAPI * lpmapfn)(int);
		#ifdef WIN32API
			(FARPROC&) lpmapfn = ::GetProcAddress(LibInst,"mapCloseData");
		#else
			(void *)lpmapfn = dlsym((void *)LibInst, "mapCloseData");
		#endif
		(*lpmapfn)(hMap);
		hMap=0;
	}
}
//=======================================================================================
//отклик на кнопку "-", ">"
void MapGIS::LessScale()
{
	if(hMap)
	{
		long int mapW, mapH;
		void (WINAPI * lpmapfn1)(HMAP, long int *, long int *);
		(FARPROC&) lpmapfn1 = ::GetProcAddress(LibInst,"mapGetPictureSize");
		(*lpmapfn1)(hMap, &mapW, &mapH);
		if(mapW < this->width() && mapH < this->height())  return;

		ChangeScale(0.5);			
	}
}
//=======================================================================================
//отклик на кнопку "+", "<" 
void MapGIS::GreateScale( )
{
	if(hMap ==0) return;
    ChangeScale(2);			
}
//=======================================================================================
void MapGIS::ChangeScale(float zoom)
{	
    // если карта не открыта, тогда менять масштаб карты бессмысленно 
	if (hMap == 0) return;
	long int X,Y;
	long int mapW, mapH;
	

	void (WINAPI * lpmapfn1)(HMAP, long int *, long int *);
	(FARPROC&) lpmapfn1 = ::GetProcAddress(LibInst,"mapGetPictureSize");
	(*lpmapfn1)(hMap, &mapW, &mapH);

	//вычислим текущий центр
	X = x_center;
	Y = y_center;

	/*void (WINAPI * lpmapfn)(HMAP, long int *, long int *, float ch);
	(FARPROC&) lpmapfn = ::GetProcAddress(LibInst,"mapChangeViewScale");
	 (*lpmapfn)(hMap, &X,&Y,zoom);*/

    mapChangeViewScale(hMap, &X,&Y,zoom);
	//qDebug("%d %d %d %f %f",scale,X,Y, mapGetDrawScale(hMap),zoom);
	x_center = (double)X;
	y_center = (double)Y;
   // this->repaint();

   
}
//=======================================================================================
void MapGIS::set_center(double x, double y)
{
	if(hMap ==0) return;
	double lat = 0.0, lng = 0.0, h=0.0;
	lat = DegreeToRadian(x);
	lng = DegreeToRadian(y);
	if( map.EllipsoideKind == KRASOVSKY42)	
		ConvertBLH( lat,lng,h, mWGS_84, &lat,&lng,&h,mCK_42);
	mapGeoToPlane(hMap, &lat, &lng);       
	mapPlaneToPicture(hMap, &lat, &lng);
	x_center = lat;
	y_center = lng;
	//this->repaint();
}
//=======================================================================================
void MapGIS::set_center()
{
   if (hMap)
   {
		long int	mapW, mapH;
		void (WINAPI * lpmapfn)(HMAP, long int *, long int *);

		#ifdef WIN32API
		  (FARPROC&) lpmapfn = ::GetProcAddress(LibInst,"mapGetPictureSize");
		#else
		  (void *)lpmapfn = dlsym((void *)LibInst, "mapGetPictureSize");
		#endif
		  (*lpmapfn)(hMap, &mapW, &mapH);
		x_center = mapW*0.5;
		y_center = mapH*0.5;
   }
}
//=======================================================================================
void MapGIS::set_center_CK42(double x, double y) //радианы СК_42
{

	if(hMap ==0) return;	
	mapGeoToPlane(hMap, &x, &y);       
	mapPlaneToPicture(hMap, &x, &y);
	x_center = x;
	y_center = y;
//	this->repaint();
}
//=======================================================================================
void MapGIS::delete_all_afs()
{
	if(hMap ==0) return;
	objects.clear();
	update();
}
//=======================================================================================
void MapGIS::drawObjects( QPainter* p)
{
	if (hMap == 0) return;
	QImage image(QCoreApplication::applicationDirPath()+"/img/afs_ok.png");
	QImage image_danger(QCoreApplication::applicationDirPath() +"/img/afs_danger.png");	
	
	QFont serifFont("Times", 10, QFont::Bold);
	p->setFont(serifFont);
	QFontMetrics f(serifFont);
	QRectF rectangle;
	
	for(int i=0; i<objects.size(); i++)
	{
		double x3 = objects[i].p.x();
		double y3 = objects[i].p.y();
		mapGeoToPlane(hMap, &x3, &y3);       
		mapPlaneToPicture(hMap, &x3, &y3);
		QRect source(0, 0, image.width(), image.height());
		pixel_karta_to_pixel_win(x3,y3);
		QRectF target((int)(x3), (int)(y3), 16, 16);
        if(objects[i].type == 1) p->drawImage(target,  image, source);
		else p->drawImage(target,  image_danger, source);
		//отрисовка номера станции отправителя в прямоугольнике
		rectangle.setRect((int)(x3)+17,(int)(y3),f.width(objects[i].num_sender)+4,f.height());
		p->fillRect(rectangle,Qt::white);
		p->drawText(rectangle,  Qt::AlignCenter,objects[i].num_sender);			
	}


}
//=======================================================================================
void MapGIS::panel()
{
	int border = 10;	
	int size = 32;
	btn_left.setRect(border, size+border,  size,  size);
	btn_right.setRect(border+2*size, size+border,  size,  size);
	btn_up.setRect(border+size, border,  size,  size);
	btn_down.setRect(border+size, border+2*size,  size,  size);
	btn_center.setRect(border+size, border+size,  size,  size);
	btn_plus.setRect(border+size, border+size*3,  size,  size);
	btn_minus.setRect(border+size, border+size*4,  size,  size);

	img_left.load(QCoreApplication::applicationDirPath()+"/img/left.png");
	img_right.load(QCoreApplication::applicationDirPath()+"/img/right.png");
	img_up.load(QCoreApplication::applicationDirPath()+"/img/up.png");
	img_down.load(QCoreApplication::applicationDirPath()+"/img/down.png");
	img_center.load(QCoreApplication::applicationDirPath()+"/img/center.png");
	img_plus.load(QCoreApplication::applicationDirPath()+"/img/plus.png");
	img_minus.load(QCoreApplication::applicationDirPath()+"/img/minus.png");

}
//=======================================================================================
void MapGIS::drawPanel(QPainter* p)
{	 
	QRect source(0, 0, img_left.width(), img_left.height());
	p->drawImage(btn_left,  img_left, source);	 
	p->drawImage(btn_right,  img_right, source);	
	p->drawImage(btn_up,  img_up, source);	
	p->drawImage(btn_down,  img_down, source);	
	p->drawImage(btn_center,  img_center, source);	
	p->drawImage(btn_plus,  img_plus, source);	
	p->drawImage(btn_minus,  img_minus, source);
}
//=======================================================================================
void  MapGIS::pixel_karta_to_pixel_win(double &x, double &y)
{
	if(hMap ==0) return;
	x=width()*0.5+x-x_center;
	y=height()*0.5+y-y_center;	
}
//=======================================================================================
void  MapGIS::pixel_win_to_pixel_karta(double &x, double &y)
{
	if(hMap ==0) return;
	x = x + x_center - width()*0.5; 
	y=y - height()*0.5 + y_center;	
}
//=======================================================================================
//скроллинг карты по клавишам
void MapGIS::ChangePos(long int dx,long int dy)
{
	if(hMap ==0) return;
	x_center += dx;
	y_center += dy;
	
}
//=======================================================================================
void MapGIS::ChangePos20(long int dx,long int dy)
{
	if(hMap ==0) return;
	dx = dx*this->width()/5;
	dy = dy*this->height()/5;
	ChangePos(dx, dy);
}	
//=======================================================================================
void  MapGIS::mouseMoveEvent(QMouseEvent *event)
{	
	if(hMap ==0) return;
	if ((event->buttons() & Qt::LeftButton) && scribbling) 
	{		
		ChangePos(lastPoint.x()-event->x(),lastPoint.y()-event->y());
		lastPoint = event->pos();
		update();
		return;
	}
	find_afs(event->pos(),false);
	get_mouse_coord(event->pos());

}
//=======================================================================================
void MapGIS::pressPanelBtn(QPoint pnt)
{
	if(btn_left.contains(pnt))  
		ChangePos20(1,0);
	else if (btn_right.contains(pnt)) 
		ChangePos20(-1,0);
	else if (btn_up.contains(pnt))
		ChangePos20(0,1);
	else if (btn_down.contains(pnt))
		ChangePos20(0,-1);
	else if(btn_plus.contains(pnt)) 
		GreateScale();
	else if(btn_minus.contains(pnt)) 
		LessScale();
	else if(btn_center.contains(pnt)) 
	{
		long int  width;
		long int  height;
		mapGetPictureSize( hMap,  &width, &height);
		x_center = width/2;
		y_center = height/2;
	}
	else return;
	update();
}
//=======================================================================================
 void MapGIS::mousePressEvent(QMouseEvent *event)
 {
	 if(hMap ==0) return;
     if (event->button() == Qt::LeftButton) 
	 {
         lastPoint = event->pos();
         scribbling = true;
		 find_afs(event->pos());
		 pressPanelBtn(event->pos());		
		 return;
     }
	 
 }
//=======================================================================================
 void MapGIS::mouseReleaseEvent(QMouseEvent *event)
 {
	 if(hMap ==0) return;
     if (event->button() == Qt::LeftButton && scribbling)
	 {
         ChangePos(lastPoint.x()-event->x(),lastPoint.y()-event->y());
         scribbling = false;
		 return;
     }
 }
 //=======================================================================================
 void MapGIS::find_afs(QPoint x1, bool sig)
{
	if(hMap ==0) return;
	int R = 10;
	for(int i=0; i<objects.size(); i++)
	{
		double x3 = objects[i].p.x();
		double y3 = objects[i].p.y();
		mapGeoToPlane(hMap, &x3, &y3);       
		mapPlaneToPicture(hMap, &x3, &y3);

		double x =x1.x(),y=x1.y();	
		pixel_win_to_pixel_karta(x, y);
		if(x3 <= x+R && x3 >= x-R &&
		   y3 <= y+R && y3 >= y-R)
		{
			if(sig) 
			{
				emit sig_afs_find(objects[i].id);		
			}
			
			setCursor(Qt::OpenHandCursor);			
		}
		else
		{
			setCursor(Qt::ArrowCursor);
		}
				
	}
}
 //=======================================================================================
 //удаление АПС
void MapGIS::delete_afs(int id)
{
	if(hMap ==0) return;
	for(int i=0; i<objects.size(); i++)
	{
		if(objects[i].id==id) 
		{
			objects.remove(i);
			return;
		}
	}	
}
//=======================================================================================
void MapGIS::open(QString File)
{
	if (File.isEmpty()) //если карта не выбрана
	{ 
		err = "Необходимо задать путь к файлу электронных карт."; 
		return; 
	}   
	objects.clear();
	file_name = File;	
	mapOpen(File.toLocal8Bit().data());

}
//=======================================================================================
void MapGIS::add(QString File)
{
	if (File.isEmpty())  return; //если карта не выбрана
	
	QStringList map_list = File.split(";");	
	for(int i=0; i<map_list.size(); i++)	
		if(check_compatibility(file_name.toLocal8Bit().data(), map_list[i].toLocal8Bit().data()))
		mapAddMap(map_list[i].toLocal8Bit().data());
		
	DOUBLEPOINT  point;
	mapSaveMapState(hMap, &point); //Сохранить текущие параметры окна карты в INI-файл карты   
}
//=======================================================================================
void MapGIS::resizeEvent( QResizeEvent * event )
{
    Q_UNUSED(event);
    update();
}
//=======================================================================================
double MapGIS::get_scale()
{	
	if(hMap ==0) return 0.0;	
	return mapGetRealShowScale(hMap);//mapGetDrawScale(hMap);	
}
//=======================================================================================
void MapGIS::set_zoom(double zoom)
{
	ChangeScale(zoom);
}
//=======================================================================================
void MapGIS::set_real_scale(double scale)
{
	if(hMap ==0) return;	
	mapSetRealShowScale(hMap,scale);
}
//=======================================================================================
void MapGIS::get_center(double &x, double &y) 
{ 
	x = x_center; 
	y = y_center;
	if(hMap)
    {
    	mapPictureToPlane(hMap,&x,&y);
    	mapPlaneToGeo(hMap,&x,&y);
    }
	else 
	{
		x = 0.0;
		y = 0.0;
	}
}
//=======================================================================================
void MapGIS::all_map_in_win()
{
	if(!hMap) return;
	
	mapSetRealShowScale(hMap,map.Scale);
	long int  width;
	long int  height;
	mapGetPictureSize( hMap,  &width, &height);
	x_center = width/2;
	y_center = height/2;
	float zoom = (float)this->width()/width;
	if( zoom > (float)this->height()/height)  zoom = (float)this->height()/height;
	mapSetRealShowScale(hMap, map.Scale/zoom);
	mapGetPictureSize( hMap,  &width, &height);
	x_center = width/2;
	y_center = height/2;
	//update();
}
//=======================================================================================
void MapGIS::get_mouse_coord(QPoint pnt)
{
	if(hMap)
	{
		double x = x_center + pnt.x() - this->width() / 2;
		double y = y_center + pnt.y() - this->height() / 2;

		 mapPictureToPlane(hMap,&x, &y);
		 mapPlaneToGeo(hMap,&x, &y);
		 
		if( map.EllipsoideKind == KRASOVSKY42)	
		{
			double h=0.0;
			ConvertBLH( x,y,h,mCK_42,  &x,&y,&h,mWGS_84);				
		}
		emit sig_cursor_poisition(QString("B %1 L %2").arg(TextCoord(&x)).arg(TextCoord(&y)));				
		
	}
}
//=======================================================================================



