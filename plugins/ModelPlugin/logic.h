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
    void gridSizeError(int gridSize);
};

static QObject* logicProvider(QQmlEngine *engine, QJSEngine *scriptEngine){
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return new Logic();
}

#endif // LOGIC_H
