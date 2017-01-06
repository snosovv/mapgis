//************************************************************
//                                                            
//						������ ����������� ��� "�����"                                
//          Copyright (c) 2014  ��� "���������� ��������������� ���� "������"                         
//                                                            
//                                                            
//  �����������: ������ �.�, ������� �������-�����������                                      
//  �������������: 25 ���� 2014                 
//                                                            
//************************************************************
#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QMainWindow>
#include <QScrollArea>
#include "include/MAPAPI.H"


#define MAX_ZOOM 1000
//����� ���
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


// ���� ��� ����������� �����
class MapGIS : public QWidget
{
    Q_OBJECT
public:
    MapGIS(QWidget * parent = 0);
    ~MapGIS();
	//������� ������� �����
    int  mapOpen(const char *name);
	//�������� �������������� �����
	int mapAddMap(  const char *name );
	void open(QString File);
	void add(QString File);

	//������� �������� �����
	void closeMap();
	//������ �������� ���
	void delete_all_afs();
    //������� �������� ���
	void delete_afs(int id);
	//������� ��������� ������ �����
	void set_center(double x, double y); 
	void set_center();
	void set_center_CK42(double x, double y);
	//������� ����������� �����  
	void ChangePos(long int dx,long int dy); 
	void ChangePos20(long int dx,long int dy); 
	void	LessScale(); //���������� ��������
	void	GreateScale(); //���������� ��������
	
	//������� ����������� �����
	void set_zoom(double zoom);
	//������� ��������� ��������
	void set_real_scale(double scale);
	//������� ��������� ��������
	double get_scale();
	//������� ��������� ������ �����
	void get_center(double &x, double &y);
	//������� ��������� ����� ����� ���������. ����������
	QString  get_file_name();

	//������� ��������� ���� ����� � �������� ����
	void all_map_in_win();

	//�������� ������������� �������� ���� 
	static bool check_compatibility(const char *name1, const char *name2);

private:
	QTextCodec *MainCodec; //�����
	QString err;		//�����. ������
	QString file_name;	//��� �����
	HINSTANCE LibInst;
	HINSTANCE LibInstFree;
	MAPREGISTER  map;			//�������� �����
    HMAP	hMap;              // ������������� �����
    RECT	RectDraw;          // ������� ��������� �����
	bool scribbling;	//������� �������������� �����
	QVector <points_afs> objects; //������ ���
	QPoint lastPoint; //���������� ���������� ����� 
	double x_center; //���������� ������ ����������� � �������� �����
	double y_center; //���������� ������ ����������� � �������� ����� 

	QRectF btn_left;	//������ ������ �����
	QRectF btn_right;	//������ ������ ������
	QRectF btn_up;		//������ ������ �����
	QRectF btn_down;	//������ ������ ����
	QRectF btn_center;	//������ ������������� �����
	QRectF btn_plus;	//������ ���������� �����
	QRectF btn_minus;	//������ ���������� �����
	QImage img_left;	//����������� ������ �����
	QImage img_right;	//����������� ������ ������
	QImage img_up;		//����������� ������ �����
	QImage img_down;	//����������� ������ ����
	QImage img_center;	//����������� �������������
	QImage img_plus;	//����������� ���������� �����
	QImage img_minus;	//����������� ���������� �����

	void ChangeScale(float zoom); //����� ��������
	void find_afs(QPoint x, bool sig=true); //����� ���
	
	//������� �������������� �������� ����� � ������� ����
	void pixel_karta_to_pixel_win(double &x, double &y);
	//������� �������������� �������� ���� � ������� �����
	void pixel_win_to_pixel_karta(double &x, double &y);		

	//������� �������� ���������� ����
	void get_mouse_coord(QPoint pnt);

	void panel(); //������ ���������� ������
	
protected:	
    void drawContents( QPainter* p, int cx, int cy, int cw, int ch); //��������� �����
	void drawObjects( QPainter* p); //��������� �������� �� �����
	void drawPanel( QPainter* p); //��������� ������ ����������� �����
	//������� ������� ���������
	void paintEvent( QPaintEvent * event);
    //������� ��������� ������� ����
	void mouseMoveEvent(QMouseEvent *event);
	//������� ��������� ������� ������ ����
	void mousePressEvent(QMouseEvent *event);
	//������� ��������� ������� ������ ����
	void mouseReleaseEvent(QMouseEvent *event);	
	//������� ��������� ��������� �������� ����
	void resizeEvent( QResizeEvent * event );
	//���������� ������ �� ������ ���������� ������
	void pressPanelBtn(QPoint pnt);
	
signals:
	//������ ����� ������ �� ���
	void sig_afs_find(int id_afs);	
	//������ ��������� ��������� �������
	void sig_cursor_poisition(QString);
   
};

#endif
