#include "barview.h"

#include <QPainter>


#include <QBoxLayout>

#include <QDebug>



#include "customlabel.h"


using namespace bar_internals;

BarView::BarView(QWidget *parent) :
    AbstractView(parent),
    m_bar_widget(new BarWidget(this)),
    m_layout(NULL),
    m_length(100),
    m_width(20)
{
    //setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_layout = new QBoxLayout(QBoxLayout::LeftToRight, this);

    m_layout->setMargin(0);
    m_layout->setSpacing(1);

    m_layout->addWidget(customLabel(), 0, Qt::AlignCenter);
    m_layout->addWidget(m_bar_widget,  0, Qt::AlignCenter);

    move(QSettings().value("bar/pos").toPoint());

    update_settings();
}

BarView::~BarView() {
    QSettings().setValue("bar/pos", pos());
}


void BarView::bar_draw(QPainter* p) const {

    // QRect   r = p->window().adjusted(0,0, -1,-1);

    // NOTE: the pivotal direction is DOWN

    const int lm1 = m_length - 1;

    QTransform  trs[4] = {
        QTransform(+1, 0, 0, -1, 0, lm1),     // top
        QTransform(0, +1, +1, 0, 0,   0),     // right
        QTransform(+1, 0, 0, +1, 0,   0),     // down
        QTransform(0, +1, -1, 0, lm1, 0)      // left
    };

    p->setTransform(trs[m_settings.flags & VIEW_DIRECTION_MASK]);


    QRect   r(0, 0, m_width-1, m_length-1);

    // draw bounding rect
    p->setPen  (m_settings.border);
    p->setBrush(Qt::NoBrush);
    p->drawRect(r);

    r.adjust(2, 2, -2, -2);

    //r.setBottom(r.center().y() / 2);

    int cur = m_current;

    if(m_settings.flags & VIEW_INVERTED) {
        cur = m_total - cur;
    }

    r.setHeight(r.height() * cur / m_total);

    p->setPen  (m_settings.filling);
    p->setBrush(m_settings.filling);
    p->drawRect(r);
}

QSize BarView::bar_size_hint() const {
    QSize   hint(m_width, m_length);

    if(((m_settings.flags & VIEW_DIRECTION_MASK) & 1) != 0) {       // is horizontal ?
        hint.transpose();
    }

    return hint;
}




void BarView::paintEvent ( QPaintEvent * ) {
    m_bar_widget->update();
}

void BarView::update_settings() {
    AbstractView::update_settings();

    Settings        s;

    m_length = s.bar.length;
    m_width  = s.bar.width;

    {
        QBoxLayout::Direction   dirs[4] = {
            QBoxLayout::BottomToTop,
            QBoxLayout::LeftToRight,
            QBoxLayout::TopToBottom,
            QBoxLayout::RightToLeft
        };

        m_layout->setDirection(dirs[m_settings.flags & VIEW_DIRECTION_MASK]);
    }

    m_bar_widget->updateGeometry();
    //m_bar_widget->update();
}



//////////////////////////////////////
// bar_internals::BarWidget
//

BarWidget::BarWidget(BarView* parent_view) :
    QWidget(),
    m_bar_view(parent_view)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    //setAttribute(Qt::WA_TranslucentBackground);
    setContextMenuPolicy(Qt::NoContextMenu);
    //setAutoFillBackground(true);
}

void BarWidget::paintEvent(QPaintEvent* ) {
    QPainter    p(this);

    // delegate the drawing to the parent bar
    m_bar_view->bar_draw(&p);
}

QSize BarWidget::sizeHint() const {
    return m_bar_view->bar_size_hint();
}

