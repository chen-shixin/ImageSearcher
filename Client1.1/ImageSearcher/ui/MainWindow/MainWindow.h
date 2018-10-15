/** @file   MainWindow.h
  * @note   ����������
  * 
  * @brief  
  * @author lesliefish
  * @date   2018/10/15
  */
#pragma once

#include "ui/Public/InfoWidget/InfoTextWidget.h"
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
        // ��ʼ������/������������
        void initCommboxDatas();
        // ��ʼ���źŲ�
        void initConnection();
        // ��������
        void sendRequest(const QString& action, const QString& filePath, const QString& depends);
        // ��������
        void recieveFromSever();
        // ����
        void search();
        // ��������
        void createIndex();
        // ��ʾ�������
        void showResult(const QStringList paths);
        // ѡ���ļ�
        void chooseFile();

    protected:
        virtual void resizeEvent(QResizeEvent* event);
    private:
        Ui::MainWindow *ui;
        InfoTextWidget* infoTextWidget{ nullptr };
        QString m_curImagePath{};
        QTcpSocket m_socket;
    };
}


