/****************************************************************************
**
** calculator.cpp
**
** Handling of button clicks for Calculator widget
**
****************************************************************************/

#include "calculator.h"
#include "ui_calculator.h"
#include <QTime>

const QString date_format = "dd.MM.yyyy hh:mm:ss";
const int wating_time = 1000;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
}

Widget::~Widget()
{
    delete ui;
    socket->close();
}

void Widget::buttonClicked()
{
    QLineEdit *res = this->findChild<QLineEdit *>("lineEdit_result");

    // if negative result
    if (res->text().contains(QRegExp("^\\D"))) {
        res->setText("");
    }
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    res->setText(res->text() + clickedButton->text());
}

void Widget::signClicked()
{
    QLineEdit *res = this->findChild<QLineEdit *>("lineEdit_result");
    QString res_txt = res->text();
    if (!res_txt.isEmpty()
            && !res_txt.contains(QRegExp("[+\\-*\\/]$"))
            && !res_txt.contains(QRegExp("\\D"))) {
        this->buttonClicked();
    }
}

void Widget::on_pushButton_0_clicked()
{
    this->buttonClicked();
}

void Widget::on_pushButton_1_clicked()
{
    this->buttonClicked();
}

void Widget::on_pushButton_2_clicked()
{
    this->buttonClicked();
}

void Widget::on_pushButton_3_clicked()
{
    this->buttonClicked();
}

void Widget::on_pushButton_4_clicked()
{
    this->buttonClicked();
}

void Widget::on_pushButton_5_clicked()
{
    this->buttonClicked();
}

void Widget::on_pushButton_6_clicked()
{
    this->buttonClicked();
}

void Widget::on_pushButton_7_clicked()
{
    this->buttonClicked();
}

void Widget::on_pushButton_8_clicked()
{
    this->buttonClicked();
}

void Widget::on_pushButton_9_clicked()
{
    this->buttonClicked();
}

void Widget::on_pushButton_plus_clicked()
{
    this->signClicked();
}

void Widget::on_pushButton_minus_clicked()
{
    this->signClicked();
}

void Widget::on_pushButton_mult_clicked()
{
    this->signClicked();
}

void Widget::on_pushButton_div_clicked()
{
    this->signClicked();
}

QString Widget::decorateMessage(QString message)
{
    return QDateTime::currentDateTime().toString(date_format) + " " + message;
}

void Widget::on_pushButton_eq_clicked()
{
    QLineEdit *res = this->findChild<QLineEdit *>("lineEdit_result");
    QString res_txt = res->text();
    QString response;
    if (!res_txt.isEmpty()) {
        QTextEdit *messages = this->findChild<QTextEdit *>("textEdit_messages");
        QLineEdit *host = this->findChild<QLineEdit *>("lineEdit_host");
        QSpinBox *port = this->findChild<QSpinBox *>("spinBox_port");

        // Connecting to server if socket is not connected
        if (socket->state() == QAbstractSocket::UnconnectedState) {
            socket->connectToHost(host->text(), port->value());
            messages->append(this->decorateMessage(
                                 "Connecting to " + host->text() +
                                 ": " + QString::number(port->value()) + "..."));
            if(socket->waitForConnected(-1)) {
                messages->append(this->decorateMessage("Connected"));
            } else {
                messages->append(this->decorateMessage(
                                     "Connection fault, please check your settings"));
           }
        }

        // Sending a request and getting a result of calculations
        if (socket->state() == QAbstractSocket::ConnectedState) {
            messages->append(this->decorateMessage(
                                 "Sending the request \"" + res_txt + "\""));
            socket->write(res_txt.toLocal8Bit());
            socket->waitForBytesWritten(wating_time);

            socket->waitForReadyRead(wating_time);
            messages->append(this->decorateMessage("Waiting for the response..."));

            response = socket->readAll();
            if (!response.isNull()) {
                messages->append(this->decorateMessage(
                                     host->text() + ": " + res->text() + "=" + response));
                res->setText(response);
            } else {
                messages->append(this->decorateMessage(host->text() + ": Incorrect statement"));
            }
            messages->append(this->decorateMessage("Done"));
        }
    }
}

void Widget::on_pushButton_c_clicked()
{
    QLineEdit *res = this->findChild<QLineEdit *>("lineEdit_result");
    res->setText("");
}
