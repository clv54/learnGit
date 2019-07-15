#include "chinese.h"
#include "ui_chinese.h"

Chinese::Chinese(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chinese)
{
    ui->setupUi(this);
}

Chinese::~Chinese()
{
    delete ui;
}
