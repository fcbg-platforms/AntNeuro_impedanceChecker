#include "mainwindow.h"
#include <math.h>
#include <boost/algorithm/string.hpp>
#include <iostream>


//---------------------------------------------------------------------------
// Layouts
//
// Maps associating the stream's channels to the proper LED for each cap layouts.
//---------------------------------------------------------------------------

static const QMap<int, elec> electrodeMap_209 = {
    {0,  elec{0, "FP1"}},       {1,  elec{1, "FPZ"}},       {2,  elec{2, "FP2"}},       {3,  elec{3, "F7"}},        {4,  elec{4, "F3"}},        {5,  elec{5, "FZ"}},        {6,  elec{6, "F4"}},
    {7,  elec{7, "F8"}},        {8,  elec{8, "FC5"}},       {9,  elec{9, "FC1"}},       {10, elec{10, "FC2"}},      {11, elec{11, "FC6"}},      {12, elec{12, "M1"}},       {13, elec{13, "T7"}},
    {14, elec{14, "C3"}},       {15, elec{15, "CZ"}},       {16, elec{16, "C4"}},       {17, elec{17, "T8"}},       {18, elec{18, "M2"}},       {19, elec{19, "CP5"}},      {20, elec{20, "CP1"}},
    {21, elec{21, "CP2"}},      {22, elec{22, "CP6"}},      {23, elec{23, "P7"}},       {24, elec{24, "P3"}},       {25, elec{25, "PZ"}},       {26, elec{26, "P4"}},       {27, elec{27, "P8"}},
    {28, elec{28, "POZ"}},      {29, elec{29, "O1"}},       {30, elec{62, "OZ"}},       {31, elec{30, "O2"}},       {32, elec{132, "REF"}},     {33, elec{133, "GRD"}}
};

static const QMap<int, elec> electrodeMap_208 = {
    {0,  elec{0,"FP1"}},        {1,  elec{1,"FPZ"}},        {2,  elec{2,"FP2"}},        {3,  elec{3,"F7"}},         {4,  elec{4,"F3"}},         {5,  elec{5,"FZ"}},         {6,  elec{6,"F4"}},
    {7,  elec{7,"F8"}},         {8,  elec{8,"FC5"}},        {9,  elec{9,"FC1"}},        {10, elec{10,"FC2"}},       {11, elec{11,"FC6"}},       {12, elec{12,"M1"}},        {13, elec{13,"T7"}},
    {14, elec{14,"C3"}},        {15, elec{15,"CZ"}},        {16, elec{16,"C4"}},        {17, elec{17,"T8"}},        {18, elec{18,"M2"}},        {19, elec{19,"CP5"}},       {20, elec{20,"CP1"}},
    {21, elec{21, "CP2"}},      {22, elec{22,"CP6"}},       {23, elec{23, "P7"}},       {24, elec{24,"P3"}},        {25, elec{25,"PZ"}},        {26, elec{26,"P4"}},        {27, elec{27,"P8"}},
    {28, elec{28,"POZ"}},       {29, elec{29,"O1"}},        {30, elec{30,"O2"}},        {31, elec{127,"EOG"}},      {32, elec{31,"AF7"}},       {33, elec{32,"AF3"}},       {34, elec{33,"AF4"}},
    {35, elec{34,"AF8"}},       {36, elec{35,"F5"}},        {37, elec{36,"F1"}},        {38, elec{37,"F2"}},        {39, elec{38,"F6"}},        {40, elec{39,"FC3"}},       {41, elec{40,"FCZ"}},
    {42, elec{41,"FC4"}},       {43, elec{42,"C5"}},        {44, elec{43,"C1"}},        {45, elec{44,"C2"}},        {46, elec{45,"C6"}},        {47, elec{46,"CP3"}},       {48, elec{47,"CP4"}},
    {49, elec{48,"P5"}},        {50, elec{49,"P1"}},        {51, elec{50,"P2"}},        {52, elec{51,"P6"}},        {53, elec{52,"PO5"}},       {54, elec{53,"PO3"}},       {55, elec{54,"PO4"}},
    {56, elec{55,"PO6"}},       {57, elec{56,"FT7"}},       {58, elec{57,"FT8"}},       {59, elec{58,"TP7"}},       {60, elec{59,"TP8"}},       {61, elec{60,"PO7"}},       {62, elec{61,"PO8"}},
    {63, elec{62,"OZ"}},        {64, elec{132,"REF"}},      {65, elec{133,"GRD"}}
};

