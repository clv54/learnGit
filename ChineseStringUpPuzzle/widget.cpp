#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include <string>

Widget::Widget(QList<QString> da, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    score = 0;
    last = nullptr;
    data1 = data = da;

    ui->textEdit->setReadOnly(true);
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setText(tr("%1").arg(score));
    ui->lineEdit_2->setPlaceholderText("将成语输入此处："); // 设置背景提示文字
    ui->lineEdit_2->setDisabled(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ui->lineEdit_2->setDisabled(false);
    ui->textEdit->setText("开始游戏：");
    score = 0;
    last = nullptr;
}

void Widget::on_pushButton_2_clicked()
{
    score = 0;
    ui->textEdit->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit->setReadOnly(true);
    data = data1;
    last = nullptr;
}

void Widget::on_lineEdit_2_returnPressed()
{
    ui->textEdit->append(tr("<font color=\"#00FF00\">%1</font>").arg(ui->lineEdit_2->text()));
    bool flag = false;
    QString end = ui->lineEdit_2->text().mid( ui->lineEdit_2->text().length() - 1);

    if (last != nullptr) {
        if (ui->lineEdit_2->text().mid(0, 1) != last) {
            ui->textEdit->append(tr("<font color=\"#FF0000\">错误：成语没有接上，you败！！！</font>"));
            ui->lineEdit_2->setDisabled(true);
            return;
        }
    }

    for (QList<QString>::iterator it = data.begin(); it != data.end(); it++)
    {
        QString temp = (*it).mid(0, 1);
        if ( temp == end ){
            //qDebug() << *it;
            ui->textEdit->append(tr("<font color=\"#FF0000\">%1</font>").arg(*it));
            last = (*it).right(1);
            data.removeOne(*it);
            flag = true;
            score++;
            ui->lineEdit->setText(tr("%1").arg(score));
            break;
        }
        if (flag)
            break;
    }
    if (!flag) {
        ui->textEdit->append(tr("<font color=\"#FF0000\">错误：词库中没有新词，电脑败！！！</font>"));
        ui->lineEdit_2->setDisabled(true);
    }

    ui->lineEdit_2->clear();
    ui->textEdit->moveCursor(QTextCursor::End);
}
