#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QList<QString> da, QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_2_returnPressed();

private:
    Ui::Widget *ui;

    int score;
    QString last;
    QList<QString> data, data1;
};

#endif // WIDGET_H
