#ifndef CHINESE_H
#define CHINESE_H

#include <QWidget>

namespace Ui {
class Chinese;
}

class Chinese : public QWidget
{
    Q_OBJECT

public:
    explicit Chinese(QWidget *parent = nullptr);
    ~Chinese();

private:
    Ui::Chinese *ui;
};

#endif // CHINESE_H
