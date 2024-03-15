#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this)) //add
    , networkManager(new QNetworkAccessManager(this)) //add
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene); //add
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onTileLoaded);

    // Load the specified tile
    loadTile("http://wprd03.is.autonavi.com/appmaptile?style=6&x=5&y=1&z=3");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // 示例：加载特定瓦片
    // loadAndDisplayTile(427289, 227618, 19);
    qDebug()<< "click";
}

void MainWindow::loadTile(const QString &url) {
    QNetworkRequest request(url);
    networkManager->get(request);
}

void MainWindow::onTileLoaded(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QPixmap pixmap;
        if (pixmap.loadFromData(data)) {
            scene->addPixmap(pixmap);
            scene->setSceneRect(pixmap.rect());
        }
    }
    reply->deleteLater();
}

