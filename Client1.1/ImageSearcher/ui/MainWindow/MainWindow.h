#pragma once

#include "FramelessWidget.h"
#include <QWidget>
#include <QTcpSocket>
namespace Ui { class MainWindow; };

namespace imagesearcher 
{
    class MainWindow : public FramelessWidget
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = Q_NULLPTR);
        ~MainWindow();

    private:
        // ��ʼ������
        void initUi();
        // ��ʼ���źŲ�
        void initConnection();
        // ��������
        void sendRequest(const QString& action, const QString& filePath, const QString& depends);
        // ��������
        void recieveFromSever();
        // show result 
        void showResult(const QStringList paths);
    private:
        Ui::MainWindow *ui;

        QString m_curImagePath{};
        QTcpSocket m_socket;
    };
}