static const QMap<int, elec> electrodeMap_203 = {
    {0,   elec{0,"FP1"}},       {1,   elec{1,"FPZ"}},       {2,   elec{2,"FP2"}},        {3,   elec{3,"F7"}},         {4,   elec{4,"F3"}},         {5,   elec{5,"FZ"}},         {6,   elec{6,"F4"}},
    {7,   elec{7,"F8"}},        {8,   elec{8,"FC5"}},       {9,   elec{9,"FC1"}},        {10,  elec{10,"FC2"}},       {11,  elec{11,"FC6"}},       {12,  elec{12,"M1"}},        {13,  elec{13,"T7"}},
    {14,  elec{14,"C3"}},       {15,  elec{15,"CZ"}},       {16,  elec{16,"C4"}},        {17,  elec{17,"T8"}},        {18,  elec{18,"M2"}},        {19,  elec{19,"CP5"}},       {20,  elec{20,"CP1"}},
    {21,  elec{21, "CP2"}},     {22,  elec{22,"CP6"}},      {23,  elec{23, "P7"}},       {24,  elec{24,"P3"}},        {25,  elec{25,"PZ"}},        {26,  elec{26,"P4"}},        {27,  elec{27,"P8"}},
    {28,  elec{28,"POZ"}},      {29,  elec{29,"O1"}},       {30,  elec{30,"O2"}},        {31,  elec{128,"HEOGR"}},    {32,  elec{31,"AF7"}},       {33,  elec{32,"AF3"}},       {34,  elec{33,"AF4"}},
    {35,  elec{34,"AF8"}},      {36,  elec{35,"F5"}},       {37,  elec{36,"F1"}},        {38,  elec{37,"F2"}},        {39,  elec{38,"F6"}},        {40,  elec{39,"FC3"}},       {41,  elec{40,"FCZ"}},
    {42,  elec{41,"FC4"}},      {43,  elec{42,"C5"}},       {44,  elec{43,"C1"}},        {45,  elec{44,"C2"}},        {46,  elec{45,"C6"}},        {47,  elec{46,"CP3"}},       {48,  elec{47,"CP4"}},
    {49,  elec{48,"P5"}},       {50,  elec{49,"P1"}},       {51,  elec{50,"P2"}},        {52,  elec{51,"P6"}},        {53,  elec{129,"HEOGL"}},    {54,  elec{53,"PO3"}},       {55,  elec{54,"PO4"}},
    {56,  elec{130,"VEOGU"}},   {57,  elec{56,"FT7"}},      {58,  elec{57,"FT8"}},       {59,  elec{58,"TP7"}},       {60,  elec{59,"TP8"}},       {61,  elec{60,"PO7"}},       {62,  elec{61,"PO8"}},
    {63,  elec{131,"VEOGL"}},   {64,  elec{63,"FT9"}},      {65,  elec{64,"FT10"}},      {66,  elec{65,"TPP9H"}},     {67,  elec{66,"TPP10H"}},    {68,  elec{67,"PO9"}},       {69,  elec{68,"PO10"}},
    {70,  elec{69,"P9"}},       {71,  elec{70,"P10"}},      {72,  elec{71,"AFF1"}},      {73,  elec{72,"AFZ"}},       {74,  elec{73,"AFF2"}},      {75,  elec{74,"FFC5H"}},     {76,  elec{75,"FFC3H"}},
    {77,  elec{76,"FFC4H"}},    {78,  elec{77,"FFC6H"}},    {79,  elec{78,"FCC5H"}},     {80,  elec{79,"FCC3H"}},     {81,  elec{80,"FCC4H"}},     {82,  elec{81,"FCC6H"}},     {83,  elec{82,"CCP5H" }},
    {84,  elec{83,"CCP3H"}},    {85,  elec{84,"CCP4H"}},    {86,  elec{85,"CCP6H"}},     {87,  elec{86,"CPP5H"}},     {88,  elec{87,"CPP3H"}},     {89,  elec{88,"CPP4H"}},     {90,  elec{89,"CPP6H"}},
    {91,  elec{90,"PPO1"}},     {92,  elec{91,"PPO2"}},     {93,  elec{92,"I1"}},        {94,  elec{93,"IZ"}},        {95,  elec{94,"I2"}},        {96,  elec{95,"AFP3H"}},     {97,  elec{96,"AFP4H"}},
    {98,  elec{97,"AFF5H"}},    {99,  elec{98,"AFF6H"}},    {100, elec{99,"FFT7H"}},     {101, elec{100,"FFC1H"}},    {102, elec{101,"FFC2H"}},    {103, elec{102,"FFT8H"}},    {104, elec{103,"FTT9H"}},
    {105, elec{104,"FTT7H"}},   {106, elec{105,"FCC1H"}},   {107, elec{106,"FCC2H"}},    {108, elec{107,"FTT8H"}},    {109, elec{108,"FTT10H"}},   {110, elec{109,"TTP7H"}},    {111, elec{110,"CCP1H"}},
    {112, elec{111,"CCP2H"}},   {113, elec{112,"TTP8H"}},   {114, elec{113,"TPP7H"}},    {115, elec{114,"CPP1H"}},    {116, elec{115,"CPP2H"}},    {117, elec{116,"TPP8H"}},    {118, elec{117,"PPO9H"}},
    {119, elec{118,"PPO5H"}},   {120, elec{119,"PPO6H"}},   {121, elec{120,"PPO10H"}},   {122, elec{121,"POO9H"}},    {123, elec{122,"POO3H"}},    {124, elec{123,"POO4H"}},    {125, elec{124,"POO10H"}},
    {126, elec{125,"OI1H"}},    {127, elec{126,"OI2H"}},    {176, elec{132,"REF"}},      {177, elec{134,"GRD"}}
};
//---------------------------------------------------------------------------


