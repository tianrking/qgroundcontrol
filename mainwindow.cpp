#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QUrlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this)) //add
    , networkManager(new QNetworkAccessManager(this)) //add
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene); //add
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onTileLoaded);
    loadTiles(3); // 使用缩放级别3
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


void MainWindow::loadTiles(int zoomLevel) {
    // 为了加载4x4的网格，我们设置x和y的范围
    // int startX = 4, endX = 7; // X坐标的起始和结束
    // int startY = 0, endY = 3; // Y坐标的起始和结束

    // 为了加载6x6的网格，我们设置x和y的范围
    int startX = 3, endX = 8; // X坐标的起始和结束
    int startY = 0, endY = 5; // Y坐标的起始和结束

    // 5x6
    startX = 3, endX = 7; // X坐标的起始和结束
    startY = 0, endY = 5; // Y坐标的起始和结束

    for (int x = startX; x <= endX; ++x) {
        for (int y = startY; y <= endY; ++y) {
            loadTile(x, y, zoomLevel);
        }
    }
}

// 修改loadTile函数以接受x, y, z参数
void MainWindow::loadTile(int x, int y, int z) {
    QString url = QString("http://wprd03.is.autonavi.com/appmaptile?style=7&x=%1&y=%2&z=%3")
                      .arg(x).arg(y).arg(z);
    QNetworkRequest request(url);
    networkManager->get(request);
}

void MainWindow::onTileLoaded(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QPixmap pixmap;
        if (pixmap.loadFromData(data)) {
            QUrl url = reply->request().url();
            QUrlQuery query(url);
            int x = query.queryItemValue("x").toInt();
            int y = query.queryItemValue("y").toInt();
            int z = query.queryItemValue("z").toInt(); // 假设URL中包含了z值

            auto item = scene->addPixmap(pixmap);
            item->setPos((x - 4) * 256, (y - 0) * 256); // 调整瓦片的位置

            // 创建文本标签显示瓦片信息
            auto text = new QGraphicsTextItem(QString("x:%1, y:%2, z:%3").arg(x).arg(y).arg(z));
            text->setPos(item->pos()); // 将文本标签放置在瓦片的左上角
            text->setDefaultTextColor(Qt::red); // 设置文本颜色为红色
            scene->addItem(text); // 将文本标签添加到场景中
        }
    }
    reply->deleteLater();
}

