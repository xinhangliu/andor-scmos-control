#include "server.h"
#include "ui_serverwindow.h"
#include <iostream>
#include "utils.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QFont>
#include <QFontDatabase>
#include <QDateTime>

Server::Server(QWidget *parent) : QDialog(parent), ui(new Ui::ServerWindow) {
    ui->setupUi(this);
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowFlags(Qt::Window);
    ui->edtServerDirPath->setText(QDir::currentPath());
    ui->horizontalLayout_3->setAlignment(Qt::AlignRight);
    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setStyleHint(QFont::TypeWriter);
    ui->tboxLog->setFont(font);
    ui->tboxLog->setReadOnly(true);
    ui->tboxLog->setWordWrapMode(QTextOption::NoWrap);
    ui->edtAddress->setEnabled(false);
    ui->edtAddress->setText("0.0.0.0");

}

void Server::log(const QString &msg) {
    ui->tboxLog->append(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + " " + msg);
}

void Server::processConnection() {
    socket = server->nextPendingConnection();
    //socket->write("hello, I'm server.\n", 18);
    this->log("<-- " + socket->peerAddress().toString() + ":" + QString::number(socket->peerPort()));
    connect(socket, &QTcpSocket::readyRead, this, &Server::rec);
    connect(socket, &QTcpSocket::disconnected, this, &Server::closingClient);
}

void Server::rec() {
    char rxBuffer[65536] = {0};
    socket->read(rxBuffer, 65536);
    this->log("Request: " + QString(rxBuffer));
    Request req = parseRequest(rxBuffer);
    emit(newRequest(req));
}

void Server::ack(int retcode) {
    socket->write(QString(retcode).toStdString().c_str(), 1);
    this->log("Ack: " + QString::number(retcode));
    socket->disconnectFromHost();
    this->log("socket closed");
}

Request Server::parseRequest(const char *requestData) {
    Request req;
    QStringList itemList = QString().fromStdString(requestData).split(';', QString::SkipEmptyParts);
    for (QString &item: itemList) {
        QStringList kv = item.split(':');
        if (kv[0] == 'i') {
            req.id = kv[1];
        } else if (kv[0] == 'm') {
            req.method = kv[1];
        } else if (kv[0] == 'p') {
            QStringList pList;
            if (kv[1].contains(',')) {
                pList = kv[1].split(',', QString::SkipEmptyParts);
            } else {
                pList.append(kv[1]);
            }
            req.parameters = pList;
        }
    }
    return req;
}

void Server::closingClient() {
    socket->deleteLater();
}

Server::~Server() {
    delete ui;
}

void Server::on_btnServerStart_clicked(bool checked) {
    if (checked) {
        server = new QTcpServer(this);
        quint16 port = static_cast<quint16>(ui->boxServerPort->value());
        connect(server, &QTcpServer::newConnection, this, &Server::processConnection);
        if (!server->listen(QHostAddress::Any, port)) {
            this->log("Server could not start");
            ui->btnServerStart->setChecked(false);
        } else {
            ui->btnServerStart->setText("Stop");
            this->log("Server is listening on port " + QString::number(port));
            //this->setVisible(false);
            emit this->serverStateChanged(true);
        }
    } else {
        if (server != nullptr) {
            server->close();
            server->deleteLater();
            server = nullptr;
            ui->btnServerStart->setText("Run");
            this->log("Server stopped");
            emit this->serverStateChanged(false);
        }
        ui->btnServerStart->setChecked(false);
    }
}

void Server::on_btnServerDirSelect_clicked() {
    QFileDialog fd(this);
    fd.setFileMode(QFileDialog::DirectoryOnly);
    fd.exec();
    ui->edtServerDirPath->setText(fd.directory().path());
    std::cout << saveDir.toStdString() << std::endl;
}

void Server::on_edtServerDirPath_textChanged(const QString &newText)
{
    saveDir = newText;
}
