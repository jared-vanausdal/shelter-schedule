#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtSql>
#include <QtDebug>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_calendar_activated(const QDate &date);

    void on_catsSearchBar_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
