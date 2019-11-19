#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


#define EEGO_SDK_BIND_STATIC // How to bind the sdk library.
#include "eemagine/sdk/factory.h"

namespace Ui {
class MainWindow;
}

// Structure containing an electrode position and name.
struct elec{
    int position;
    QString name;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

//----------------------------------------------------------
// Methods
//----------------------------------------------------------

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//----------------------------------------------------------
// Slots
//----------------------------------------------------------

public slots:
    void startStop(void);
    int startAcquisition(void);
    void showImpedanceThresholds(void);
    void changeThreshold(int);
    void highlighElectrode(int, int);
    void highlighElectrode(QTableWidgetItem*);
    void highlighElectrode();
    void showFileBox();
    void showSearchElectrode();
    void saveToFile();
    void on_capID(int);
    void dispImpedanceLED(void);

private:
    void dumpImpedance(int, int, QString);
    void fillListElectrodes();
    void stopAcquisition();

//----------------------------------------------------------
// Attributes
//----------------------------------------------------------

private:
    Ui::MainWindow *ui;

    eemagine::sdk::factory fact;
    eemagine::sdk::amplifier* amp;
    eemagine::sdk::stream* impedanceStream;
    eemagine::sdk::buffer buf;

    const QMap<int, elec>* electrodeMap;
     unsigned long long refMask;

    int highLighted_led;
    QTimer *timer;

};

#endif // MAINWINDOW_H
