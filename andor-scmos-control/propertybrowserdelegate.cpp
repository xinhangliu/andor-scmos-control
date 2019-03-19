#include "propertybrowserdelegate.h"
#include <QLineEdit>
#include <QFile>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QLoggingCategory>
#include <QLabel>
#include <QJsonDocument>
#include <QJsonValue>
#include "mainwindow.h"

PropertyBrowserDelegate::PropertyBrowserDelegate(QObject *parent, QJsonArray *propertyList): QItemDelegate(parent) {
    this->propertyList = *propertyList;
}

QWidget* PropertyBrowserDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &index) const {
    if (index.column() != 0) {
        QJsonValue feature = propertyList.at(index.row());
        QString featureType = feature["type"].toString();
        if (featureType == "integer") {
            QSpinBox *editor = new QSpinBox(parent);
            editor->setMaximum(65536);
            return editor;
        } else if (featureType == "float") {
            QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
            editor->setMaximum(65536.);
            editor->setDecimals(10);
            return editor;
        } else if (featureType == "enum") {
            return new QComboBox(parent);
        } else if (featureType == "bool") {
            return new QCheckBox(parent);
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

void PropertyBrowserDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    auto value = index.model()->data(index, Qt::EditRole);
    if (dynamic_cast<QSpinBox *>(editor) != nullptr) {
        QSpinBox *box = static_cast<QSpinBox *>(editor);
        box->setValue(value.toInt());
        auto min = index.model()->data(index, Qt::UserRole+1).toInt();
        auto max = index.model()->data(index, Qt::UserRole+2).toInt();
        box->setRange(min, max);
    } else if (dynamic_cast<const QDoubleSpinBox *>(editor) != nullptr) {
        QDoubleSpinBox *box = static_cast<QDoubleSpinBox*>(editor);
        box->setValue(value.toDouble());
        auto min = index.model()->data(index, Qt::UserRole+1).toDouble();
        auto max = index.model()->data(index, Qt::UserRole+2).toDouble();
        box->setRange(min, max);
    } else if (dynamic_cast<const QCheckBox *>(editor) != nullptr) {
        auto value = index.model()->data(index, Qt::CheckStateRole);
        QCheckBox *box = static_cast<QCheckBox*>(editor);
        box->setChecked(value.toBool());
    } else if (dynamic_cast<const QComboBox *>(editor) != nullptr) {
        QComboBox *box = static_cast<QComboBox *>(editor);
        QStringList enumStringList = index.model()->data(index, Qt::UserRole+1).toStringList();
        foreach (const QString &v, enumStringList)
            box->addItem(v, v);
        box->setCurrentIndex(box->findText(value.toString()));
    }
}

void PropertyBrowserDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    if (dynamic_cast<QSpinBox *>(editor) != nullptr) {
        QSpinBox *box = static_cast<QSpinBox*>(editor);
        box->interpretText();
        model->setData(index, box->value(), Qt::EditRole);
    } else if (dynamic_cast<const QDoubleSpinBox *>(editor) != nullptr) {
        QDoubleSpinBox *box = static_cast<QDoubleSpinBox*>(editor);
        box->interpretText();
        model->setData(index, box->value(), Qt::EditRole);
    } else if (dynamic_cast<const QCheckBox *>(editor) != nullptr) {
        QCheckBox *box = static_cast<QCheckBox*>(editor);
        model->setData(index, box->isChecked(), Qt::CheckStateRole);
    } else if (dynamic_cast<const QComboBox *>(editor) != nullptr) {
        QComboBox *box = static_cast<QComboBox *>(editor);
        model->setData(index, box->currentText(), Qt::EditRole);
    }
}

void PropertyBrowserDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const {
    editor->setGeometry(option.rect);
}

