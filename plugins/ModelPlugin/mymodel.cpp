#include "mymodel.h"
#include <QDebug>
#include <functional>
MyModel::MyModel(QObject *parent): QAbstractListModel(parent){
    setSize(16);
}

int MyModel::rowCount(const QModelIndex &parent) const{
    if(parent.isValid()){
        return 0;
    }
    return m_data.size();
}

QVariant MyModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }
    switch (role) {
    case ValueRole:
        return QVariant(m_data.at(index.row()));
    default:
        return QVariant();
    }
}

QHash<int,QByteArray> MyModel::roleNames() const{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[ValueRole] = "value";
    return roles;
}

bool MyModel::setData(const QModelIndex &index, const QVariant value, int role){
    if(!index.isValid()){
        return false;
    }
    switch (role) {
    case ValueRole: m_data[index.row()] = value.toInt();
        break;
    default: return false;
    }
    emit dataChanged(index,index,QVector<int>() << role);
    return true;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const{
    if(!index.isValid()){
        return Qt::ItemIsEnabled;
    }
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

int MyModel::getValue(int ind) const{
    return m_data[ind];
}

bool MyModel::setValue(int ind, int value){
    if(ind < 0 || ind >= m_data.size()){
        return false;
    }
    m_data[ind] = value;
    QModelIndex mIndex = this->index(ind);
    dataChanged(mIndex,mIndex,QVector<int>() << ValueRole);
    return true;
}

void MyModel::appendValue(int value){
    m_data.append(value);
    QModelIndex mIndex = this->index(m_data.size()-1);
    dataChanged(mIndex,mIndex,QVector<int>() << ValueRole);
}

int MyModel::size() const{
    return m_data.size();
}

void MyModel::setSize(int size){
    if(m_data.size()!=0)
        m_data.clear();
    for(int i = 1; i <=size; i++){
        beginInsertRows(QModelIndex(),m_data.size(),m_data.size());
        m_data.append(i);
        endInsertRows();
    }
}

void MyModel::move(int index, int gridSize){
    if(index >= m_data.size() || gridSize*gridSize != m_data.size())
        return;
    std::function<void(int,int)> beginMove = [&](int first, int second){
        beginMoveRows(QModelIndex(), first,first,QModelIndex(),second);
        endMoveRows();
    };
    std::function<void(int,int)> swap = [&](int first, int second){
        int tmp = getValue(first);
        setValue(first, getValue(second));
        setValue(second, tmp);
    };
    if(gridSize*gridSize != size())
        return;
    int j = index % gridSize;
    int i = index/gridSize;
    if(i>0){
        if(getValue(j+(i-1)*gridSize) == gridSize*gridSize){    //up+
            beginMove(j+i*gridSize,j+((i-1)*gridSize));
            beginMove((j+1)+(i-1)*gridSize,j+((i)*gridSize)+1);
            swap(j+i*gridSize,j+((i-1)*gridSize));
            return;
        }
    }
    if(j>0){
        if(getValue(j-1+i*gridSize) == gridSize*gridSize){       //left+
            beginMove(j+(i*gridSize),(j-1)+i*gridSize);
            swap(j+(i*gridSize),(j-1)+i*gridSize);
            return;
        }
    }
    if(j<gridSize-1){
        if(getValue(j+1+i*gridSize) == gridSize*gridSize){      //right+
            beginMove(j+i*gridSize,j+1+i*gridSize+1);
            swap(j+i*gridSize,j+1+i*gridSize);
            return;
        }
    }
    if(i<gridSize-1){
        if(getValue(j+(i+1)*gridSize) == gridSize*gridSize){ //down+
            beginMove(j+i*gridSize,j+((i+1)*gridSize));
            beginMove((j)+(i+1)*gridSize,j+(i*gridSize));
            swap(j+i*gridSize,j+((i+1)*gridSize));
            return;
        }
    }
}
