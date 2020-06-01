#ifndef CONTACTS_NEW_H
#define CONTACTS_NEW_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class Contacts_new;
}

class Contacts_new : public QWidget
{
    Q_OBJECT

public:
    explicit Contacts_new(QWidget *parent = nullptr);
    ~Contacts_new();

public slots:
    void onAddContact(const int &i);

signals:
    void giveContactBack(const QJsonValue &val, const int &i);

private slots:
    void on_add_clicked();

    void on_del_clicked();

    void on_save_clicked();

private:
    Ui::Contacts_new *ui;
    int i;
};

#endif // CONTACTS_NEW_H
