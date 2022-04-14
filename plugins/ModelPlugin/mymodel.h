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
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE void populate(int gridSize);
    Q_INVOKABLE void move(int index);

    bool isSolvable();
    void shuffle();
    Q_INVOKABLE bool isSolved();
    Q_INVOKABLE void mix();

private:
    QList<int> m_data;
    int m_gridSize;
};

#endif // MYMODEL_H
