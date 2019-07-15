#include "chinese.h"
#include "wid.h"
#include "widget.h"

Wid::Wid(QWidget *parent)
    : QWidget(parent)
{
    rgbList = new QList<QColor>{
            Qt::color0,
            Qt::white,
            Qt::darkGray,
            Qt::gray,
            Qt::lightGray,
            Qt::red,
            Qt::green,
            Qt::blue,
            Qt::cyan,
            Qt::magenta,
            Qt::yellow,
            Qt::darkRed,
            Qt::darkGreen,
            Qt::darkBlue,
            Qt::darkCyan,
            Qt::darkMagenta,
            Qt::darkYellow};
    s = new sql();
    data = s->select("manageRecord", "");

    _layout();
    connectSignals();
}

Wid::~Wid()
{
}

void Wid::_layout()
{
    resize(1100, 800);

    contentsWidget = new QListWidget(this);
    contentsWidget->setStyleSheet("background-color:transparent");      // 设置背景为透明色
    contentsWidget->setIconSize(QSize(35, 35));
    contentsWidget->setMaximumWidth(150);
    contentsWidget->setSpacing(10);

    pagesWidget = new QStackedWidget(this);
    pagesWidget->addWidget(new Widget(data, this));
    pagesWidget->addWidget(new Chinese());

    createIcons();  // 创建选择功能界面的列表按钮
    contentsWidget->setCurrentRow(0);

    //this->setPalette(QPalette(QPalette::Background, Qt::white));  // 如果设置主界面的背景颜色，下拉框QComboBox就会变为黑色

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(10);       // 设置边缘留白

    QHBoxLayout* headlLayout = new QHBoxLayout();
    headlLayout->setMargin(8);       // 设置边缘留白
    QLabel* label = new QLabel(tr("GAME"), this);
    label->setAlignment(Qt::AlignCenter);       // 位置在中间
    label->setFont(QFont(tr("Consolas"), 14));
    //m_skinButton = new QPushButton(QIcon(":/new/icon/src/山.jpg"), nullptr, this);
    m_skinButton = new QPushButton("换肤", this);
    m_skinButton->setFixedSize(30,22);
    m_skinButton->setIconSize(QSize(30, 30));
    //skinButton->setFlat(true);          // 设置扁平化，无边框
    headlLayout->addWidget(label);
    headlLayout->addWidget(m_skinButton);

    QHBoxLayout* bodyLayout = new QHBoxLayout();
    //QPushButton* button = new QPushButton("1", this);
    bodyLayout->addWidget(contentsWidget);
    bodyLayout->addWidget(pagesWidget);

    mainLayout->addLayout(headlLayout,1);
    mainLayout->addLayout(bodyLayout,9);

}

void Wid::createIcons()
{
    QListWidgetItem *noticeButton = new QListWidgetItem(contentsWidget);
    noticeButton->setText(tr("成语接龙"));
    noticeButton->setTextAlignment(Qt::AlignHCenter);
    noticeButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *classroomButton = new QListWidgetItem(contentsWidget);
    classroomButton->setText(tr("成语接龙"));
    classroomButton->setTextAlignment(Qt::AlignHCenter);
    classroomButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

void Wid::connectSignals()
{
    connect(contentsWidget, &QListWidget::currentItemChanged, this, &Wid::changePage);

    // 切换皮肤信号槽
    connect(m_skinButton, &QPushButton::clicked, [&](){
        QPalette pal(this->palette());
        pal.setColor(QPalette::Background, rgbList->first());
        rgbList->push_back(rgbList->first());rgbList->pop_front();  // 把第一个颜色放到最后
        this->setAutoFillBackground(true);
        this->setPalette(pal);
    });
}

void Wid::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
