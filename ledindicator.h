#ifndef LEDINDICATOR_H
#define LEDINDICATOR_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <vector>

enum color {gray, red, yellow, green };

class LedIndicator: public QWidget {
    Q_OBJECT

//----------------------------------------------------------
// Methods
//----------------------------------------------------------

public:
    LedIndicator(QWidget *parent = 0);
    LedIndicator(const QString& name, const double& x, const double& y, int ledSize = 8, QWidget *parent = 0);

    void setState(color state);

    void setHighImpColor(QColor highColor);
    void setLowImpColor(QColor lowColor);
    void setMidImpColor(QColor midColor);

    void setHighPattern(Qt::BrushStyle highPattern);
    void setLowPattern(Qt::BrushStyle lowPattern);
    void setMidPattern(Qt::BrushStyle midPattern);

    void setLedThreshold(int impThreshold);

    void setHighLighted(bool);

    void setLedSize(int size);
    int getLedSize(void) const;

    void setRelativePosX(double);
    double getRelativePosX(void) const;

    void setRelativePosY(double);
    double getRelativePosY(void) const;

protected:
    void paintEvent(QPaintEvent *);

//----------------------------------------------------------
// Slots
//----------------------------------------------------------

public slots:
    void displayImpedance(double impValue);

//----------------------------------------------------------
// Attributes
//----------------------------------------------------------

public:
    QLabel* name;

private:
    color lit;
    QColor ledNotConnected;
    QColor ledHighImpedance;
    QColor ledLowImpedance;
    QColor ledMidImpedance;
    Qt::BrushStyle ledHighPattern;
    Qt::BrushStyle ledLowPattern;
    Qt::BrushStyle ledMidPattern;
    Qt::BrushStyle ledNotConnectedPattern;

    int ledSize;

    std::vector<double> threshold;
    bool highlighted;
    double impValue;

    double relativePos_x;
    double relativePos_y;
};

#endif // LEDINDICATOR_H
