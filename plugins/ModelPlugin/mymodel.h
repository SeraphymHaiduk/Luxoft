#ifndef MYMODEL_H
#define MYMODEL_H
#include <QObject>
#include <QAbstractListModel>
#include <QModelIndex>
#include <QByteArray>
class MyModel: public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles{
       ValueRole = Qt::UserRole + 1,
    };
    MyModel(QObject* parent = 0);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int,QByteArray> roleNames() const;
    virtual bool setData(const QModelIndex &index,const QVariant value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    Q_INVOKABLE int getValue(int ind) const;
    Q_INVOKABLE bool setValue(int ind,int value);
    Q_INVOKABLE void appendValue(int value);
    Q_INVOKABLE int size() const;
    Q_INVOKABLE void setSize(int size);
    Q_INVOKABLE void move(int first,int second);
private:
    QList<int> m_data;
};

#endif // MYMODEL_H
