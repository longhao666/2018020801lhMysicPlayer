#include "widget.h"
#include "ui_widget.h"
#include <QUrl>
#include <QDebug>
#include <QDir>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->lhMusicPlayerInit();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::lhMusicPlayerInit()
{
    playCount = 1;

//    playerSong = "../../lhMusicSong/刘惜君 - 我很快乐.mp3";
//    playerSong = "D:/QtProject/QtMusic/lhMusicSong/来了.mp3";
//    playerSong = "D:/QtProject/QtMusic/lhMusicSong/胡彦斌 - 为你我受冷风吹";
//    playerSong = "MKJ - Time.mp3";
//    QString playerSong1 = "D:/QtProject/QtMusic/lhMusicSong/好歌/庄心妍 - 走着走着就散了.mp3";
//    QString playerSong2 = "D:/QtProject/QtMusic/lhMusicSong/好歌/薛之谦 - 演员.mp3";
//    QString playerSong3 = "D:/QtProject/QtMusic/lhMusicSong/好歌/OutaMatic,Charlie Puth,Selena Gomez - We Dont Talk Anymore (OutaMatic Remix).mp3";
//    QString playerSong4 = "D:/QtProject/QtMusic/lhMusicSong/好歌/胡彦斌 - 为你我受冷风吹.mp3";
//    playerSong = "D:/QtProject/QtMusic/lhMusicSong/好歌/胡彦斌 - 为你我受冷风吹.mp3";

//    playerListSong << playerSong1 << playerSong2 << playerSong3 << playerSong4;
    //qDebug() << playerListSong;
//    qDebug() << playerListSong.length();
//    qDebug() << playerListSong.size();
    this->getFilePath();
    //sleep(1);
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setMedia(QUrl::fromLocalFile(playerListSong[playCount]));
//    mediaPlayer->setMedia(QUrl::fromLocalFile(playerListSong[playCount+1]));
   // mediaPlayer->setMedia(QUrl(playerSong));
    mediaPlayer->setVolume(30);
    ui->soundHorizontalSlider->setValue(30);
    //mediaPlayer->play();


}


void Widget::on_playPushButton_clicked()
{
    if(ui->playPushButton->text() == "播放") {
        //qDebug("666");
        mediaPlayer->play();
        ui->playPushButton->setText(tr("暂停"));
    }else {
        //qDebug("6667766");
        mediaPlayer->pause();
        //mediaPlayer->stop();
        ui->playPushButton->setText(tr("播放"));
    }
}

void Widget::on_proPushButton_clicked()
{
    mediaPlayer->stop();
    playCount--;
    if(playCount == -1) {
        playCount = playerListSong.length() - 1;
    }
    mediaPlayer->setMedia(QUrl(playerListSong[playCount]));
    mediaPlayer->play();
    ui->playPushButton->setText(tr("暂停"));
}

void Widget::on_nextPushButton_clicked()
{
    mediaPlayer->stop();
    playCount++;
    if(playCount == playerListSong.length()) {
        playCount = 0;
    }
    mediaPlayer->setMedia(QUrl(playerListSong[playCount]));
    mediaPlayer->play();
    ui->playPushButton->setText(tr("暂停"));
}

void Widget::on_soundHorizontalSlider_valueChanged(int value)
{
    mediaPlayer->setVolume(value);
}

/**
 * @brief Widget::on_pushButton_clicked
 * 遍历目录下所有文件，并过滤后缀名，最后打印完整的文件路径直接上代码：
 */
void Widget::on_pushButton_clicked()
{
    this->getFilePath();
}

/**
 * @brief Widget::getFilePath
 * 遍历目录下所有文件，并过滤后缀名，最后打印完整的文件路径直接上代码：
 */
void Widget::getFilePath()
{
    ui->songListWidget->clear();
    playerListSong.clear();
    lyricList.clear();
    QString path = "D:/QtProject/QtMusic/lhMusicSong/好歌";
    //qDebug("jinle");
    QDir dir(path);
    //判断路径是否存在
    if(!dir.exists()) {
        qDebug("113");
        return ;
    }

    QStringList filters;
    filters << QString("*.mp3");
    dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
    dir.setNameFilters(filters); //设置文件名称过滤器，只为filters格式（后缀为.jpeg等图片格式）

    int dirCount = dir.count();
    if(dirCount <= 0) {
        return ;
    }

//    QStringList stringList;
//    //获取分隔符
//    //QChar separator = QDir::separator();
//    QChar separator = QChar('/');
//    if(!path.contains(separator)) {
//        separator = QChar('\\');
//    }
//    QChar last_char = path.at(path.length()-1);
//    if(last_char == separator) {
//        separator = QChar();
//    }

//    foreach(QFileInfo mfi ,dir.entryInfoList()) {
//        if(mfi.isFile()) {
//            QString file_path = path + separator +  mfi.fileName();
//            stringList.append(file_path);
//        }
//    }

//    for (int i=0; i< stringList.size(); ++i) {
//        qDebug() << stringList.at(i);
//    }

    /**
     * 上面的替换成下面这个,添加到歌曲列表中
     */
    //QStringList stringList;
    //获取分隔符
    //QChar separator = QDir::separator();
    QChar separator = QChar('/');
    if(!path.contains(separator)) {
        separator = QChar('\\');
    }
    QChar last_char = path.at(path.length()-1);
    if(last_char == separator) {
        separator = QChar();
    }

    foreach(QFileInfo mfi ,dir.entryInfoList()) {
        if(mfi.isFile()) {
            QString file_path = path + separator +  mfi.fileName();
            playerListSong.append(file_path);
            // 这里还添加一个歌名列表
            lyricList.append(mfi.fileName());
        }
    }

//    for (int i=0; i< playerListSong.size(); ++i) {
//        qDebug() << playerListSong.at(i);
//    }

//    for (int i=0; i< lyricList.size(); ++i) {
//        //qDebug() << lyricList.at(i);
//        ui->songListWidget->addItem(lyricList[i]);
//    }
    ui->songListWidget->addItems(lyricList);
}


void Widget::on_songListWidget_currentRowChanged(int currentRow)
{
    qDebug()<<currentRow;
    for(int i=0; i==currentRow; i++) {
        qDebug("jinlema");
        mediaPlayer->stop();
        playCount = currentRow;
        mediaPlayer->setMedia(QUrl(playerListSong[playCount]));
        mediaPlayer->play();
        ui->playPushButton->setText(tr("暂停"));
    }
}
