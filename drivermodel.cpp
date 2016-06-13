#include "drivermodel.h"

DriverModel::DriverModel(QObject *parent) : QAbstractListModel(parent)
{

}

void DriverModel::addDriverItem(const DriverItem &driver)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_driverItems << driver;
    endInsertRows();
}

int DriverModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_driverItems.count();
}

QVariant DriverModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_driverItems.count())
        return QVariant();

    const DriverItem &driver = m_driverItems[index.row()];
    if (role == NameRole)
        return driver.name();
    else if (role == IconRole)
        return driver.icon();
    else if (role == DescRole )
        return driver.desc();
    return QVariant();
}

///
/// \brief DriverModel::addSomeItem
/// \param lst
///  新增一个数据
///
void DriverModel::addSomeItem(QStringList lst)
{
    if(lst.isEmpty())return;
    //以下代码可以刷新内容 但是无法局部刷新
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_driverItems.append(DriverItem(lst));
    endInsertRows();

    //以下代码在QML模式下不能刷新数据 可能是Qt的bug
    //QModelIndex t1 = index(rowCount(),rowCount());
    //emit dataChanged(t1, t1); // view good 最关键的刷新数据，不会取消所选项
    //emit dataChanged(this->index(m_driverItems.size()),this->index(m_driverItems.size()));
}
///
/// \brief DriverModel::updateSomeItem
/// \param name
/// 更新某一条记录 以name为key
///
bool DriverModel::updateSomeItem(const QStringList &namelst)
{
    bool update = false;
    foreach (DriverItem item, m_driverItems) {
        if(item.name() == namelst.at(0)){
            beginInsertRows(QModelIndex(), rowCount(), rowCount());
            item.setIcon(namelst.at(1));
            item.setDesc(namelst.at(2));
            endInsertRows();
            update = true;
            break;
        }
    }
    return update;
}

///
/// \brief DriverModel::removeSomeItem
/// \param name
/// 删除某个key记录
///
bool DriverModel::removeSomeItem(const QString &name)
{
    bool update = false;
    for (int i=0;i< m_driverItems.size();i++) {
        if(m_driverItems.at(i).name() == name){
            beginRemoveRows(QModelIndex(), i,i);
            m_driverItems.removeAt(i);
            endRemoveRows();
            update = true;
            break;
        }
    }
    return update;
}

///
/// \brief DriverModel::roleNames
/// \return
/// 为Model中的item分配角色
/// 便于在QML中使用
///
QHash<int, QByteArray> DriverModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "dName";
    roles[IconRole] = "dIcon";
    roles[DescRole] = "dDesc";
    return roles;
}


///
/// \brief DriverItem::DriverItem
/// \param name
/// \param icon
/// \param desc
/// 以下为每个item的数据的实现
///
DriverItem::DriverItem(const QString &name, const QString &icon, const QString &desc)
{
    m_name = name;
    m_icon = icon;
    m_desc = desc;
}

DriverItem::DriverItem(const QStringList &lst)
{
    if(lst.isEmpty() || lst.count()<2)return;
    m_name = lst.at(0);
    m_icon = lst.at(1);
    m_desc = lst.at(2);
}

QString DriverItem::name() const
{
    return m_name;
}

QString DriverItem::icon() const
{
    return m_icon;
}

QString DriverItem::desc() const
{
    return m_desc;
}

void DriverItem::setName(const QString &name)
{
    m_name = name;
}

void DriverItem::setIcon(const QString &icon)
{
    m_icon = icon;
}

void DriverItem::setDesc(const QString &desc)
{
    m_desc = desc;
}
