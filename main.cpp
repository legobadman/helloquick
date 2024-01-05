#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "selfdefinedqmltype.h"
#include <QQmlContext>
#include "mytest.h"
#include "quick_parameter.h"
#include "quick_node.h"
#include "models/GraphModel.h"
#include "models/tree_model.h"
#include "models/tree_item.h"
#include "qanNavigable.h"
#include "qanGrid.h"
#include "qanLineGrid.h"
#include "qanNavigablePreview.h"
#include <QFontDatabase>
#include <QSurfaceFormat>
#include <QTreeView>
#include "models/GraphsTreeModel.h"

//#define TEST_TREE_MODEL


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

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
    graphM->appendNode("17d801b-CreateCube", "CreateCube", { 0, 0 });
    graphM->appendNode("d8b3fc3d-ParticlesWrangle", "ParticlesWrangle", {400, 400});
    graphM->addLink({ "17d801b-CreateCube","prim" }, { "d8b3fc3d-ParticlesWrangle", "prim" });

    GraphModel* subg2 = nullptr, *subg = nullptr;
    {
        subg = new GraphModel("aaa");
        {
            GraphModel* ssubg = new GraphModel("bbb");
            ssubg->appendNode("0x84g654-SubInput", "SubInput", {0,0});
            ssubg->appendNode("0x865754-SubOutput", "SubOutput", { 400, 400 });
            ssubg->addLink({"0x84g654-SubInput", "port"}, {"0x865754-SubOutput", "port"});
            subg->appendSubgraphNode("a75hs832-bbb", "bbb", {
                "bbb",
                {
                    {"input", "int", ParamControl::Lineddit},
                    {"SRC", ""}
                },
                {
                    {"output", "int"},
                    {"DST", ""}
                }
            }, ssubg, { 150, 150 });
        }
        subg->appendNode("74235gtbeer-SubInput", "SubInput", { 0, 0 });
        subg->appendNode("445gfdggre-SubOutput", "SubOutput", { 800, 800 });
        subg->addLink({"74235gtbeer-SubInput", "port"}, {"445gfdggre-SubOutput", "port"});

        graphM->appendSubgraphNode("cgrewg-aaa", "aaa", {
            "aaa",
            {
                {"code", "string", ParamControl::Multiline},
                {"params", "dict"},
                {"SRC", ""}
            },
            {
                {"result", ""},
                {"DST", ""}
            }
        }, subg, {400, 0});

        subg2 = new GraphModel("aaa");
        {
            GraphModel* ssubg = new GraphModel("bbb");
            ssubg->appendNode("abn64fs-SubInput", "SubInput", { 0,0 });
            ssubg->appendNode("gv287tr-SubOutput", "SubOutput", { 400, 400 });
            ssubg->addLink({ "abn64fs-SubInput", "port" }, { "gv287tr-SubOutput", "port" });
            subg2->appendSubgraphNode("6435hege-bbb", "bbb", {
                "bbb",
                {
                    {"input", "int", ParamControl::Lineddit},
                    {"SRC", ""}
                },
                {
                    {"output", "int"},
                    {"DST", ""}
                }
            }, ssubg, { 150, 150 });
        }
        subg2->appendNode("abr37465-SubInput", "SubInput", { 0, 0 });
        subg2->appendNode("jnmtyret-SubOutput", "SubOutput", { 800, 800 });
        subg2->addLink({ "abr37465-SubInput", "port" }, { "jnmtyret-SubOutput", "port" });

        graphM->appendSubgraphNode("ghr56443g-aaa", "aaa", {
            "aaa",
            {
                {"code", "string", ParamControl::Multiline},
                {"params", "dict"},
                {"SRC", ""}
            },
            {
                {"result", ""},
                {"DST", ""}
            }
        }, subg2, { 900, 0 });
    }

    GraphsTreeModel* pTreeModel = new GraphsTreeModel(graphM);

    QStandardItemModel* pTree2 = new QStandardItemModel;
    QStandardItem* pItem = new QStandardItem("item1");
    {
        QStandardItem* pItem_ = new QStandardItem("item11");
        QStandardItem* pItem__ = new QStandardItem("item12");
        pItem->appendRow(pItem_);
        pItem->appendRow(pItem__);
    }
    QStandardItem* pItem2 = new QStandardItem("item2");
    {
        QStandardItem* pItem_ = new QStandardItem("item21");
        QStandardItem* pItem__ = new QStandardItem("item22");
        pItem2->appendRow(pItem_);
        pItem2->appendRow(pItem__);
    }
    pTree2->appendRow(pItem);
    pTree2->appendRow(pItem2);


    auto america = new TreeItem("America");
    auto asia = new TreeItem("Asia");
    auto europe = new TreeItem("Europe");
    auto brazil = new TreeItem("Brazil");
    auto canada = new TreeItem("Canada");
    auto italy = new TreeItem("Italy");
    auto portugal = new TreeItem("Portugal");

    auto treeModel = new TreeModel();
    treeModel->addTopLevelItem(america);
    treeModel->addTopLevelItem(asia);
    treeModel->addTopLevelItem(europe);
    treeModel->addItem(america, brazil);
    treeModel->addItem(america, canada);
    treeModel->addItem(europe, italy);
    treeModel->addItem(europe, portugal);


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

#ifndef TEST_TREE_MODEL
    engine.rootContext()->setContextProperty("nodesModel", graphM);
    engine.rootContext()->setContextProperty("treeModel", pTreeModel);

    //engine.load(QUrl(QStringLiteral("qrc:/qml/testNode.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/qml/testGraphEditor.qml")));
    //engine.load(QUrl(QStringLiteral("qrc:/qml/autoload-static/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
#else
    QTreeView tree;
    tree.setModel(pTree2);
    tree.show();
    return app.exec();
#endif
}