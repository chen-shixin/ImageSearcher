#include "InfoWidget.h"
#include "ui_InfoWidget.h"

namespace imagesearcher
{
    InfoWidget::InfoWidget(QWidget *parent)
        : FramelessWidget(parent)
    {
        ui = new Ui::InfoWidget();
        ui->setupUi(this);
        setWindowFlags(windowFlags() | Qt::SubWindow);
        setAttribute(Qt::WA_ShowModal);
        init();
    }

    InfoWidget::~InfoWidget()
    {
        delete ui;
    }

    QWidget* InfoWidget::getCenterPage()
    {
        return ui->centerPage;
    }

    void InfoWidget::init()
    {
        connect(ui->okBtn, &QPushButton::clicked, [this]
        {
            emit signalOK();
        });

        connect(ui->cancelBtn, &QPushButton::clicked, [this]
        {
            emit signalCancel();
            close();
        });

        connect(ui->closeBtn, &QPushButton::clicked, [this]
        {
            emit signalClose();
            close();
        });

        connect(ui->ignoreBtn, &QPushButton::clicked, [this]
        {
            emit signalIgnore();
            close();
        });
        setFixedSize(400, 400 * 0.618);
        setPageTitle(tr("Prompt"));
        ui->okBtn->setText(tr("OK"));
        ui->cancelBtn->setText(tr("Cancel"));
        ui->ignoreBtn->setText(tr("Ignore"));
        ui->ignoreBtn->hide();//Ĭ������
        ui->checkBox->hide();

        // ����Ƥ����ʽqss
        QString qssPath{ ":/qss/InfoWidget.qss" };
        QFile file(qssPath);
        if (file.open(QFile::ReadOnly))
        {
            setStyleSheet(file.readAll());
        }
    }

    void InfoWidget::hideBottomBtn()
    {
        ui->cancelBtn->hide();
        ui->okBtn->hide();
        ui->bottomFrame->hide();
    }

    /** @fn     InfoWidget::SetWindowTitle
    *  @brief  ���ñ���
    *  @param  const QString & title
    *  @return void
    */
    void InfoWidget::setPageTitle(const QString& title)
    {
        ui->titleLabel->setText(title);
    }

    /** @fn     InfoWidget::SetOKBtnText
    *  @brief  ����ȷ����ť�ı�
    *  @param  const QString & text
    *  @return void
    */
    void InfoWidget::setOKBtnText(const QString& text)
    {
        ui->okBtn->setText(text);
    }

    void InfoWidget::setOKBtnVisible(bool visible)
    {
        ui->okBtn->setVisible(visible);
    }

    /** @fn     InfoWidget::SetCancelBtnText
    *  @brief  ����ȡ����ť�ı�
    *  @param  const QString & text
    *  @return void
    */
    void InfoWidget::setCancelBtnText(const QString& text)
    {
        ui->cancelBtn->setText(text);
    }

    void InfoWidget::setCancelBtnVisible(bool visible)
    {
        ui->cancelBtn->setVisible(visible);
    }

    void InfoWidget::setIgnoreBtnText(const QString& text)
    {
        ui->ignoreBtn->setText(text);
    }



    void InfoWidget::setIgnoreBtnVisible(bool bShow)
    {
        ui->ignoreBtn->setVisible(bShow);
    }

    void InfoWidget::setCheckBoxText(const QString& text)
    {
        ui->checkBox->setText(text);
    }

    void InfoWidget::setCheckBoxVisible(bool visible)
    {
        ui->checkBox->setVisible(visible);
    }

    bool InfoWidget::getCheckedState()
    {
        return ui->checkBox->isChecked();
    }
}



