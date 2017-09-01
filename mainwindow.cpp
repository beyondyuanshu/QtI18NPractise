#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTranslator>
#include <QDebug>

#include "utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    , languageMap(QMap<int, QString>())
    , customLabel(QNUMERIC_H)
{
    ui->setupUi(this);

    // init language map
    languageMap.insert(0, QLocale::system().name());
    languageMap.insert(1, "en_US");
    languageMap.insert(2, "zh_cn");

    customLabel = new QLabel(this);
    ui->verticalLayout->addWidget(customLabel);

    QString currentLocalName = Utils::getLocalName();
    if (languageMap.values().contains(currentLocalName)) {
        ui->comboBox->setCurrentIndex(languageMap.key(currentLocalName));
    }

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onLanguageSelectChanged(int)));

    retranslateCustomUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        // retranslateUi contains clear comboBox, so disconnect first.
        disconnect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
                   this, SLOT(onLanguageSelectChanged(int)));
        ui->retranslateUi(this);
        connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
                this, SLOT(onLanguageSelectChanged(int)));
        ui->label->setText(tr("Hello,Qt."));

        retranslateCustomUi();
    }

    QMainWindow::changeEvent(event);
}

void MainWindow::onLanguageSelectChanged(int index)
{
    if (languageMap.size() < index + 1)
        return;

    bool isEffectImmediately = ui->checkBox->isChecked();
    if (!isEffectImmediately) {
        QMessageBox::information(this, tr("Hint"), tr("Effect when restart the app."));
    } else {
        // TODO: should install one times.
        QTranslator *translator = new QTranslator(this);
        translator->load(Utils::findQmFile(languageMap.value(index)));
        qApp->installTranslator(translator);
    }

    Utils::setLocalName(languageMap.value(index));
}

void MainWindow::retranslateCustomUi()
{
    customLabel->setText(tr("I'm custom label, not in designer."));
}
