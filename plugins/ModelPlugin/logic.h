#ifndef LOGIC_H
#define LOGIC_H
#include <QObject>
#include "mymodel.h"
#include <QQmlEngine>
#include <QJSEngine>
class Logic: public QObject
{
    Q_OBJECT
public:
    Logic(QObject *parent = 0);
    Q_INVOKABLE bool moveTile(MyModel* model, int index, int gridSize);
    Q_INVOKABLE bool isSolvable(MyModel* model, int gridSize);
    Q_INVOKABLE void shuffle(MyModel* model, int gridSize);
    Q_INVOKABLE bool isSolved(MyModel* model, int gridSize);
    Q_INVOKABLE void mix(MyModel* model, int gridSize);

    void gridSizeError(int gridSize);
};

static QObject* logicProvider(QQmlEngine *engine, QJSEngine *scriptEngine){
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return new Logic();
}

#endif // LOGIC_H
