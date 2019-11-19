#include "aspectratiolabel.h"

AspectRatioLabel::AspectRatioLabel(QWidget* parent, Qt::WindowFlags f) : QLabel(parent, f)
{
}

void AspectRatioLabel::createLed(const QString& name, double posX, double posY) {

    int ledSize = 10;

    // Shift all electrodes (to save time du to original bad aligment)
    int shiftX = 15;
    int shiftY = 25;


    // Relative position + substract the widget's size.
    double x = (posX - ledSize + shiftX) / pixmapWidth;
    double y = (posY- ledSize + shiftY) / pixmapHeight;

    ledVector.push_back(new LedIndicator(name, x, y, ledSize, this));
    ledVector.back()->hide();

    impLabel.push_back(new QLabel(ledVector.back()));
    impLabel.back()->hide();

    int fontSize = (this->width() - 2*xMargin) / 100;
    const QFont f( "Arial", fontSize, QFont::Normal);

    for(int i=0; i<this->ledVector.length(); ++i) {
        adapSizeLED(*ledVector.at(i), *impLabel.at(i), f);
    }
}
void AspectRatioLabel::displayLed() {

    // Prepare the electrodes positions on the image.
    {
        createLed("FP1", 300, 65);          createLed("FPZ", 360.0, 60.0);      createLed("FP2", 425.0, 65.0);      createLed("F7", 195.0, 135.0);
        createLed("F3", 275.0, 153.0);      createLed("FZ", 360.0, 158.0);      createLed("F4", 450.0, 153.0);      createLed("F8", 528.0, 135.0);
        createLed("FC5", 213.0, 200.0);     createLed("FC1", 312.0, 207.0);     createLed("FC2", 413.0, 207.0);     createLed("FC6", 512.0, 200.0);
        createLed("M1", 73.0, 309.0);       createLed("T7", 155.0, 257.0);      createLed("C3", 258.0, 257.0);      createLed("CZ", 360.0, 260.0);
        createLed("C4", 465.0, 257.0);      createLed("T8", 570.0, 257.0);      createLed("M2", 647.0, 309.0);      createLed("CP5", 213.0, 313.0);
        createLed("CP1", 313.0, 307.0);     createLed("CP2", 410.0, 307.0);     createLed("CP6", 512.0, 313.0);     createLed("P7", 195.0, 378.0);
        createLed("P3", 275.0, 359.0);      createLed("PZ", 360.0, 355.0);      createLed("P4", 450.0, 359.0);      createLed("P8", 530.0, 378.0);
        createLed("POZ", 360.0, 405.0);     createLed("O1", 300.0, 455.0);      createLed("O2", 422.0, 455.0);      createLed("AF7", 242.0, 93.0);

        createLed("AF3", 300.0, 105.0);     createLed("AF4", 425.0, 105.0);     createLed("AF8", 480.0, 93.0);      createLed("F5", 235.0, 147.0);
        createLed("F1", 317.0, 158.0);      createLed("F2", 405.0, 158.0);      createLed("F6", 488.0, 147.0);      createLed("FC3", 260.0, 206.0);
        createLed("FCZ", 360.0, 208.0);     createLed("FC4", 462.0, 206.0);     createLed("C5", 205.0, 257.0);      createLed("C1", 310.0, 257.0);
        createLed("C2", 413.0, 257.0);      createLed("C6", 518.0, 257.0);      createLed("CP3", 263.0, 309.0);     createLed("CP4", 463.0, 310.0);
        createLed("P5", 232.0, 367.0);      createLed("P1", 318.0, 356.0);      createLed("P2", 406.0, 356.0);      createLed("P6", 490.0, 367.0);
        createLed("PO5", 270.0, 414.0);     createLed("PO3", 298.0, 409.0);     createLed("PO4", 424.0, 409.0);     createLed("PO6", 453.0, 414.0);
        createLed("FT7", 165.0, 192.0);     createLed("FT8", 560.0, 192.0);     createLed("TP7", 165.0, 320.0);     createLed("TP8", 560.0, 320.0);
        createLed("PO7", 240.0, 423.0);     createLed("PO8", 480.0, 425.0);     createLed("OZ", 360.0, 465.0);      createLed("FT9", 140.0, 175.0);

        createLed("FT10", 585, 175.0);      createLed("TPP9H", 145.0, 340.0);   createLed("TPP10H", 580.0, 340.0);  createLed("PO9", 215.0, 435.0);
        createLed("PO10", 505.0, 435.0);    createLed("P9", 165.0, 400.0);      createLed("P10", 560.0, 400.0);     createLed("AFF1", 335.0, 135.0);
        createLed("AFZ", 360.0, 110.0);     createLed("AFF2", 385.0, 135.0);    createLed("FFC5H", 250.0, 175.0);   createLed("FFC3H", 290.0, 180.0);
        createLed("FFC4H", 430.0, 180.0);   createLed("FFC6H", 470.0, 175.0);   createLed("FCC5H", 235.0, 230.0);   createLed("FCC3H", 290.0, 230.0);
        createLed("FCC4H", 440.0, 230.0);   createLed("FCC6H", 490.0, 230.0);   createLed("CCP5H", 235.0, 280.0);   createLed("CCP3H", 285.0, 280.0);
        createLed("CCP4H", 440.0, 280.0);   createLed("CCP6H", 490.0,280.0);    createLed("CPP5H", 235.0, 335.0);   createLed("CPP3H", 285.0, 330.0);
        createLed("CPP4H", 435.0, 330.0);   createLed("CPP6H", 490.0, 335.0);   createLed("PPO1", 335.0, 380.0);    createLed("PPO2", 385.0, 380.0);
        createLed("I1", 300.0, 500.0);      createLed("IZ", 361.0, 500.0);      createLed("I2", 422.0, 500.0);      createLed("AFP3H", 330.0, 85.0);

        createLed("AFP4H", 390.0, 85.0);    createLed("AFF5H", 265.0, 120.0);   createLed("AFF6H", 455.0, 120.0);   createLed("FFT7H", 205.0, 170.0);
        createLed("FFC1H", 335.0, 180.0);   createLed("FFC2H", 385.0, 180.0);   createLed("FFT8H", 515.0, 170.0);   createLed("FTT9H", 145.0, 210.0);
        createLed("FTT7H", 185.0, 215.0);   createLed("FCC1H", 335.0, 230.0);   createLed("FCC2H", 385.0, 230.0);   createLed("FTT8H", 540.0, 215.0);
        createLed("FTT10H", 585.0, 210.0);  createLed("TTP7H", 175.0, 280.0);   createLed("CCP1H", 330.0, 280.0);   createLed("CCP2H", 388.0, 280.0);
        createLed("TTP8H", 545, 280.0);     createLed("TPP7H", 190.0, 340.0);   createLed("CPP1H", 335.0, 330.0);   createLed("CPP2H", 388.0, 330.0);
        createLed("TPP8H", 535.0, 340);     createLed("PPO9H", 195.0, 407.0);   createLed("PPO5H", 255.0, 385.0);   createLed("PPO6H", 467.0, 385.0);
        createLed("PPO10H", 530.0, 410.0);  createLed("POO9H", 250.0, 455.0);   createLed("POO3H", 330.0, 430.0);   createLed("POO4H", 390.0, 430.0);
        createLed("POO10H", 470.0, 455.0);  createLed("OI1H", 325.0, 480.0);    createLed("OI2H", 395.0, 480.0);    createLed("EOG", 30.0, 6.0);

        createLed("HEOGR", 100.0, 30.0);      createLed("HEOGL", 30.0, 30.0);      createLed("VEOGU", 65, 0.0);         createLed("VEOGL", 65, 60);
        createLed("REF", 360.0, 306.0);       createLed("GRD", 360.0, 110.0);      createLed("GRD", 700.0, 30.0);

    }
}

