#include "GraphsTreeModel.h"
#include "../common.h"
#include "Descriptors.h"


GraphsTreeModel::GraphsTreeModel(GraphModel* mainModel, QObject* parent)
    : QAbstractItemModel(parent)
    , m_main(mainModel)
{
}

GraphsTreeModel::~GraphsTreeModel()
{
}

QModelIndex GraphsTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (row < 0 || row >= rowCount(parent))
        return QModelIndex();

    if (parent.isValid()) {
        GraphModel* pSubgraph = parent.data(ROLE_SUBGRAPH).value<GraphModel*>();
        Q_ASSERT(pSubgraph);
        return createIndex(row, column, pSubgraph); //index的pointer项指的是拥有此item的GraphModel，类似于QStandItem的parent指针
    }
    else {
        return createIndex(row, column, nullptr);
    }
}

QModelIndex GraphsTreeModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();

    if (child.internalId() == 0) {
        return QModelIndex();
    }

    QModelIndex innerChild = innerIndex(child);
    auto pModel = innerChild.model();
    if (auto pItem = qobject_cast<NodeItem*>(pModel->parent()))
    {
        if (auto parentModel = qobject_cast<GraphModel*>(pItem->parent()))
        {
            int row = parentModel->indexFromId(pItem->ident);
            return createIndex(row, 0, parentModel);
        }
    }
    return createIndex(0, 0);   //main item
}

int GraphsTreeModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        //main item
        return 1;
    }

    GraphModel* pSubgraph  = parent.data(ROLE_SUBGRAPH).value<GraphModel*>();
    return pSubgraph ? pSubgraph->rowCount() : 0;
}

int GraphsTreeModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

bool GraphsTreeModel::hasChildren(const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return true;        //the only child is main item.
    }
    else {
        GraphModel* pSubgraph = parent.data(ROLE_SUBGRAPH).value<GraphModel*>();
        return pSubgraph ? (pSubgraph->rowCount() > 0) : false;
    }
}

QModelIndex GraphsTreeModel::innerIndex(const QModelIndex& treeIdx) const
{
    if (!treeIdx.isValid())
        return QModelIndex();

    //tree项的行号和图模型的行号是一致的。
    GraphModel* ownerModel = static_cast<GraphModel*>(treeIdx.internalPointer());
    Q_ASSERT(ownerModel);
    return ownerModel->index(treeIdx.row(), 0);
}

QVariant GraphsTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    if (index.internalId() == 0) {
        //main item
        if (Qt::DisplayRole == role || ROLE_OBJNAME == role) {
            return "main";
        }
        else if (ROLE_SUBGRAPH == role) {   //相当于子图节点那样，main可以看作最根部的子图节点
            return QVariant::fromValue(m_main);
        }
        return QVariant();
    }
    QModelIndex innerIdx = innerIndex(index);
    return innerIdx.data(role);
}

bool GraphsTreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    QModelIndex innerIdx = innerIndex(index);
    QAbstractItemModel* pModel = const_cast<QAbstractItemModel*>(innerIdx.model());
    return pModel ? pModel->setData(innerIdx, value, role) : false;
}

QModelIndexList GraphsTreeModel::match(const QModelIndex& start, int role,
    const QVariant& value, int hits,
    Qt::MatchFlags flags) const
{
    return QModelIndexList();
}

QHash<int, QByteArray> GraphsTreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ROLE_OBJNAME] = "name";
    roles[ROLE_OBJID] = "ident";
    roles[ROLE_PARAMS] = "params";
    roles[ROLE_LINKS] = "linkModel";
    roles[ROLE_OBJPOS] = "pos";
    roles[ROLE_SUBGRAPH] = "subgraph";
    return roles;
}

int GraphsTreeModel::depth(const QModelIndex& index) const
{
    int count = 0;
    auto anchestor = index;
    if (!index.isValid()) {
        return 0;
    }
    while (anchestor.parent().isValid()) {
        anchestor = anchestor.parent();
        ++count;
    }
    return count;
}

GraphModel* GraphsTreeModel::graph(const QModelIndex& index) const
{
    if (index.isValid() && index.internalId() == 0)
        return nullptr;

    GraphModel* ownerModel = static_cast<GraphModel*>(index.internalPointer());
    Q_ASSERT(ownerModel);
    return ownerModel;
}

QString GraphsTreeModel::ident(const QModelIndex& index) const
{
    return index.data(ROLE_OBJID).toString();
}

//! Clear the model.
void GraphsTreeModel::clear()
{
    emit layoutAboutToBeChanged();
    beginResetModel();
    delete m_main;
    m_main = new GraphModel("main", this);
    endResetModel();
    emit layoutChanged();
}

/*!
*  Return the root item to the QML Side.
*  This method is not meant to be used in client code.
*/
QModelIndex GraphsTreeModel::rootIndex()
{
    return {};
}
