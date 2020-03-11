#ifndef LIGHT_WIDGET_H
#define LIGHT_WIDGET_H
#include <QWidget>
#include <QColor>

class LightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LightWidget(QWidget* parent = nullptr);
    ~LightWidget();
    double diameter() const;
    void setDiameter(double diameter);
    QColor color() const;
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment alignment);

public slots:
    void setOnOff(bool _state);
    void setColorSlot(QRgb _color);

public:
    int heightForWidth(int width) const;
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

private:
    void setColor(QColor _color);

protected:
    void paintEvent(QPaintEvent* event);

private:
    double m_diameter;
    QColor m_color;
    Qt::Alignment m_alignment;
    int m_pixX, m_pixY;
    int m_diamX, m_diamY;
    bool m_OnOff;
};

#endif