void AspectRatioLabel::setPixmap(const QPixmap& pm)
{
    pixmapWidth = pm.width();
    pixmapHeight = pm.height();

    QLabel::setPixmap(pm);
}

void AspectRatioLabel::adapSizeLED(LedIndicator& led, QLabel& impLabel, const QFont& f)
{

    // for the led
    int new_x = static_cast<int>(led.getRelativePosX() * (this->width() - 2*xMargin) + xMargin);
    int new_y = static_cast<int>(led.getRelativePosY() * (this->height() - 2*yMargin) + yMargin);

    led.move(new_x, new_y);
    led.setLedSize(static_cast<int>((this->width() - 2*xMargin) * 0.02));

    // for the impedance displayed inside led
    //new_x = led.getLedSize()/4;
    //new_y = led.getLedSize()/4;

    impLabel.setFont(f);
    impLabel.setScaledContents(true);
    //impLabel.adjustSize();

    // for the name displayed below
    new_x = 1 + led.getLedSize()/6;
    new_y = 1 + led.getLedSize()+2;
    led.name->setFont(f);
    led.name->move(new_x, new_y);
    led.name->adjustSize();
}

void AspectRatioLabel::resizeEvent(QResizeEvent* event)
{

    int fontSize = (this->width() - 2*xMargin) / 150;
    const QFont f( "Arial", fontSize, QFont::AllLowercase);

    for(int i=0; i<ledVector.length(); ++i) {
        adapSizeLED(*ledVector.at(i), *impLabel.at(i), f);
    }

    QLabel::resizeEvent(event);
}

void AspectRatioLabel::moveEvent(QMoveEvent *event) {

    QLabel::moveEvent(event);

}

