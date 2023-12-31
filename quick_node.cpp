#include "quick_node.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>


ZQuickNode::ZQuickNode()
{
    m_name = "nodeName";
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &ZQuickNode::onMockCoreCallback);
    m_timer->start(1000);
}

QString ZQuickNode::getName()
{
    return m_name;
}

void ZQuickNode::setName(QString name)
{
    m_name = name;
    emit name_changed();
}

QQmlListProperty<ZQuickParam> ZQuickNode::params()
{
    return QQmlListProperty<ZQuickParam>(this, this,
        &ZQuickNode::appendParam,
        &ZQuickNode::paramCount,
        &ZQuickNode::param,
        &ZQuickNode::clearParam);
}

void ZQuickNode::appendParam(ZQuickParam* param)
{
    m_params.append(param);
    emit params_changed();
}

int ZQuickNode::paramCount() const
{
    return m_params.count();
}

ZQuickParam* ZQuickNode::param(int index) const
{
    return m_params.at(index);
}

void ZQuickNode::clearParam()
{
    m_params.clear();
    emit params_changed();
}

void ZQuickNode::onMockCoreCallback()
{
    if (false) {
        QQmlEngine* engine = QQmlEngine::contextForObject(this)->engine();
        QQmlComponent comp(engine, QUrl(QStringLiteral("qrc:/qml/ZParam.qml")));
        QObject* myObject = comp.create();
        ZQuickParam* item = qobject_cast<ZQuickParam*>(myObject);
        item->setName("damidami");
        item->setControl(ZQuickParam::CTRL_MULTITEXT);
        if (this == this->parentItem()) {
            int j;
            j = 0;
        }
        appendParam(item);
        //emit newparamCommand("newparam");
    }

    if (false) {
        clearParam();
    }
}

void ZQuickNode::appendParam(QQmlListProperty<ZQuickParam>* list, ZQuickParam* s)
{
    reinterpret_cast<ZQuickNode*>(list->data)->appendParam(s);
}

int ZQuickNode::paramCount(QQmlListProperty<ZQuickParam>* list)
{
    return reinterpret_cast<ZQuickNode*>(list->data)->paramCount();
}

ZQuickParam* ZQuickNode::param(QQmlListProperty<ZQuickParam>* list, int i)
{
    return reinterpret_cast<ZQuickNode*>(list->data)->param(i);
}

void ZQuickNode::clearParam(QQmlListProperty<ZQuickParam>* list)
{
    reinterpret_cast<ZQuickNode*>(list->data)->clearParam();
}
