#ifndef ASPECTRATIOLABEL_H
#define ASPECTRATIOLABEL_H

#include "ledindicator.h"

#pragma once

#include <QLabel>

class AspectRatioLabel : public QLabel
{
    Q_OBJECT

//----------------------------------------------------------
// Methods
//----------------------------------------------------------
private:
    void updateMargins();

public:
    explicit AspectRatioLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void displayLed();
    void createLed(const QString&, double, double);
    void adapSizeLED(LedIndicator& led, QLabel& impLabel, const QFont& f);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void moveEvent(QMoveEvent *event) override;

//----------------------------------------------------------
// Slots
//----------------------------------------------------------
public slots:
    void setPixmap(const QPixmap& pm);

//----------------------------------------------------------
// Attributes
//----------------------------------------------------------
public:
    QVector<LedIndicator*> ledVector;
    QVector<QLabel*> impLabel;

private:

    int pixmapWidth;
    int pixmapHeight;

    int xMargin = 0;
    int yMargin = 0;
};

#endif // ASPECTRATIOLABEL_H
