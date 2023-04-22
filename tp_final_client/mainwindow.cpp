#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QTcpSocket>
#include <QDateTime>
#include <QString>
#include <QDebug>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->searchTxt, SIGNAL(textChanged(QString)), this, SLOT(on_lineEdit_textChanged(QString)));
    connect(ui->btnTxt, &QPushButton::clicked, this, &MainWindow::on_btnTxt_clicked);
    QComboBox *myComboBox = findChild<QComboBox*>("type");
    if (myComboBox) {
        QStringList items = {"image", "text", "exec"};
        myComboBox->addItems(items);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setListModel(QStringListModel* model)
{
    ui->listView->setModel(model);
}

void MainWindow::on_btnTxt_clicked()
{

    //récuperer les résultat du formulaire
    QString nom_du_fichier = ui->searchTxt->text();
    QString type_du_fichier = ui->type->currentText();
    QString extention_du_fichier = ui->extention->text();
    QString minSize = ui->minSize->text();
    QString maxSize = ui->maxSize->text();
    QString minDate = ui->minDate-> text();
    QString maxDate = ui->maxDate->text();

    qint64 minSizeInt = minSize.toLongLong();
    qint64 maxSizeInt = maxSize.toLongLong();

    qDebug() << "Nom du fichier : " << nom_du_fichier;
    qDebug() << "Type du fichier : " << type_du_fichier;
    qDebug() << "Extension du fichier : " << extention_du_fichier;
    qDebug() << "Taille minimale : " << minSizeInt;
    qDebug() << "Taille maximale : " << maxSizeInt;
    qDebug() << "Date minimale : " << minDate;
    qDebug() << "Date maximale : " << maxDate;

    QByteArray data;
       QDataStream out(&data, QIODevice::WriteOnly);
       out << nom_du_fichier << type_du_fichier << extention_du_fichier << minSizeInt << maxSizeInt << minDate << maxDate;

       // Créer un thread pour envoyer les données
       SendThread *sendThread = new SendThread(this);
       sendThread->setData(data);
       sendThread->start();
    QStringList list;

//    // Obtenir la référence de la QListView
    QListView* listView = ui->listView;

//    // Créer un modèle pour la liste
    QStringListModel* model = new QStringListModel(list, this);

//    // Affecter le modèle à la QListView
    listView->setModel(model);

}


