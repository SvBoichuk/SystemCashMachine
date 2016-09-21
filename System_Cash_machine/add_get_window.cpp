#include "add_get_window.h"
#include "ui_add_get_window.h"
#include <QMessageBox>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QDateTime>

Add_Get_Window::Add_Get_Window(ClientNetwork *n, int type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_Get_Window)
{
    ui->setupUi(this);

    //case 1 - Add money form
    //case 2 - Get money form
    switch(type)
    {
        case 1:
            ui->get_variants->hide(); // this widget hide
            this->setFixedSize(400,150);
            this->setWindowTitle("Add money");
            break;
        case 2:
            this->setFixedSize(400,260);
            this->setWindowTitle("Get money");
            break;
    }
    net = n;
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]{3,6}")));
    ui->pushButton_5->setEnabled(false);
}

Add_Get_Window::~Add_Get_Window()
{
    delete ui;
}

void Add_Get_Window::on_pushButton_5_clicked()
{
    this->close();
}


void Add_Get_Window::on_btn_100_clicked()
{
    ui->lineEdit->setText(ui->btn_100->text());
    QString num = "GET ";
    num += ui->lineEdit->text();
    qDebug() << num;
    net->Send(num.toStdString().c_str());
    char buf[14];
    memset(buf,0,14);
    net->Recv(buf);

    if(strcmp(buf,"GetMoneyOK") == 0)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Check","Print check?", QMessageBox::Yes | QMessageBox::No);
        if( reply == QMessageBox::Yes)
        {
            QTextDocument doc;
            QString str;
            str += QString("**********CHECK**********\nSUM: ") += ui->lineEdit->text() + "\nDate: " + QDateTime::currentDateTime().toString();
            doc.setHtml("<h3>" + str + "</h3>");
            QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("\\check.pdf");
            doc.print(&printer);
            printer.newPage();
        }
    }
}

void Add_Get_Window::on_btn_200_clicked()
{
    ui->lineEdit->setText(ui->btn_200->text());
}

void Add_Get_Window::on_btn_500_clicked()
{
    ui->lineEdit->setText(ui->btn_500->text());
}

void Add_Get_Window::on_btn_1000_clicked()
{
    ui->lineEdit->setText(ui->btn_1000->text());
}

void Add_Get_Window::on_lineEdit_textChanged(const QString &arg1)
{
    //min sum is 100, and max is 99999
    if(ui->lineEdit->text().length() < 3 || ui->lineEdit->text().length() > 5)
        ui->pushButton_5->setEnabled(false);
    else ui->pushButton_5->setEnabled(true);
}
