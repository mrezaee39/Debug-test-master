#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //////
   // connect(ui->Toggle,SIGNAL(clicked()),this,SLOT(Widget_Color_Change()));
    //connect(this,SIGNAL(bool_status(bool ch)),this,SLOT(Widget_Color_Change(bool ch)));
    connect(this,SIGNAL(can_sent(int)),ui->CAN_Id,SLOT(display(int)));
    connect(this,SIGNAL(can_sent(can_frame)),this,SLOT(show_data_status(can_frame)));
   ui->pushButton->setCheckable(true);
   ui->Hide_Button->setCheckable(true);
   countDown.start(1000); // every 1000 give me a tick

   SecValue=20;
   MinValue=20;
   connect(&countDown,SIGNAL(timeout()),this,SLOT(CountDown_Slot()));
   connect(this,SIGNAL(stop_car()),this,SLOT(Alarm()));

   QFile file(":/csv/CSV/DTC-List.csv");
   QTextStream textStream(&file);
   file.open(QIODevice::ReadOnly);
   qDebug()<<textStream.readLine();

   ui->LOG_1->setText(textStream.readLine());// read first line//


}

int j=0;
int i=0;
int h=0;
 can_frame A;
MainWindow::~MainWindow()
{
    delete ui;
    SecValue=0;
    MinValue=0;
    //connect(ui->User_setting1,SIGNAL(valueChanged(int)),this,SLOT((int)));
}

/* void MainWindow::Widget_Color_Change(bool ch)
{


}*/


//ui->Widget_Color->setStyleSheet("background-color: \"red\"");




void MainWindow::on_pushButton_clicked(bool checked)
{

    if (checked){
    ui->Widget_Color->setStyleSheet("background-color: \"red\"");
    }
   else {
    ui->Widget_Color->setStyleSheet("background-color: \"blue\"");
    }
    qDebug()<<"Toggle is clicked"<<i;
    i++;
}




void MainWindow::on_Hide_Button_toggled(bool checked) // we have git added huhu!
{
    if(checked){
        ui->pushButton->setVisible(false);
    }
    else{
        ui->pushButton->setVisible(true);
    }
}


/*void MainWindow::on_User_setting1_sliderMoved(int position)
{
   ui->progressBar->setValue(position);
   qDebug()<<j;
   j++;
}*/

/*void MainWindow::on_User_setting1_rangeChanged(int min, int max)
{
    //ui->progressBar->setValue(position);
    qDebug()<<max;
    qDebug()<<min;

}*/

void MainWindow::on_User_setting1_valueChanged(int value)
{
    ui->progressBar->setValue(value);
    ui->lcdNumber->display(value);
    qDebug()<<value;

}


void MainWindow::on_pushButton_2_clicked()
{

   A.can_id =0x50;
   A.can_dlc=8;
   A.data[0]=0b10011110;
   A.data[1]=0b11011101;

  // qDebug()<<"hex is : "<<A.data[0];
  //emit can_sent(A.data[0]);
   emit can_sent(A);

}

void MainWindow::show_data_status(can_frame A)
{
    // deviding the message area :
    static int A0_0=A.data[0] & 0xF; // 1 -> 0b00001111 means just to take first lsb bits
    static int A0_1=(A.data[0] >> 4) & 0xF; //2
    static int A1_0=A.data[1] & 0xF; //3
    static int A1_1=(A.data[1] >> 4) & 0xF; //4

    static QString data_1;
    static QString data_2;
    static QString data_3;
    static QString data_4;
    static QString id;
    data_1.setNum(A0_0,16);//convert from int to hex string
    data_2.setNum(A0_1,16);
    data_3.setNum(A1_0,16);//convert from int to hex string
    data_4.setNum(A1_1,16);
    id.setNum(A.can_id,16);

    ui->data_1->setText(data_1);
    //ui->data_2->setText(data_2);
    ui->data_3->setText(data_3);
    ui->data_4->setText(data_4);
    ui->msg_Id->setText(id);
    qDebug()<<A.data[0];

    if (A0_0==0xE||A0_1==0xE||A1_0==0xE||A1_1==0xE){
         ui->Widget_Color->setStyleSheet("background-color: \"violet\"");
    }

    //ui->data_1->setNum(A.data[0]);
}

void MainWindow::CountDown_Slot()
{

  if (SecValue==0&&MinValue!=0)
  {
      MinValue--;
      SecValue=59;
   }
  else if(SecValue!=0&&MinValue!=0)
 {
      SecValue--;
 }
  else if(SecValue==0&&MinValue==0){
      MinValue=0;
      SecValue=0;
      emit stop_car();
  }
 // qDebug()<<MinValue<<SecValue;
  ui->Min->setNum(MinValue);
  ui->Sec->setNum(SecValue);



}

void MainWindow::Alarm()
{
    qDebug()<<"stop";
  //  MinValue=0;
    //SecValue=0;

}


static int O=0;

    void MainWindow::on_pushButton_3_clicked()
{
   if (O < 10)
   { ++O;}
    ui->usersetting->setNum(O);
}


void MainWindow::on_pushButton_4_clicked()
{
    if (-10< O)
    {--O;}
    ui->usersetting->setNum(O);
}

void MainWindow::devision(qint8 A)
{   //char data_1;
    //char data_2;

    // deviding the message area :
   int A0_0=A & 0xF; // 1 -> 0b00001111 means just to take first lsb bits
   int A0_1=(A >> 6) & 0b01; //2

   // data_1.setNum(A0_0,16);
    //data_1.setNum(A0_1,16);

  qDebug()<<"A0_0 is :"<<A0_0;
  qDebug()<<"A0_1 is :"<<A0_1;

}
void MainWindow::on_data_clicked()
{
    qint8 B = 0x45;//2

    devision(B);
}
