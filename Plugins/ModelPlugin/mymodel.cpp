#include "mymodel.h"
#include <QDebug>
#include <algorithm>
#include <time.h>
MyModel::MyModel(QObject *parent): QAbstractListModel(parent){
    populate(4);
}

int MyModel::rowCount(const QModelIndex &parent = QModelIndex()) const{
    return m_data.size();
}

QVariant MyModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }
    switch (role) {
    case ValueRole:
        return m_data.at(index.row());
    default:
        return QVariant();
    }
}

QHash<int,QByteArray> MyModel::roleNames() const{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[ValueRole] = "value";
    return roles;
}

void MyModel::populate(int gridSize){
    if(gridSize <= 0){
        return;
    }
    if(m_data.size()!=0)
        m_data.clear();
    m_gridSize = gridSize;
    beginInsertRows(QModelIndex(),m_data.size(),m_gridSize*m_gridSize-1);
    for(int i = 1; i <= gridSize*gridSize; i++){
        m_data.append(i);
    }
    endInsertRows();
}

void MyModel::move(int index){
    if(index >= m_data.size())
        return;
    int j = index % m_gridSize;
    int i = index/m_gridSize;
    int first, second;
    if(i>0){
        if(m_data[j+(i-1)*m_gridSize] == m_data.size()){    //up+
            first = j+i*m_gridSize;
            second = j+((i-1)*m_gridSize);
            beginMoveRows(QModelIndex(), first,first,QModelIndex(),second);
                m_data.move(first,second);
            endMoveRows();
            first = (j+1)+(i-1)*m_gridSize;
            second = j+((i)*m_gridSize)+1;
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second-1);
            endMoveRows();
            return;
        }
    }
    if(j>0){
        if(m_data[j-1+i*m_gridSize] == m_data.size()){       //left+
            first = j+(i*m_gridSize);
            second = (j-1)+i*m_gridSize;
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second);
            endMoveRows();
            return;
        }
    }
    if(j<m_gridSize-1){
        if(m_data[j+1+i*m_gridSize] == m_data.size()){      //right+
            first = j+i*m_gridSize;
            second = j+1+i*m_gridSize+1;
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second);
            endMoveRows();
            return;
        }
    }
    if(i<m_gridSize-1){
        if(m_data[j+(i+1)*m_gridSize] == m_data.size()){ //down+
            first = j+i*m_gridSize;
            second = j+((i+1)*m_gridSize);
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second-1);
            endMoveRows();
            first = (j)+(i+1)*m_gridSize;
            second = j+(i*m_gridSize);
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second);
            endMoveRows();
            return;
        }
    }
}


bool MyModel::isSolvable(){
    qDebug() << "is solvable?";
    qDebug() << m_gridSize;
    int e = 0;
    for(int i = 0; i < m_data.size(); i++){
        if(m_data[i] == m_data.size())
            e = i/m_gridSize+1;
    }
    int n = 0;
    for(int i = 0; i < m_data.size()-1; i++){
        if(m_data[i] != m_data.size() && m_data[i+1] != m_data.size()){
            for(int j = i+1; j < m_data.size(); j++){
                if(m_data[i] > m_data[j]){
                    n += 1;
                }
            }
        }
    }
    return !((n+e)%2);
}
void MyModel::shuffle(){
    srand(time(NULL));
    for(int i = 0; i < m_data.size();i++){
        int tmp = m_data[i];
        int randI = rand()%m_data.size();
        m_data[i] = m_data[randI];
        m_data[randI] = tmp;
    }
    QModelIndex topLeft = this->index(0);
    QModelIndex bottomRight = this->index(m_data.size()-1);
    emit dataChanged(topLeft,bottomRight);
}
bool MyModel::isSolved(){
    if(m_data[m_data.size()-1] != m_data.size()){
        return false;
    }
    return std::is_sorted(m_data.begin(),m_data.end());
}
void MyModel::mix(){
    do{
        shuffle();
        qDebug() << ("new model values");
    } while(!isSolvable());
    qDebug() << ("new combination successfully found");
}

int MyModel::getGridSize() const{
    return m_gridSize;
}

