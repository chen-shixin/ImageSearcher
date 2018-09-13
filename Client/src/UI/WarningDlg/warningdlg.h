/** @file    aboutdlg.h
* @note
* @brief   �˳���ʾ����
*
* @author  lesliefish
* @date    2017��10��19��
*
* @note    detailed functional description of this document and comments
* @note    History
*
* @warning warning message related to this document
*/

#ifndef WARNINGDLG_H
#define WARNINGDLG_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class WarningDlg;
}

class WarningDlg : public QDialog
{
    Q_OBJECT

public:
    explicit WarningDlg(QWidget *parent = 0);
    ~WarningDlg();

private:
    Ui::WarningDlg *ui;
    void exit();
protected:
    //ʵ�������ޱ߿򴰿��϶�
    QPoint m_pointMove;
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
signals:
    void sigExit();
};

#endif // WARNINGDLG_H
