#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void onLanguageSelectChanged(int index);

private:
    void retranslateCustomUi();

private:
    Ui::MainWindow *ui;

    QMap<int, QString> languageMap;
    QLabel *customLabel;
};

#endif // MAINWINDOW_H
