#ifndef DRIVERMODEL_H
#define DRIVERMODEL_H

#include <QObject>
#include <QAbstractListModel>

class DriverItem
{
public:
    DriverItem(const QString &name, const QString &icon,const QString& desc);

    DriverItem(const QStringList &lst);

    QString name() const;
    QString icon() const;
    QString desc()const;

    void setName(const QString& name);
    void setIcon(const QString& icon);
    void setDesc(const QString& desc);

private:
    QString m_name;
    QString m_icon;
    QString m_desc;
};


class DriverModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DriverRoles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        DescRole
    };
    explicit DriverModel(QObject *parent = 0);

   Q_INVOKABLE  void addDriverItem(const DriverItem &item);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
public slots:
    void addSomeItem(QStringList lst);
    bool updateSomeItem(const QStringList& name);
    bool removeSomeItem(const QString& name);

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<DriverItem> m_driverItems;
public slots:
};

#endif // DRIVERMODEL_H
