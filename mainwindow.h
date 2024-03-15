#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void onTileLoaded(QNetworkReply *reply);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QNetworkAccessManager *networkManager;
    void loadTiles(int zoomLevel);
    void loadTile(int x, int y, int z);


};
#endif // MAINWINDOW_H
