#include "contacts.h"
#include "ui_contacts.h"

Contacts::Contacts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contacts)
{
    ui->setupUi(this);



    connect(ui->save, SIGNAL(clicked), this, SIGNAL(on_save_clicked()));
}

Contacts::~Contacts()
{
    delete ui;
}

void Contacts::onGiveContact(const QJsonValue &val, const int &i)
{
    this->i = i;
    edit = false;
    ui->edit->setDefault(false);

    ui->edit->setChecked(false);
    ui->add->setEnabled(false);
    ui->del->setEnabled(false);
    ui->name->setReadOnly(true);
    ui->surname->setReadOnly(true);

    ui->name->setText(val.toObject().value("name").toString());
    ui->surname->setText(val.toObject().value("surname").toString());

    ui->phones->clear();
    ui->phones->setRowCount(0);

    QStringList list;
    list.append("type"); list.append("number");
    ui->phones->setColumnCount(2);
    ui->phones->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->phones->setSelectionMode(QAbstractItemView::NoSelection);
    ui->phones->setHorizontalHeaderLabels(list);
    ui->phones->horizontalHeader()->setStretchLastSection(true);

    QJsonArray phones = QJsonValue(val.toObject().value("phones")).toArray();
    for(int i = 0; i < phones.count(); i++)
    {
        ui->phones->insertRow(i);
        ui->phones->setItem(i, 0, new QTableWidgetItem(phones[i].toObject().value("type").toString()));
        ui->phones->setItem(i, 1, new QTableWidgetItem(phones[i].toObject().value("number").toString()));
    }
}

void Contacts::on_save_clicked()
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

void Contacts::on_add_clicked()
{
    ui->phones->insertRow(ui->phones->rowCount());
}

void Contacts::on_del_clicked()
{
    ui->phones->removeRow(ui->phones->currentRow());
}

void Contacts::on_edit_clicked()
{
    if (edit == false)
    {
        edit = true;
        ui->edit->setDefault(true);
        ui->phones->setEditTriggers(QAbstractItemView::DoubleClicked);
        ui->phones->setSelectionMode(QAbstractItemView::ExtendedSelection);
        ui->name->setReadOnly(false);
        ui->surname->setReadOnly(false);
        ui->add->setEnabled(true);
        ui->del->setEnabled(true);
    }
    else
    {
        edit = false;
        ui->edit->setDefault(false);
        ui->phones->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->phones->setSelectionMode(QAbstractItemView::NoSelection);
        ui->name->setReadOnly(true);
        ui->surname->setReadOnly(true);
        ui->add->setEnabled(false);
        ui->del->setEnabled(false);
        ui->phones->clearSelection();
    }
}
