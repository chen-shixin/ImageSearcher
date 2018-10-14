#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>

namespace imagesearcher
{
    MainWindow::MainWindow(QWidget *parent)
        : FramelessWidget(parent)
    {
        ui = new Ui::MainWindow();
        ui->setupUi(this);

        initUi();
        initConnection();
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    void MainWindow::initUi()
    {
        infoTextWidget = new InfoTextWidget;
        infoTextWidget->setOKBtnVisible(false);
        infoTextWidget->setCancelBtnText(tr("Close"));

        ui->tableWidget->setRowCount(10);
        ui->tableWidget->setColumnCount(6);
        ui->tableWidget->horizontalHeader()->hide();
        ui->tableWidget->verticalHeader()->hide();
        ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        int itemHeight = this->width() / 6;
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
        {
            ui->tableWidget->setRowHeight(i, itemHeight);
            if (i < ui->tableWidget->columnCount())
            {
                ui->tableWidget->setColumnWidth(i, itemHeight);
            }
        }


        // ����Ƥ����ʽqss
        QString qssPath{ ":/qss/ImageSearcher.qss" };
        QFile file(qssPath);
        if (file.open(QFile::ReadOnly))
        {
            setStyleSheet(file.readAll());
        }
    }

    /** @fn     imagesearcher::MainWindow::initConnection
     *  @brief  
     *  @return void 
     */
    void MainWindow::initConnection()
    {
        connect(ui->closeBtn, &QPushButton::clicked, [&] { close(); });
        connect(ui->minBtn, &QPushButton::clicked, [&] { showMinimized(); });
        connect(&m_socket, &QTcpSocket::readyRead, [&] {recieveFromSever(); });
        connect(infoTextWidget, &InfoTextWidget::signalOK, [&] {close(); });

        connect(ui->openFileBtn, &QPushButton::clicked, [&]
        {
            QString openDir{""};
            if (!m_curImagePath.isEmpty())
            {
                int dotPos = m_curImagePath.lastIndexOf("/");
                openDir = m_curImagePath.left(dotPos + 1);
            }
            QString path = QFileDialog::getOpenFileName(this, tr("Open File"), openDir, tr("Image Files (*.jpg *.png)"));
            if (path.isEmpty())
            {
                return;
            }

            QString labelImageSetQss = QString("QLabel{border-image : url(%1);}").arg(path);
            ui->selectedImageLabel->setStyleSheet(labelImageSetQss);
            ui->selectedImageLabel->clear();

            m_curImagePath = path;
        });

        // ����
        connect(ui->searchBtn, &QPushButton::clicked, [&]
        {
            if (m_curImagePath.isEmpty())
            {
                infoTextWidget->setTipText(tr("Please select image file first."));
                infoTextWidget->show();
                return;
            }

            QString action = "SEARCH";
            QString depends = ui->searchTypeCombo->currentText().trimmed();
            depends = "CEDD";
            sendRequest(action, m_curImagePath, depends);

            ui->tableWidget->clear();
        });

        // ����
        connect(ui->createIndexBtn, &QPushButton::clicked, [&]
        {
            QString action = "INDEX";
            QString depends = "CEDD";
            sendRequest(action, "C:", depends);
        });
    }

    /** @fn     imagesearcher::MainWindow::sendRequest
     *  @brief  ��������
     *  @param  const QString & action ����
     *  @param  const QString & filePath Ҫ�ȶԵ�ͼ��·��
     *  @param  const QString & depends ����/��������
     *  @return void
     */
    void MainWindow::sendRequest(const QString& action, const QString& filePath, const QString& depends)
    {
        m_socket.connectToHost("127.0.0.1", 12345);
        QString sendStr = action + "-CSU-" + filePath + "-CSU-" + depends + "-CSU-" + "\n";
        bool connected = m_socket.waitForConnected(5000); // ��ʱ5��

        if (!connected)
        {
            // ���ӷ�����ʧ��
            infoTextWidget->setTipText(tr("Connect server failed."));
            infoTextWidget->show();
            return;
        }

        m_socket.write(sendStr.toUtf8().data(), sendStr.toUtf8().size());
    }

    /** @fn     imagesearcher::MainWindow::recieveFromSever
     *  @brief  ������������յ�������
     *  @return void
     */
    void MainWindow::recieveFromSever()
    {
        QString recievedString = m_socket.readAll();
        m_socket.disconnected();

        if (recievedString.trimmed().compare("Index over!") == 0)
        {
            // ���������Ϣ
            infoTextWidget->setTipText(tr("Index over!"));
            infoTextWidget->show();
            return;
        }

        // ��������ͼ����
        QStringList paths = recievedString.split("-CSU-");
        if (!paths.empty())
        {
            paths.removeLast();
            showResult(paths);
        }
    }

    /** @fn     imagesearcher::MainWindow::showResult
     *  @brief  genju jiansuojieguo xianshichulai
     *  @param  const QStringList paths
     *  @return void
     */
    void MainWindow::showResult(const QStringList paths)
    {
        ui->tableWidget->clear();
        //��k��ͼ�� 
        int k = 0;
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            for (int j = 0; j < ui->tableWidget->columnCount(); j++)
            {
                QLabel *label = new QLabel();
                label->setScaledContents(true);
                QImage* img = new QImage();
                img->load(paths[k]);
                label->setPixmap(QPixmap::fromImage(*img));
                label->setToolTip(paths[k] + "");
                ui->tableWidget->setCellWidget(i, j, label);
                k++;
                if (k == paths.size()) 
                {
                    return;
                }
            }
        }
    }

}

