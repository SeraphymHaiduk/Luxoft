#include "logic.h"
#include <time.h>
#include <QDebug>
Logic::Logic(QObject* parent): QObject(parent){}

bool Logic::isSolvable(MyModel* model, int gridSize){
    if(gridSize*gridSize != model->size()){
        gridSizeError(gridSize);
        return false;
    }
    int e = 0;
        for(int i = 0; i < gridSize*gridSize; i++){
            if(model->getValue(i) == gridSize*gridSize)
                e = i+1;
        }
        int n = 0;
        for(int i = 0; i < gridSize*gridSize-1; i++){
            if(model->getValue(i) != gridSize*gridSize && model->getValue(i+1) != gridSize*gridSize){
                for(int j = i+1; j < gridSize*gridSize; j++){
                    if(model->getValue(i) > model->getValue(j)){
                        n += 1;
                    }
                }
            }
        }
        return !((n+e)%2);
}
void Logic::shuffle(MyModel* model, int gridSize){
    if(gridSize*gridSize != model->size()){
        gridSizeError(gridSize);
        return;
    }
    srand(time(NULL));
    for(int i = 0; i < gridSize*gridSize;i++){
        int tmp = model->getValue(i);
        int randI = rand()%(gridSize*gridSize);
        model->setValue(i, model->getValue(randI));
        model->setValue(randI,tmp);
    }
}
bool Logic::isSolved(MyModel* model, int gridSize){
    if(gridSize*gridSize != model->size()){
        gridSizeError(gridSize);
        return false;
    }
    if(model->getValue(gridSize*gridSize-1) != gridSize*gridSize){
            return false;
        }
        for(int j = 0; j < gridSize*gridSize; j++){
            if(j+1 != model->getValue(j)){
                return false;
            }
        }
        return true;
}
void Logic::mix(MyModel* model, int gridSize){
    do{
        shuffle(model,gridSize);
        qDebug() << ("new model values");
    } while(!isSolvable(model,gridSize));
    qDebug() << ("new combination successfully found");
}

void Logic::gridSizeError(int gridSize) {
    qDebug() << "Uncorrect size of grid: " << gridSize;
}
