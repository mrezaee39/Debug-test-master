#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
struct can_frame {
    int    can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    int    can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    int    data[8];
};
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

       void on_pushButton_clicked(bool checked);

       void on_Hide_Button_toggled(bool checked);

     //  void on_User_setting1_sliderMoved(int position);

       void on_User_setting1_valueChanged(int value);

       void on_pushButton_2_clicked();

       void show_data_status(can_frame);

       void CountDown_Slot();

       void Alarm();


       void on_pushButton_3_clicked();

       void on_pushButton_4_clicked();

       void devision(qint8 A);

       void on_data_clicked();

signals:
       void can_sent(can_frame);
       void stop_car();

private:
    Ui::MainWindow *ui;

    QTimer countDown;
    int SecValue;
    int MinValue;

};
#endif // MAINWINDOW_H
