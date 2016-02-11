#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase shelterDB = QSqlDatabase::addDatabase("QSQLITE");
    QString databasePath = QCoreApplication::applicationDirPath() +  "/database/shelterDB";

    shelterDB.setDatabaseName(databasePath);

    qDebug() << databasePath;

    if (!shelterDB.open()){
        qDebug("Connection Failed");
    }
    else{
        qDebug("Connection Successful");
    }

    // Sets up Volunteers Table
    QSqlRelationalTableModel *volunteerModel = new QSqlRelationalTableModel(0,shelterDB);
    volunteerModel->setTable("volunteerTable");
    volunteerModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    volunteerModel->select();
    volunteerModel->setHeaderData(1,Qt::Horizontal,tr("First Name"));
    volunteerModel->setHeaderData(2,Qt::Horizontal,tr("Last Name"));
    volunteerModel->setHeaderData(3,Qt::Horizontal,tr("Address"));
    volunteerModel->setHeaderData(4,Qt::Horizontal,tr("Email"));
    volunteerModel->setHeaderData(5,Qt::Horizontal,tr("Phone Number"));

    ui->volunteersTable->setModel(volunteerModel);
    ui->volunteersTable->hideColumn(0);
    ui->volunteersTable->setAlternatingRowColors(true);
    ui->volunteersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->volunteersTable->show();

    // Set Up Cats Table  --- Doesn't Work Yet, Fix in the morning ---
    QSqlRelationalTableModel *catsModel = new QSqlRelationalTableModel(0,shelterDB);
    catsModel->setTable("catsTable");
    catsModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    // Changes the SQL Query from "Select * From table" to "Select (chosen columns) From table"
    catsModel->QSqlQueryModel::setQuery("select ID_NUMBER, NAME, ROOM_NUMBER,TAG_NUMBER,DESCRIPTION,IMAGE  from catsTable");

    catsModel->select();//"select ID_NUMBER, NAME, ROOM_NUMBER,TAG_NUMBER,DESCRIPTION,IMAGE  from catsTable");
    catsModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
    catsModel->setHeaderData(2,Qt::Horizontal,tr("Location"));
    catsModel->setHeaderData(3,Qt::Horizontal,tr("ID Number"));
    catsModel->setHeaderData(4,Qt::Horizontal,tr("Description"));
    catsModel->setHeaderData(5,Qt::Horizontal,tr("Image"));

    ui->catsTable->setModel(catsModel);
    ui->catsTable->hideColumn(0);
    ui->catsTable->setAlternatingRowColors(true);
    ui->catsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->catsTable->show();





    QStringList roomsLabels;
    roomsLabels<< "Room" << "AM Shift" << "PM Shift";
    //ui->roomsTable->setHorizontalHeaderLabels((QStringList() << "Room" << "AM Shift" << "PM Shift"));
    ui->roomsTable->horizontalHeader()->show();
    ui->roomsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->roomsDateEdit->setDate(ui->calendar->selectedDate());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calendar_activated(const QDate &date)
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_catsSearchBar_textChanged(const QString &arg1)
{

    QSqlDatabase shelterDB = QSqlDatabase::addDatabase("QSQLITE");
    shelterDB.setDatabaseName("/home/jared/Desktop/Qt Projects/ShelterDB/shelterDB");

    QSqlRelationalTableModel *catsModel = new QSqlRelationalTableModel(0,shelterDB);
    catsModel->setTable("cats");

    if (ui->catsSearchBar->text() != ""){

        /* Doesn't quite work yet. Also, the SQL Query is wrong. Figure this out tomorrow. */

        QString queryStart = "select ID_NUMBER, NAME, ROOM_NUMBER,TAG_NUMBER,DESCRIPTION,IMAGE from catsTable where";
        QString queryEnd = " in *";
        QString query = queryStart + ui->catsSearchBar->text() + queryEnd;
        catsModel->QSqlQueryModel::setQuery(query);
    }
    else{
        catsModel->QSqlQueryModel::setQuery("select ID_NUMBER, NAME, ROOM_NUMBER,TAG_NUMBER,DESCRIPTION,IMAGE from catsTable");
    }
    ui->catsTable->setModel(catsModel);
    ui->catsTable->hideColumn(0);
    ui->catsTable->setAlternatingRowColors(true);
    ui->catsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->catsTable->show();
}
