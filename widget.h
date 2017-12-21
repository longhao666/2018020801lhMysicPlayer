#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QMediaPlayer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:


    void on_playPushButton_clicked();

    void on_proPushButton_clicked();

    void on_nextPushButton_clicked();

    void on_soundHorizontalSlider_valueChanged(int value);

    void on_pushButton_clicked();

    void on_songListWidget_currentRowChanged(int currentRow);

public:
    void lhMusicPlayerInit();

private:
    void getFilePath();

private:
    Ui::Widget *ui;

    QString playerSong;
    QString playerlyric;
    QMediaPlayer *mediaPlayer;
    QStringList playerListSong;
    QStringList lyricList;

    int playCount;
};

#endif // WIDGET_H
