#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QPalette>
#include <QDebug>
#include <QIcon>
#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include "WarningDlg/warningdlg.h"
#include "FramelessWidget/FramelessWidget.h"
#include "About/AboutDlg.h"

namespace Ui 
{
class MainWindow;
}

class MainWindow : public FramelessWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void runOver();

private:
    void initUi();
    void initConnect();

    //��������
    void sendRequest(QString& strAction, QString& filepath, QString& depends);
    //������
    void readMessage();
    //�������չʾ���������
    void showResult(const QString&);

    //��һ��ͼ���ļ�
    bool openImageFile();
    //��ʾ�򿪵�ͼƬ
    void showChoosedImage(const QString&);

private:
	Ui::MainWindow *ui;
	//�򿪵��ļ�·��
	QString m_openedFilePath;
	WarningDlg* m_warningDlg{ nullptr };
	AboutDlg* m_aboutDlg{nullptr};
	QTcpSocket* m_pSocket;
};

#endif // MAINWINDOW_H
