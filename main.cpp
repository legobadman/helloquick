#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "selfdefinedqmltype.h"
#include <QQmlContext>
#include "mytest.h"
#include "quick_parameter.h"
#include "quick_node.h"
#include "models/GraphModel.h"
#include "qanNavigable.h"
#include "qanGrid.h"
#include "qanLineGrid.h"
#include "qanNavigablePreview.h"
#include <QFontDatabase>
#include <QSurfaceFormat>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);
    QSurfaceFormat::setDefaultFormat(format);

    QQmlApplicationEngine engine;

    QFontDatabase::addApplicationFont("qrc:/font/MiSans/MiSans-Thin.ttf");
    QFontDatabase::addApplicationFont("qrc:/font/MiSans/MiSans-Semibold.ttf");
    QFontDatabase::addApplicationFont("qrc:/font/MiSans/MiSans-Regular.ttf");
    QFontDatabase::addApplicationFont("qrc:/font/MiSans/MiSans-Normal.ttf");
    QFontDatabase::addApplicationFont("qrc:/font/MiSans/MiSans-Medium.ttf");
    QFontDatabase::addApplicationFont("qrc:/font/MiSans/MiSans-Light.ttf");
    QFontDatabase::addApplicationFont("qrc:/font/MiSans/MiSans-Heavy.ttf");
    QFontDatabase::addApplicationFont("qrc:/font/MiSans/MiSans-ExtraLight.ttf");
    QFontDatabase::addApplicationFont("qrc:/font/MiSans/MiSans-Demibold.ttf");
    QFontDatabase::addApplicationFont("qrc:/font/MiSans/MiSans-Bold.ttf");

    QFont font("MiSans", 10);
    app.setFont(font);


    //MyTest* test = new MyTest;
    //engine.rootContext()->setContextProperty("myTestQml", test);

    //qmlRegisterType<MyTest>("MyTestImportUri", 1, 0, "MyTestQmlName");

    qRegisterMetaType<ZQuickParam::CONTROL_TYPE>("ZQuickParam::CONTROL_TYPE");
    qmlRegisterType<ZQuickParam>("ZQuickParam", 1, 0, "ZQuickParam");
    qmlRegisterType<ZQuickNode>("ZQuickNode", 1, 0, "ZQuickNode");

    qRegisterMetaType<ParamsModel*>("ParamsModel*");
    qRegisterMetaType<LinkModel*>("LinkModel*");

    qmlRegisterType<qan::Navigable>("QuickQanava", 2, 0, "Navigable");
    qmlRegisterType<qan::NavigablePreview >("QuickQanava", 2, 0, "NavigablePreview");
    qmlRegisterType<qan::OrthoGrid>("QuickQanava", 2, 0, "OrthoGrid");
    qmlRegisterType<qan::impl::GridLine>("QuickQanava", 2, 0, "GridLine");
    qmlRegisterType<qan::LineGrid>("QuickQanava", 2, 0, "AbstractLineGrid");

    qmlRegisterUncreatableType<ParamControl>("zeno.enum", 1, 0, "ParamControl", "Not creatable as it is an enum type");

    //QQmlComponent comp(&engine, QUrl(QStringLiteral("qrc:/qml/ZParam2.qml")));
    //QObject* myObject = comp.create();
    //ZQuickParam* item = qobject_cast<ZQuickParam*>(myObject);

    GraphModel* graphM = new GraphModel("main");
    graphM->appendNode("17d801b-CreateCube", "CreateCube", { 100, 100 });
    graphM->appendNode("d8b3fc3d-ParticlesWrangle", "ParticlesWrangle", {400, 400});
    graphM->addLink({ "17d801b-CreateCube","prim" }, { "d8b3fc3d-ParticlesWrangle", "prim" });

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [=]() {
        if (false) {
            QModelIndex idx = graphM->index(0, 0);
            //nodesModel->updateParamName(idx, 0, "pos2");
            //nodesModel->removeParam(idx, 0);

            ParamsModel* params = graphM->params(idx);
            //params->removeRow(1);
            //params->addParam({ true, "fuckme", "string", ParamControl::Multiline });

            params->setData(params->index(0, 0), "newName", ROLE_OBJNAME);

            //nodesModel->setData(idx, "FUCKQML", ROLE_OBJNAME);
        }

        if (false) {
            //test append node.
            graphM->appendNode("dfe3fc3d-GetFrameNum", "GetFrameNum", { 400, 400 });
        }

        if (false) {
            graphM->removeNode("d8b3fc3d-ParticlesWrangle");
        }

        if (false) {
            graphM->addLink({ "17d801b-CreateCube","DST" }, { "d8b3fc3d-ParticlesWrangle", "zfxCode" });
        }

        if (false) {
            graphM->addLink({ "17d801b-CreateCube","prim" }, { "d8b3fc3d-ParticlesWrangle", "prim" });
        }

        if (false) {
            graphM->removeLink(1);
        }

        if (false) {
            graphM->setData(graphM->index(0, 0), QVariantList({0, 0}), ROLE_OBJPOS);

        }

    });
    timer.start(1000);

    engine.rootContext()->setContextProperty("nodesModel", graphM);

    //engine.load(QUrl(QStringLiteral("qrc:/qml/testNode.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/qml/navigable.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}