#include "ParamsModel.h"


ParamsModel::ParamsModel(NODE_DESCRIPTOR desc, QObject* parent)
    : QAbstractListModel(parent)
{

    for (SOCKET_DESCRIPTOR socket_desc : desc.inputs)
    {
        m_items.append({ true, socket_desc.name, socket_desc.type, socket_desc.control });
    }

    for (SOCKET_DESCRIPTOR socket_desc : desc.outputs)
    {
        m_items.append({ false, socket_desc.name, socket_desc.type });
    }
}

QVariant ParamsModel::data(const QModelIndex& index, int role) const
{
    const ParamItem& param = m_items[index.row()];

    switch (role)
    {
    case ROLE_OBJNAME:          return param.name;
    case ROLE_PARAM_TYPE:       return param.type;
    case ROLE_PARAM_CONTROL:    return param.control;
    case ROLE_ISINPUT:          return param.bInput;
    case ROLE_NODEIDX:          return m_nodeIdx;
    }
    return QVariant();
}

bool ParamsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return QAbstractListModel::setData(index, value, role);
}

QHash<int, QByteArray> ParamsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ROLE_OBJNAME] = "name";
    roles[ROLE_PARAM_TYPE] = "type";
    roles[ROLE_PARAM_CONTROL] = "control";
    roles[ROLE_ISINPUT] = "input";
    return roles;
}

int ParamsModel::rowCount(const QModelIndex& parent) const
{
    return m_items.count();
}

void ParamsModel::setNodeIdx(const QModelIndex& nodeIdx)
{
    m_nodeIdx = nodeIdx;
}

QModelIndex ParamsModel::paramIdx(const QString& name, bool bInput) const
{
    for (int r = 0; r < rowCount(); r++)
    {
        QModelIndex idx = index(r, 0);
        if (name == data(idx, ROLE_OBJNAME).toString() && bInput == data(idx, ROLE_ISINPUT).toBool())
            return idx;
    }
    return QModelIndex();
}

void ParamsModel::addLink(const QModelIndex& paramIdx, const QPersistentModelIndex& linkIdx)
{
    m_items[paramIdx.row()].links.append(linkIdx);
}
