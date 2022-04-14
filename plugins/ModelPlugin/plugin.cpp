#include "plugin.h"
#include "mymodel.h"
//#include "logic.h"
void Plugin::registerTypes(const char *uri){
    qmlRegisterType<MyModel>(uri, 1, 0, "MyModel");
}
