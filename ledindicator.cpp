#include "ledindicator.h"

// Constructor
LedIndicator::LedIndicator(QWidget *parent) : QWidget(parent) {

}

LedIndicator::LedIndicator(const QString& name, const double& x, const double& y, int ledSize, QWidget *parent) :
    QWidget(parent)
{
    threshold.push_back(5);
    threshold.push_back(10);
    lit = gray;
    ledHighImpedance=Qt::red;
    ledLowImpedance=Qt::green;
    ledMidImpedance=Qt::yellow;
    ledNotConnected=Qt::gray;

    ledHighPattern = Qt::SolidPattern;
    ledLowPattern = Qt::SolidPattern;
    ledMidPattern = Qt::SolidPattern;
    ledNotConnectedPattern = Qt::SolidPattern;


    highlighted = false;

    // Assign the name label displayed below the led
    this->name = new QLabel(this);
    this->name->setText(name);

    // Led's relative positions to the parent picture.
    this->relativePos_x = x;
    this->relativePos_y = y;
    this->ledSize = ledSize;

}

//-----------------------------------------------------------------------------------------------------
//                                          PaintEvent overload
//-----------------------------------------------------------------------------------------------------
void LedIndicator::paintEvent(QPaintEvent *) {
  QPainter p(this);

  switch(lit) {
  case gray:
      p.setBrush(QBrush(ledNotConnected, ledNotConnectedPattern));
      break;
  case red:
      p.setBrush(QBrush(ledHighImpedance, ledHighPattern));
      break;
  case yellow:
      p.setBrush(QBrush(ledMidImpedance, ledMidPattern));
      break;
  case green:
      p.setBrush(QBrush(ledLowImpedance, ledLowPattern));
      break;
  }

  if (highlighted == true) {
    QPen* pen = new QPen();
    pen->setWidth(3);
    pen->setColor(Qt::blue);
    p.setPen(*pen);
  }
  else
    p.setPen(Qt::NoPen);

  p.drawEllipse(1,1,ledSize,ledSize);
}

//-----------------------------------------------------------------------------------------------------
//                                          Getters and Setters
//-----------------------------------------------------------------------------------------------------
void LedIndicator::setState(color state)
{
    lit = state;
    repaint();
}

void LedIndicator::setHighImpColor(QColor highColor)
{
    ledHighImpedance=highColor;
    repaint();
}

void LedIndicator::setLowImpColor(QColor lowColor)
{
    ledLowImpedance=lowColor;
    repaint();
}

void LedIndicator::setMidImpColor(QColor midColor)
{
    ledMidImpedance=midColor;
    repaint();
}

void LedIndicator::setHighPattern(Qt::BrushStyle highPattern)
{
    ledHighPattern=highPattern;
    repaint();
}

void LedIndicator::setLowPattern(Qt::BrushStyle lowPattern)
{
    ledLowPattern=lowPattern;
    repaint();
}

void LedIndicator::setMidPattern(Qt::BrushStyle midPattern)
{
    ledMidPattern=midPattern;
    repaint();
}

void LedIndicator::setLedThreshold(int impThreshold) {
    switch(impThreshold) {
    case(0):
        threshold.at(0) = 5.0;
        threshold.at(1) = 10.0;
        break;
    case(1):
        threshold.at(0) = 10.0;
        threshold.at(1) = 20.0;
        break;
    case(2):
        threshold.at(0) = 20.0;
        threshold.at(1) = 50.0;
        break;
    case(3):
        threshold.at(0) = 50.0;
        threshold.at(1) = 100.0;
        break;
    }
}

void LedIndicator::setHighLighted(bool highLight) {
    this->highlighted = highLight;
    repaint();
}


void LedIndicator::setLedSize(int size)
{
    ledSize=size;


    setFixedSize(size+25, size+25);
    repaint();
}

int LedIndicator::getLedSize(void) const {
    return this->ledSize;
}

void LedIndicator::setRelativePosX(double x) {
    this->relativePos_x = x;
}

double LedIndicator::getRelativePosX(void) const  {
    return this->relativePos_x;
}

void LedIndicator::setRelativePosY(double y) {
    this->relativePos_y = y;
}

double LedIndicator::getRelativePosY(void) const {
    return this->relativePos_y;
}

//-----------------------------------------------------------------------------------------------------
//                                                  Functions
//-----------------------------------------------------------------------------------------------------

void LedIndicator::displayImpedance(double impValue) {

    if ( (impValue < threshold.at(0)) )
        lit = green;
    else if ( impValue > threshold.at(1) )
        lit = red;
    else
        lit = yellow;
    repaint();
}

