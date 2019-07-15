#ifndef WID_H
#define WID_H

#include <QtWidgets>
#include "sql.h"

class Wid : public QWidget
{
    Q_OBJECT
public:
    explicit Wid(QWidget *parent = nullptr);
    ~Wid();

private:
    void _layout();
    void createIcons();
    void connectSignals();

signals:

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
    QPushButton* m_skinButton;

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;

    QList<QColor>* rgbList;

    sql* s;
    QList<QString> data;
};

#endif // WID_H

