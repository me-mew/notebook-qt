#ifndef CONTACTS_H
#define CONTACTS_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class Contacts;
}

class MainWindow;

class Contacts : public QWidget
{
    Q_OBJECT

public:
    explicit Contacts(QWidget *parent = nullptr);
    ~Contacts();

public slots:
    void onGiveContact(const QJsonValue &val, const int &i);

signals:
    void giveContactBack(const QJsonValue &val, const int &i);

private slots:
    void on_save_clicked();

    void on_add_clicked();

    void on_del_clicked();

    void on_edit_clicked();

private:
    Ui::Contacts *ui;
    int i;
    bool edit;
};

#endif // CONTACTS_H