// Constructeur
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Q_INIT_RESOURCE(impCheck);

    // Display the eeg layout
    QPixmap image(":/resources/HeadImage.png");
    image = image.scaled(750, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->eegPicture->setScaledContents(true);
    ui->eegPicture->setPixmap(image);

    ui->eegPicture->displayLed();

    // Hide buttons
    ui->Impedance_comboBox->setDisabled(true);
    ui->Impedance_checkBox->setDisabled(true);
    ui->savingBox->setDisabled(true);
    ui->SearchBox->setDisabled(true);
    ui->dispImpedanceLED->setDisabled(true);

    // Fix the size of the electrodes list
    ui->listElectrodes->setRowCount(1);
    ui->listElectrodes->setColumnCount(2);
    ui->listElectrodes->setItem(0, 0, new QTableWidgetItem(QString("FP1                        ")));
    ui->listElectrodes->setItem(0, 1, new QTableWidgetItem(QString("NaN")));
    ui->listElectrodes->resizeRowsToContents();
    ui->listElectrodes->resizeColumnToContents(0);
    ui->listElectrodes->verticalHeader()->setVisible(false);
    ui->listElectrodes->horizontalHeader()->setVisible(false);
    ui->widget_2->setFixedWidth(ui->listElectrodes->columnWidth(0)+ui->listElectrodes->columnWidth(1)+ui->listElectrodes->autoScrollMargin()+ui->listElectrodes->verticalHeader()->width()+10);

    // Keep the good layout even when listElectrodes is hidden.
    QSizePolicy retain = ui->listElectrodes->sizePolicy();
    retain.setRetainSizeWhenHidden(true);
    ui->listElectrodes->setSizePolicy(retain);
    ui->listElectrodes->hide();

    // Define the timer for the loop update.
    this->timer = new QTimer(this);

    // Saving File
    ui->savingFile->setPlaceholderText(QString("filename"));
    ui->savingFile->setDisabled(true);
    ui->savingFileAccept->hide();

    // Search for an electrode
    ui->SearchElectrode->setDisabled(true);

    // capID
    ui->connectButton->setDisabled(true);

    this->highLighted_led = false;

    //-----------------------------------------------------------------------------------------------------
    // Connect SIGNALS TO SLOTS
    //-----------------------------------------------------------------------------------------------------

    // Connect: the Button connect to the function StartStop().
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(startStop()));

    //Connect: the selection of cap ID to the button connect
    connect(ui->capID, SIGNAL(currentIndexChanged(int)), this, SLOT(on_capID(int)));

    // Connect: the Impedance_check to the Impedance_comboBox
    connect(ui->Impedance_checkBox, SIGNAL(stateChanged(int)), this, SLOT(showImpedanceThresholds(void)));

    // Connect: the threshold change
    connect(ui->Impedance_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeThreshold(int)));

    // Connect: when a electrode is highlighted in the listElectrodes
    connect(ui->listElectrodes, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(highlighElectrode(QTableWidgetItem*)));

    // Connect: timer for impedance update (loop).
    connect(timer, SIGNAL(timeout()), this, SLOT(startAcquisition()));

    //Connect: saving button to savingFile
    connect(ui->savingBox, SIGNAL(clicked(bool)), this, SLOT(showFileBox()));

    // Connect: savingButton cancel to delete savingfile name
    connect(ui->savingFileAccept, SIGNAL(rejected()), ui->savingFile, SLOT(clear()));

    //Connect: the savingButton ok to the saving process
    connect(ui->savingFileAccept, SIGNAL(accepted()), this, SLOT(saveToFile()));

    //Connect the searchBox to the searchElectrode line
    connect(ui->SearchBox, SIGNAL(stateChanged(int)), this, SLOT(showSearchElectrode()));

    //Connect: the searchElectrode change to highlight the electrode
    connect(ui->SearchElectrode, SIGNAL(editingFinished()), this, SLOT(highlighElectrode()));

    //Connect: dumps the impedances values when button pressed
    connect(ui->dispImpedanceLED, SIGNAL(clicked(bool)), this, SLOT(dispImpedanceLED()));
}

