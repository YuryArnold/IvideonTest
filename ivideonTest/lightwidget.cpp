#include "lightwidget.h"
#include <math.h>
#include <QPainter>
#include <QGradient>
#include <QPaintDevice>

LightWidget::
LightWidget(QWidget* parent) :
    QWidget(parent),
    m_color(QColor("gray")),
    m_alignment(Qt::AlignCenter),
    m_OnOff(false)
{
    setDiameter(double(height()/4));
}

LightWidget::~LightWidget()
{
}

double LightWidget::diameter() const
{
    return m_diameter;
}

void LightWidget::setDiameter(double diameter)
{
    m_diameter = diameter;

    m_pixX = round(double(height())/heightMM());
    m_pixY = round(double(width())/widthMM());

    m_diamX = m_diameter*m_pixX;
    m_diamY = m_diameter*m_pixY;

    update();
}


QColor LightWidget::color() const
{
    return m_color;
}

void LightWidget::setColor(QColor color)
{
    m_color = color;
    update();
}

void LightWidget::setOnOff(bool _state)
{
    if (m_OnOff != _state){
        m_OnOff = _state;
        if(m_OnOff)
            setColor(QColor("white"));
        else {
            setColor(QColor("gray"));
        }
        update();
    }
}

void LightWidget::setColorSlot(QRgb _color)
{
    if(m_OnOff)
        setColor(QColor(_color));
}


Qt::Alignment LightWidget::alignment() const
{
    return m_alignment;
}

void LightWidget::setAlignment(Qt::Alignment alignment)
{
    m_alignment = alignment;
    update();
}


int LightWidget::heightForWidth(int width) const
{
    return width;
}

QSize LightWidget::sizeHint() const
{
    return QSize(m_diamX, m_diamY);
}

QSize LightWidget::minimumSizeHint() const
{
    return QSize(m_diamX, m_diamY);
}

void LightWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    setDiameter(double(height()/4));
    QPainter p(this);
    QRect geo = geometry();
    int width = geo.width();
    int height = geo.height();
    int x = (width-m_diamX)/2;
    int y = (height-m_diamY)/2;

    QRadialGradient g(x + m_diamX/2,
                      y + m_diamY/2,
                      m_diamX * 0.55,
                      m_diamX * 0.55,
                      m_diamY * 0.55);

    g.setColorAt(0, Qt::white);
    g.setColorAt(1, m_color);


    QBrush brush(g);
    QPen pen(Qt::black);
    pen.setWidth(2);
    p.setPen(pen);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setBrush(brush);
    p.drawEllipse(x, y, m_diamX-1, m_diamY-1);
}

