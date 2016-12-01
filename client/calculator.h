/****************************************************************************
**
** calculator.h
**
****************************************************************************/

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTCPSocket.h>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void buttonClicked();
    void signClicked();

    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();

    void on_pushButton_plus_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_mult_clicked();
    void on_pushButton_div_clicked();

    void on_pushButton_eq_clicked();

    void on_pushButton_c_clicked();

private:
    QTcpSocket *socket;
    QString decorateMessage(QString message);
    Ui::Widget *ui;
};

#endif // WIDGET_H
