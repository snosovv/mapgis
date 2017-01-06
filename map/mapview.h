//************************************************************
//                                                            
//						Модуль отображения ГИС "КАРТА"                                
//          Copyright (c) 2014  ОАО "Московское конструкторское бюро "Компас"                         
//                                                            
//                                                            
//  Разработчик: Сафина Л.Р, ведущий инженер-программист                                      
//  Модифицирован: 25 июля 2014                 
//                                                            
//************************************************************
#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QMainWindow>
#include <QScrollArea>
#include "include/MAPAPI.H"


#define MAX_ZOOM 1000
//класс АПС
class points_afs
{
public:
	int id;
	int type;
	QPointF p;
	QString num_sender;
	points_afs(){};
	~points_afs(){};

};


// Окно для отображения карты
class MapGIS : public QWidget
{
    Q_OBJECT
public:
    MapGIS(QWidget * parent = 0);
    ~MapGIS();
	//функция открыти карты
    int  mapOpen(const char *name);
	//открытие дополнительной карты
	int mapAddMap(  const char *name );
	void open(QString File);
	void add(QString File);

	//функция закрытия карты
	void closeMap();
	//фукция удаления АПС
	void delete_all_afs();
    //функция удаления АПС
	void delete_afs(int id);
	//функция установки центра карты
	void set_center(double x, double y); 
	void set_center();
	void set_center_CK42(double x, double y);
	//функция перемещения карты  
	void ChangePos(long int dx,long int dy); 
	void ChangePos20(long int dx,long int dy); 
	void	LessScale(); //уменьшение масштаба
	void	GreateScale(); //увеличение масштаба
	
	//функция зумирования карты
	void set_zoom(double zoom);
	//функция установки масштаба
	void set_real_scale(double scale);
	//функция получения масштаба
	double get_scale();
	//функция получения центра карты
	void get_center(double &x, double &y);
	//функция получения имени файла картограф. информации
	QString  get_file_name();

	//функция отрисовки всей карты в пределах окна
	void all_map_in_win();

	//проверка совместимости проекций карт 
	static bool check_compatibility(const char *name1, const char *name2);

private:
	QTextCodec *MainCodec; //кодек
	QString err;		//текст. ошибки
	QString file_name;	//имя файла
	HINSTANCE LibInst;
	HINSTANCE LibInstFree;
	MAPREGISTER  map;			//формуляр карты
    HMAP	hMap;              // Идентификатор карты
    RECT	RectDraw;          // Область отрисовки карты
	bool scribbling;	//признак перетаскивания карты
	QVector <points_afs> objects; //список АПС
	QPoint lastPoint; //предыдущие координаты мышки 
	double x_center; //координаты центра изображения в пикселях карты
	double y_center; //координаты центра изображения в пикселях карты 

	QRectF btn_left;	//кнопка сдвига влево
	QRectF btn_right;	//кнопка сдвига вправо
	QRectF btn_up;		//кнопка сдвига вверх
	QRectF btn_down;	//кнопка сдвига вниз
	QRectF btn_center;	//кнопка центрирования карты
	QRectF btn_plus;	//кнопка увеличения карты
	QRectF btn_minus;	//кнопка уменьшения карты
	QImage img_left;	//пиктограмма сдвига влево
	QImage img_right;	//пиктограмма сдвига вправо
	QImage img_up;		//пиктограмма сдвига вверх
	QImage img_down;	//пиктограмма сдвига вниз
	QImage img_center;	//пиктограмма центрирования
	QImage img_plus;	//пиктограмма увеличения карты
	QImage img_minus;	//пиктограмма уменьшения карты

	void ChangeScale(float zoom); //смена масштаба
	void find_afs(QPoint x, bool sig=true); //поиск АПС
	
	//функция преобразования пикселей карты в пиксели окна
	void pixel_karta_to_pixel_win(double &x, double &y);
	//функция преобразования пикселей окна в пиксели карты
	void pixel_win_to_pixel_karta(double &x, double &y);		

	//функция получает координаты мыши
	void get_mouse_coord(QPoint pnt);

	void panel(); //панель управления картой
	
protected:	
    void drawContents( QPainter* p, int cx, int cy, int cw, int ch); //отрисовка карты
	void drawObjects( QPainter* p); //отрисовка объектов на карте
	void drawPanel( QPainter* p); //отрисовка панели отображения карты
	//функция событий отрисовки
	void paintEvent( QPaintEvent * event);
    //функция обработки событий мыши
	void mouseMoveEvent(QMouseEvent *event);
	//функция обработки нажатий кнопок мыши
	void mousePressEvent(QMouseEvent *event);
	//функция обработки отжатий кнопок мыши
	void mouseReleaseEvent(QMouseEvent *event);	
	//функция обработки изменения размеров окна
	void resizeEvent( QResizeEvent * event );
	//обработчик кликов по панели управления картой
	void pressPanelBtn(QPoint pnt);
	
signals:
	//сигнал клика мышкой по АПС
	void sig_afs_find(int id_afs);	
	//сигнал получения координат курсора
	void sig_cursor_poisition(QString);
   
};

#endif
