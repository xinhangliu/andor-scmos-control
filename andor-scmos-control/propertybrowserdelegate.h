#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QJsonArray>


class PropertyBrowserDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit PropertyBrowserDelegate(QObject *parent = nullptr, QJsonArray *propertyList = nullptr);

    // Create Editor when we construct MyDelegate
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    // Then, we set the Editor
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    // When we modify data, this model reflect the change
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    // Give the SpinBox the info on size and location
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool isInit;

signals:

public slots:

private:
    QJsonArray propertyList;

};

#endif // MYDELEGATE_H
