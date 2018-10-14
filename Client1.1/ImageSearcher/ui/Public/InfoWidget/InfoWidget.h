/** @file   InfoWidget.h
  *
  * @brief  ��Ϣ���ڻ���  ��Ҫ����PC�˸���������
  * @author yulei
  * @date   2018/07/06
  */
#pragma once
#include "FramelessWidget.h"
namespace Ui
{
    class InfoWidget;
};

namespace imagesearcher
{
    class InfoWidget : public FramelessWidget
    {
        Q_OBJECT

    public:
        InfoWidget(QWidget *parent = Q_NULLPTR);
        ~InfoWidget();

        // ���Ľ���ָ��
        QWidget* getCenterPage();
        // ���صײ�������ť
        void hideBottomBtn();
        // ���ô��ڱ���
        void setPageTitle(const QString& title);
        // ����ȷ����ť�ı�
        void setOKBtnText(const QString& text);
        void setOKBtnVisible(bool visible);
        // ����ȡ����ť�ı�
        void setCancelBtnText(const QString& text);
        void setCancelBtnVisible(bool visible);

        void setIgnoreBtnText(const QString& text);
        void setIgnoreBtnVisible(bool bShow);
        void setCheckBoxText(const QString& text);
        void setCheckBoxVisible(bool visible);
        bool getCheckedState();
    signals:
        void signalOK();
        void signalCancel();
        void signalIgnore();
        void signalClose();

    private:
        void init();

    private:
        Ui::InfoWidget *ui;
    };

}

