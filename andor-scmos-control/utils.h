#ifndef UTILS_H
#define UTILS_H
#include "atcore.h"
#include <QString>
#include <QString>
#include <QStringList>

struct Request {
    QString id;
    QString method;
    QStringList parameters;
};

typedef struct Request Request;

#endif // UTILS_H
