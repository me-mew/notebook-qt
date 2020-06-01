#include "contacts_new.h"
#include "ui_contacts_new.h"

Contacts_new::Contacts_new(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contacts_new)
{
    ui->setupUi(this);

    /*QPixmap save_png("C:\\Users\\defaultuser0\\Qt projects\\Notebook\\save.png");
    ui->save->setIcon(save_png);*/
}

Contacts_new::~Contacts_new()
{
    delete ui;
}

void Contacts_new::onAddContact(const int &i)
{
    this->i = i;

    QStringList list;
    list.append("type"); list.append("number");
    ui->phones->setColumnCount(2);
    ui->phones->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->phones->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->phones->setHorizontalHeaderLabels(list);
    ui->phones->horizontalHeader()->setStretchLastSection(true);
}

void Contacts_new::on_add_clicked()
{
    ui->phones->insertRow(ui->phones->rowCount());
}

void Contacts_new::on_del_clicked()
{
    ui->phones->removeRow(ui->phones->currentRow());
}

void Contacts_new::on_save_clicked()
{
    QJsonObject contact;
    contact.insert("name", ui->name->text());
    contact.insert("surname", ui->surname->text());
    QJsonArray phones;
    int length = 0;
    for (int j = 0; j < ui->phones->rowCount(); j++)
    {
        if (ui->phones->item(j, 1) != 0)
        {
            QJsonObject phone;
            phone.insert("type", ui->phones->takeItem(j, 0)->text());
            phone.insert("number", ui->phones->takeItem(j, 1)->text());
            phones.insert(length, phone);
            length++;
        }
    }
    contact.insert("phones", phones);

    emit this->giveContactBack(QJsonValue(contact), i);

    this->close();
}
