/** @file    aboutdlg.h
* @note
* @brief   ���ڴ���
*
* @author  lesliefish
* @date    2017��10��21��
*
* @note    detailed functional description of this document and comments
* @note    History
*
* @warning warning message related to this document
*/

#ifndef ABOUTDLG_H
#define ABOUTDLG_H

#include <QDialog>

namespace Ui {
class AboutDlg;
}

class AboutDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDlg(QWidget *parent = 0);
    ~AboutDlg();

private:
    Ui::AboutDlg *ui;
protected:
    //ʵ�������ޱ߿򴰿��϶�
    QPoint m_pointMove;
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // ABOUTDLG_H
