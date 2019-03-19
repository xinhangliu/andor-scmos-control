#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QTcpSocket>
#include <QTcpServer>
#include "utils.h"

namespace Ui {
class ServerWindow;
}

class Server : public QDialog
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();
    QTcpSocket *socket;
    QString saveDir;
    void log(const QString &msg);
signals:
    void newRequest(Request);
    void serverStateChanged(bool isRunning);

public slots:
    void processConnection();
    void rec();
    void closingClient();
    void ack(int);
    void on_btnServerStart_clicked(bool);

private:
    Ui::ServerWindow *ui;
    QTcpServer *server = nullptr;
    Request parseRequest(const char *requestData);

private slots:
    void on_btnServerDirSelect_clicked();
    void on_edtServerDirPath_textChanged(const QString &arg1);
};

#endif // SERVER_H
