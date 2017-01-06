#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "map/mapview.h"

#define NAME_APP "mapgis"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    MapGIS *GIS_map; //ГИС Панорама
    void write_gis_params(QString map_name, double scale, double x, double y);
    void get_gis_params(QString map_name, double &scale, double &x, double &y);
};

#endif // MAINWINDOW_H
