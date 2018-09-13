#include "MainWindow/MainWindow.h"
#include "ui_MainWindow.h"
#include <future>
#include <QEventLoop>

MainWindow::MainWindow(QWidget *parent) :
    FramelessWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pSocket = new QTcpSocket(this);

    initUi();
    initConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
    m_pSocket->disconnected();
}

/**
 *  @brief  ��ʼ������
 *  @name
 *  @author lesliefish
 *  @param  none
 *  @return
 */
void MainWindow::initUi()
{
    setWindowFlags(Qt::FramelessWindowHint);
    QIcon icon(":/new/Icon/images/main.png");
    setWindowIcon(icon);
    setWindowTitle(ui->appNameBtn->text());

    m_warningDlg = new WarningDlg;
    m_aboutDlg = new AboutDlg;

    // ����Qss�ļ�
    QString stylePath = QDir::currentPath() + "/res/main.qss";
    QFile fileQss(stylePath);
    if (fileQss.open(QFile::ReadOnly))
    {
        setStyleSheet(fileQss.readAll());
    }

    ui->maxBtn->setVisible(false);
    ui->showTableWidget->setRowCount(10);
    ui->showTableWidget->setColumnCount(6);

    for (int i = 0; i < ui->showTableWidget->rowCount(); ++i)
    {
        ui->showTableWidget->setRowHeight(i, 130);
        if (i < ui->showTableWidget->columnCount())
            ui->showTableWidget->setColumnWidth(i, 130);
    }
}


//************************************
// Method:    initConnect
// FullName:  MainWindow::initConnect
// author:    lesliefish
// Returns:   void
// Qualifier: �źŲۺ�������
//************************************
void MainWindow::initConnect()
{
    connect(ui->helpBtn, &QPushButton::clicked, [&]() {m_aboutDlg->exec(); });
    connect(ui->minBtn, &QPushButton::clicked, [&]() {this->showMinimized(); });
    connect(ui->closeBtn, &QPushButton::clicked, [&]() {m_warningDlg->exec(); });
    connect(m_warningDlg, &WarningDlg::sigExit, [&]() {this->close(); });

    connect(ui->chooseImageBtn, &QPushButton::clicked, this, &MainWindow::openImageFile);

    //����
    connect(ui->startSearchBtn, &QPushButton::clicked,
        [=]()
    {
        if (m_openedFilePath.size() == 0)
        {
            return;
        }
        ui->showTableWidget->clear();
        QString searchAction = "SEARCH";
        QString searchDepends = ui->searchTypeCombo->currentText().trimmed();
        sendRequest(searchAction, m_openedFilePath, searchDepends);
    }
    );

    //����
    connect(ui->createIndexBtn, &QPushButton::clicked, [&]()
    {
        QString indexAction = "INDEX";
        QString indexDepends = ui->searchTypeCombo->currentText().trimmed();
        ui->createIndexBtn->setEnabled(false);
        ui->createIndexBtn->setText(QString::fromLocal8Bit("������,���Ժ�..."));
        
        sendRequest(indexAction, m_openedFilePath, indexDepends);


    }
    );

    connect(m_pSocket, &QAbstractSocket::readyRead, [&]() {readMessage(); });
}


//************************************
// Method:    openImageFile
// FullName:  MainWindow::openImageFile
// author:    lesliefish
// Returns:   bool
// Qualifier: ��ͼƬ
//************************************
bool MainWindow::openImageFile()
{
    m_openedFilePath = QFileDialog::getOpenFileName(this,
        tr("���ļ�"),
        "/",
        tr("ͼ���ļ�(*.jpg *.png)"));
    if (m_openedFilePath.isEmpty())
    {
        return false;
    }

    qDebug() << m_openedFilePath;

    showChoosedImage(m_openedFilePath);
    return true;
}

//************************************
// Method:    sendRequest
// FullName:  MainWindow::sendRequest
// author:    lesliefish
// Returns:   void
// Qualifier: �����˷����������߼�������
// Parameter: QString & strAction
// Parameter: QString & filepath
// Parameter: QString & depends
//************************************
void MainWindow::sendRequest(QString& strAction, QString& filepath, QString& depends)
{
    QEventLoop loop;
    connect(this, &MainWindow::runOver, &loop, &QEventLoop::quit);
    auto fut = std::async([&]
    {
        m_pSocket->connectToHost("127.0.0.1", 12345);
        bool connected = m_pSocket->waitForConnected(5000);// waitForConnected();
        QString sendStr = strAction + "CSU" + filepath + "CSU" + depends + "CSU" + "\n";

        if (connected)
        {
            m_pSocket->write(sendStr.toStdString().c_str(), sendStr.size());
            m_pSocket->waitForBytesWritten();
        }

        emit runOver();
        return connected;
    });

    loop.exec();

    if (fut.get())
    {
        ui->createIndexBtn->setText(QString::fromLocal8Bit("�������"));
        ui->createIndexBtn->setEnabled(true);
    }
    else
    {
        ui->createIndexBtn->setText(QString::fromLocal8Bit("������󣡵����������"));
        ui->createIndexBtn->setEnabled(true);
    }

}

//************************************
// Method:    readMessage
// FullName:  MainWindow::readMessage
// author:    lesliefish
// Returns:   void
// Qualifier: ���ܷ���˷���������
//************************************
void MainWindow::readMessage()
{
    QString strImagesPath(m_pSocket->readAll());
    m_pSocket->disconnected();

    //�����������
    if (strImagesPath.trimmed() == "Index over!")
    {
        ui->createIndexBtn->setText(tr("������ϣ�"));
        ui->createIndexBtn->setEnabled(true);
        return;
    }

    //�����������
    qDebug() << strImagesPath << endl;
    showResult(strImagesPath);
}

//************************************
// Method:    showResult
// FullName:  MainWindow::showResult
// author:    lesliefish
// Returns:   void
// Qualifier: ��ʾ�������
// Parameter: const QString & strPath ���ؽ����ͼ�����ݼ���·��
//************************************
void MainWindow::showResult(const QString& strPath)
{
    QStringList filepathList = strPath.split("CSU");
    filepathList.removeLast();//ȥ�����Ļ��пհ�
    //��k��ͼ��
    int k = 0;
    for (int i = 0; i < ui->showTableWidget->rowCount(); i++)
    {
        for (int j = 0; j < ui->showTableWidget->columnCount(); j++)
        {
            QLabel *label = new QLabel();
            label->setScaledContents(true);
            QImage* img = new QImage();
            img->load(filepathList[k]);
            label->setPixmap(QPixmap::fromImage(*img));
            label->setToolTip(filepathList[k] + "");
            ui->showTableWidget->setCellWidget(i, j, label);
            k++;
        }
    }
}


//************************************
// Method:    showChoosedImage
// FullName:  MainWindow::showChoosedImage
// author:    lesliefish
// Returns:   void
// Qualifier: ��ʾ����ͼƬ��������
// Parameter: const QString & path �ļ�·��
//************************************
void MainWindow::showChoosedImage(const QString& path)
{
    ui->choosedImageWidget->setStyleSheet("QWidget{border-image: url(" + path + ")}");
    ui->choosedImageWidget->setToolTip(path);
}



