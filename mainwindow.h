#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QDateTime>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QFile>
#include <QResizeEvent>
#include <QCloseEvent>
#include <QUrl>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

    void resizeEvent(QResizeEvent *);
    static string filePath;
    static QString url;
    static QString temFile;

private slots:
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent*);
    void doProcessReadRead();
    void doProcessFinish();
    //void doProcessError(QNetworkReply::NetworkError);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QFile *myFile;
    void Init();
};
#endif // MAINWINDOW_H
