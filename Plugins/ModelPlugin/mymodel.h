#ifndef MYMODEL_H
#define MYMODEL_H
#include <QObject>
#include <QAbstractListModel>
#include <QModelIndex>
#include <QByteArray>
class MyModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int gridSize READ getGridSize)
public:
    enum Roles{
       ValueRole = Qt::UserRole + 1,
    };
    MyModel(QObject* parent = 0);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE void move(int index);

    Q_INVOKABLE bool isSolved();
    Q_INVOKABLE void mix();
    int getGridSize() const;
private:
    QList<int> m_data;
    int m_gridSize;

    void populate(int gridSize);
    bool isSolvable();
    void shuffle();
};

#endif // MYMODEL_H
