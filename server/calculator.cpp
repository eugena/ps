/****************************************************************************
**
** calculator.cpp
**
** Performing calculations
**
****************************************************************************/

#include "calculator.h"

Calculator::Calculator(QObject *parent) : QObject(parent)
{

}

bool Calculator::checkStatement(QString st)
{
    return st.contains(QRegExp("\\d+[+\\-*\\/]\\d+"));
}

int Calculator::getResult(QString st) {
    int result;

    QRegExp rx("(\\d+)(\\D)(\\d+)");
    rx.indexIn(st);
    QStringList list = rx.capturedTexts();
    int number1 = list.at(1).toInt();
    QString sign = list.at(2);
    int number2 = list.at(3).toInt();

    QStringList signs;
    signs << "+" << "-" << "*" << "/";
    int sign_index;

    sign_index = signs.indexOf(sign);
    switch (sign_index) {
    case 0:
        result = number1 + number2;
        break;
    case 1:
        result = number1 - number2;
        break;
    case 2:
        result = number1 * number2;
        break;
    case 3:
        result = number1 / number2;
        break;
    }
    return result;
}