//-----------------------------------------------------------------------------------------------------
//                                                  Functions
//-----------------------------------------------------------------------------------------------------

// Destructeur
MainWindow::~MainWindow()
{
    delete ui;
}

// Stops the acquisition by closing the impedance stream and the amp
void MainWindow::stopAcquisition()
{
    timer->stop();

    for(int i = 0; i <  ui->eegPicture->ledVector.length(); ++i)
        ui->eegPicture->ledVector.at(i)->setState(gray);
    delete this->impedanceStream;
    delete this->amp;
    ui->connectButton->setText("Connect");
}

// Fills the electrodes list depending on the chosen layout
void MainWindow::fillListElectrodes()
{
    ui->listElectrodes->setRowCount(electrodeMap->size());

    int i = 0;
    for (auto e : electrodeMap->values()) {
        ui->listElectrodes->setItem(i, 0, new QTableWidgetItem(e.name));
        ui->listElectrodes->setItem(i, 1, new QTableWidgetItem(QString("NaN")));
        ++i;
    }

    ui->listElectrodes->show();
}

// Dumps impedance's values in the electrodes list.
void MainWindow::dumpImpedance(int PosInTable, int PosInLed, QString impValue) {

    // for the table
    ui->listElectrodes->setItem(PosInTable, 1, new QTableWidgetItem(impValue));

    // for the impedance displayed on the led
    ui->eegPicture->impLabel.at(PosInLed)->setFixedSize(50,20);
    ui->eegPicture->impLabel.at(PosInLed)->setText(impValue);
    ui->eegPicture->impLabel.at(PosInLed)->adjustSize();
}

//-----------------------------------------------------------------------------------------------------
//                                                  SLOTS
//-----------------------------------------------------------------------------------------------------

