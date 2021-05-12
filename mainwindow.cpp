#include "mainwindow.h"
#include "ui_mainwindow.h"

QString MainWindow::url = "https://api.dujin.org/bing/1920.php";
QString MainWindow::temFile = "~BingWallpaper.tem";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    Init();

}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_pushButton_clicked(){
    //文件夹路径
    QString srcDirPath = QFileDialog::getExistingDirectory(
                 this, "选择壁纸存储路径",
                 "/");

    if (srcDirPath.isEmpty())
    {
        return;
    }
    else
    {
        QString urlMobile = "https://api.dujin.org/bing/m.php";
        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyyMMddhhmm");
        QString fileName = srcDirPath +"/"+ current_date+ ".jpg";      //将文件与路径拼接
        //QString url0 = url + "?abc=" + current_date;
        //QString fileNameMobile = srcDirPath+"/"+ current_date+ "Mobile.jpg";

        if (QFile::copy(temFile,fileName)){

            QMessageBox::information(this,"提示","下载完成!");//QMessageBox::Yes);

        }

    }
}

void MainWindow::resizeEvent(QResizeEvent *event){

    int width = event->size().width();
    int height = event->size().height();
    int labelX= 0;
    int labelY = height-50;
    int buttonX = width-50;
    int buttonY = height-50;
    int widthLabel = width-80;
    int heightLabel2 = height-60;
    ui->label->setGeometry(labelX,labelY,widthLabel,30);
    ui->pushButton->setGeometry(buttonX,buttonY,30,30);
    ui->label_2->setGeometry(0,0,width,heightLabel2);
    QPixmap tem;
    tem.load(temFile);
    tem = tem.scaled(ui->label_2->size(),Qt::KeepAspectRatio);
    ui->label_2->clear();
    ui->label_2->setPixmap(tem);
    ui->label_2->show();
}
void MainWindow::closeEvent(QCloseEvent *event){
    QFile file(temFile);
    file.remove();
}

void MainWindow::Init(){

    myFile = new QFile(this);
    myFile->setFileName(temFile);
    myFile->open(QIODevice::WriteOnly);

    manager = new QNetworkAccessManager(this);
    QNetworkRequest request;//构造一个访问请求
    request.setUrl(QUrl(url));
    reply = manager->get(request);

    //信号连接
    connect(reply,SIGNAL(readyRead()),this,SLOT(doProcessReadRead()));
    connect(reply,SIGNAL(finished()),this,SLOT(doProcessFinish()));
}

//SLOTS
void MainWindow::doProcessReadRead(){

    while (!reply->atEnd()){
        QByteArray bytes = reply->readAll();
        myFile->write(bytes);
    }
}

void MainWindow::doProcessFinish(){
    myFile->close();
    QFont font ("行书", 12, 2);
    ui->label->setFont(font);
    QPixmap tem;
    tem.load(temFile);
    tem = tem.scaled(ui->label_2->size(),Qt::KeepAspectRatio);
    ui->label_2->clear();//清空
    ui->label_2->setPixmap(tem);//加载到Label标签
    ui->label_2->show();//显示
}
//end SLOTS
