#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GIS_map = 0;

    GIS_map = new MapGIS();
    //    GIS_map->open("c:/QtPrj/mapgis/gismap/Moscow/osm3d/RU-MOW-3d.sit");
    GIS_map->open("c:/QtPrj/mapgis/gismap/Moscow/ru-mow/RU-MOW.sit");

    this->setCentralWidget(GIS_map);

    double scale =0.0; double x=0.0; double y=0.0;
    get_gis_params(GIS_map->get_file_name(), scale, x, y);
    if(x != 0.0 && y != 0.0)
    {

        GIS_map->set_real_scale(scale);
        GIS_map->set_center_CK42(x,y);
    }
    else
        GIS_map->set_center();

    GIS_map->update();
}

MainWindow::~MainWindow()
{
    if(GIS_map)
    {
        double x = 0.0, y = 0.0;
        GIS_map->get_center(x,y);
        write_gis_params(GIS_map->get_file_name(), GIS_map->get_scale(), x, y);

        GIS_map->closeMap();
        delete GIS_map;
    }

    delete ui;
}

void MainWindow::write_gis_params(QString map_name, double scale, double x, double y)
{
    if(map_name.isEmpty()) return;
    QSettings settings(NAME_APP,"inc");
    settings.beginGroup(map_name);
    settings.setValue("scale",scale);
    settings.setValue("x",x);
    settings.setValue("y",y);
    settings.endGroup();
}

void  MainWindow::get_gis_params(QString map_name, double &scale, double &x, double &y)
{
    QSettings settings(NAME_APP,"inc");
    settings.beginGroup(map_name);
    scale = settings.value("scale",0.0).toDouble();
    x = settings.value("x",0.0).toDouble();
    y = settings.value("y",0.0).toDouble();
    settings.endGroup();
}