// Sorting the amplifiers according to their serial number. First amplifier to connect should be the one with the lowest SN.
template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {

    // initialize original index locations
    std::vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    sort(idx.begin(), idx.end(),
         [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

    return idx;
}

// React to button connect pressed
void MainWindow::startStop(void){

    if ((ui->connectButton->text() == "Connect") || (ui->connectButton->text() == "Failed")) {


        try {
            ui->Impedance_checkBox->setEnabled(true);
            ui->savingBox->setEnabled(true);
            ui->SearchBox->setEnabled(true);
            ui->dispImpedanceLED->setEnabled(true);

            // Instance the ampli and stream
            std::vector<eemagine::sdk::amplifier*>  amps;
            std::vector<std::string> serialTmp;
            amps = fact.getAmplifiers();

            // Check if two amplifiers connected (128Ch)
            if ( amps.size() > 1 ) {

                for (unsigned int i = 0; i < amps.size(); ++i) {
                    serialTmp.push_back(amps.at(i)->getSerialNumber());}

                std::vector<eemagine::sdk::amplifier*>  tmpAmps;

                for (auto i : sort_indexes(serialTmp)) {
                    tmpAmps.push_back(amps.at(i));
                    }
                this->amp = fact.createCascadedAmplifier(tmpAmps); }

            else {
                this->amp = amps.at(0);
            }

            // Impedance Stream's Instanciation
            if ( this->amp )
                this->impedanceStream = this->amp->OpenImpedanceStream(this->refMask);

            // Fill electrodeList according to the ampli
            fillListElectrodes();

            // Define the timer update to be 0.5 sec.
            timer->start(500); // msec
            ui->connectButton->setText("Disconnect");

        } catch(...) {
            QMessageBox ErrorConnectBox;
            ErrorConnectBox.setText("ERROR: Check that the amplifier is plugged to the computer.");
            ErrorConnectBox.exec();
            ui->connectButton->setText("Failed");}
    } else {

        stopAcquisition();
    }
}

// Remove EXG channels from the list for the 128 layout
// Du to the sdk beta version, exg only present for 128.
// I hope it will be fixed in the release

bool removeUnwantedChannels(int pos, int channelCount) {
    // Only for 128 layout
    if ( channelCount > 66 ) {
        // EXG pos to remove
        if ( (pos > 63 && pos < 88) || (pos >  151  &&  pos < 176) ) {
            return true;
        } else return false;
    } else return false;
}

// "MAIN" Update function, connected to a timer
int MainWindow::startAcquisition() {

    try {
        int j = 0;
        double impValue;

        // Get the data
        buf = this->impedanceStream->getData();
        int channelCount = static_cast<int>(buf.getChannelCount());
        QMap<int, elec>::const_iterator it(electrodeMap->begin());

        for(int i = 0; i < channelCount; ++i) {

            // Skip the EXG channels
            if ( removeUnwantedChannels(i, channelCount) ) continue;

            // Convert Ohm in kOhm
            impValue = static_cast<double>(round(buf.data()[i]/1000.00));

            // Update leds' color
            this->ui->eegPicture->ledVector.at(it.value().position)->displayImpedance(impValue);

            // Update the values on the leds.
            if ( impValue >= 100 ) {
                this->dumpImpedance(j, it.value().position, QString(" > 100 "));
            } else {
                this->dumpImpedance(j, it.value().position, QString::number(impValue));
            }
            ++j;
            ++it;
        }
    } catch (...) {
        ui->connectButton->setText("Failed");
        delete this->impedanceStream;
        delete this->amp;
    }
    return 0;
}

// Shows impedances after threshold button pressed
void MainWindow::showImpedanceThresholds(void){

    if(ui->Impedance_checkBox->isChecked())
        ui->Impedance_comboBox->setDisabled(false);
    else
        ui->Impedance_comboBox->setDisabled(true);
}

// Shows fileBox after saving button pressed
void MainWindow::showFileBox(){

    if(ui->savingBox->isChecked()) {
        ui->savingFile->setDisabled(false);
        ui->savingFileAccept->show();
    }
    else {
        ui->savingFile->setDisabled(true);
        ui->savingFile->clear();
        ui->savingFileAccept->hide();
    }
}

// Shows the electrode selected.
void MainWindow::showSearchElectrode(){

    if(ui->SearchBox->isChecked()) {
        ui->SearchElectrode->setDisabled(false);
    }
    else {
        ui->SearchElectrode->clear();
        ui->SearchElectrode->setDisabled(true);
    }
}

// Change the thresholds' values when changed in the box
void MainWindow::changeThreshold(int impThreshold) {

    for(int i=0; i<ui->eegPicture->ledVector.length();++i) {
        ui->eegPicture->ledVector.at(i)->setLedThreshold(impThreshold);
    }
}

// Highlights a specific electrode
void MainWindow::highlighElectrode(int electrode_row, int) {

    ui->eegPicture->ledVector.at(this->highLighted_led)->setHighLighted(false);

    electrode_row = electrodeMap->value(electrode_row).position;

    if (this->highLighted_led != electrode_row) {
        this->highLighted_led = electrode_row;
        ui->eegPicture->ledVector.at(electrode_row)->setHighLighted(true);
    }
}

// Highlights a specific electrode from the table
void MainWindow::highlighElectrode(QTableWidgetItem* item) {

    highlighElectrode(item->row(), item->column());
}

// Highlights specific electrode written in the searchBox.
void MainWindow::highlighElectrode() {

    std::string electrodeName = ui->SearchElectrode->text().toStdString();
    boost::algorithm::to_upper(electrodeName);
    QString QElectrodeName = QString::fromStdString(electrodeName);

    QMap<int, elec>::const_iterator i(electrodeMap->begin());

    while (i != electrodeMap->end()) {
        if ( i.value().name == QElectrodeName ) {
            highlighElectrode((i.key()), 0);
            break;
        }
        ++i;
    }
}

// Selects the layout corresponding to the selected cap
void MainWindow::on_capID(int posID) {

    if (posID == 1) {
        this->electrodeMap = &electrodeMap_209;
        this->refMask = 0xFFFFFFFF;
    }
    else if (posID == 2) {
        this->electrodeMap= &electrodeMap_208;
        this->refMask = 0xFFFFFFFFFFFFFFFF;
    }
    else if (posID == 3) {
        this->electrodeMap= &electrodeMap_203;
        this->refMask = 0xFFFFFFFFFFFFFFFF;
    }

    //Hides all Leds (in case switch to lower density cap, remove new unused led)
    for( int i = 0; i < ui->eegPicture->ledVector.length(); ++i ) {
        ui->eegPicture->ledVector.at(i)->hide();
    }

    // Shows the Leds corresponding to the cap layout.
    QMap<int, elec>::const_iterator i(electrodeMap->begin());

    while (i != electrodeMap->end()) {

        ui->eegPicture->ledVector.at(i.value().position)->show();
        ++i;
    }
    ui->connectButton->setEnabled(true);
}

// Saves to file specified in the box
void MainWindow::saveToFile(void) {

    QString fileName = ui->savingFile->text();
    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite)) {

            QTextStream stream(&file);
            stream << "ELECTRODES IMPEDANCE [kOhms], \n\n";

            for (int i = 0; i < ui->listElectrodes->rowCount(); ++i)
                stream << ui->listElectrodes->item(i,0) << " = " << ui->listElectrodes->item(i,1) << "\n";
        }
        file.close();
    }
}

// Dumps impedances' values on the LED when diplayImpedanceLED box selected
void MainWindow::dispImpedanceLED(void) {
    if(ui->dispImpedanceLED->isChecked()) {
        for(int i=0; i<ui->eegPicture->impLabel.length(); ++i ) {
            ui->eegPicture->impLabel.at(i)->show();
        }
    }
    else {
        for(int i=0; i<ui->eegPicture->impLabel.length(); ++i ) {
            ui->eegPicture->impLabel.at(i)->hide();
        }
    }
}
