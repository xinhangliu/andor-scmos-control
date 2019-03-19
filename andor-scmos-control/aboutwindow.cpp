#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AboutWindow) {
    ui->setupUi(this);
    setWindowTitle("About");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);
    ui->horizontalLayout->setAlignment(Qt::AlignHCenter);
    QPixmap ico = QPixmap(":/assets/icon.ico");
    ico.scaled(ui->icon->width(), ui->icon->height(), Qt::KeepAspectRatio);
    ui->icon->setPixmap(ico);
    ui->icon->setScaledContents(true);
    ui->icon->setMargin(16);
    ui->appName->setAlignment(Qt::AlignHCenter);
    ui->appName->setText("<h2>Andor sCMOS Control</h2>");
    ui->version->setAlignment(Qt::AlignHCenter);
    ui->version->setText("Versionn 1.0.0");
    ui->description->setAlignment(Qt::AlignHCenter);
    ui->description->setWordWrap(true);
    ui->description->setOpenExternalLinks(true);
    ui->description->setText("A GUI application for Andor sCMOS, based on Qt framework. More Information can be found on <a href=\"https://github.com/xinhangliu/andor-scmos-control\">GitHub repo</a>.");
}

AboutWindow::~AboutWindow() {
    delete ui;
}
