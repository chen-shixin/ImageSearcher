#pragma once

#include <QWidget>
#include "InfoWidget.h"

namespace Ui { class InfoTextWidget; };

namespace imagesearcher
{
    class InfoTextWidget : public InfoWidget
    {
        Q_OBJECT

    public:
        InfoTextWidget(QWidget *parent = Q_NULLPTR);
        ~InfoTextWidget();

        //������ʾ��Ϣ
        void setTipText(const QString& text);

    private:
        Ui::InfoTextWidget *ui;
        QString m_text;
    };
}
