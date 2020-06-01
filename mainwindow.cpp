#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    this->load_from_file();
    this->on_load();

    contacts = new Contacts;
    contacts_new = new Contacts_new;
    notes = new Notes;
    notes_new = new Notes_new;

    // сигналы для просмотра контактов
    connect(ui->contacts, SIGNAL(doubleClicked), this, SIGNAL(on_listWidget_doubleClicked(const QModelIndex&)));
    connect(this, SIGNAL(giveContact(const QJsonValue&, const int&)), contacts, SLOT(onGiveContact(const QJsonValue&, const int&)));
    connect(contacts, SIGNAL(giveContactBack(const QJsonValue&, const int&)), this, SLOT(onGiveContactBack(const QJsonValue&, const int&)));

    // сигналы для добавления контакта
    connect(this, SIGNAL(addContact(const int&)), contacts_new, SLOT(onAddContact(const int&)));
    connect(contacts_new, SIGNAL(giveContactBack(const QJsonValue&, const int&)), this, SLOT(onGiveContactBack(const QJsonValue&, const int&)));

    // сигналы для просмотра заметок
    connect(ui->notes, SIGNAL(doubleClicked), this, SIGNAL(on_notes_doubleClicked(const QModelIndex&)));
    connect(this, SIGNAL(giveNote(const QJsonValue&, const int&)), notes, SLOT(onGiveNote(const QJsonValue&, const int&)));
    connect(notes, SIGNAL(giveNoteBack(const QJsonValue&, const int&)), this, SLOT(onGiveNoteBack(const QJsonValue&, const int&)));

    // сигналы для добавления заметки
    connect(this, SIGNAL(addNote(const int&)), notes_new, SLOT(onAddNote(const int&)));
    connect(notes_new, SIGNAL(giveNoteBack(const QJsonValue&, const int&)), this, SLOT(onGiveNoteBack(const QJsonValue&, const int&)));
}

MainWindow::~MainWindow()
{
    load_to_file();
    delete ui;
}

void MainWindow::load_from_file()
{
//C:\Users\mboxc\Downloads\Notebook\Notebook
    //file.setFileName("C:\\Qt\\Notebook\\Notebook.json");
    file.setFileName("C:\\Users\\mboxc\\Downloads\\Notebook\\Notebook\\Notebook.json");
    if (file.open(QIODevice::ReadOnly|QFile::Text))
    {
        QJsonDocument doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &doc_error);
        doc_contacts_array = QJsonValue(doc.object().value("contacts")).toArray();
        doc_notes_array = QJsonValue(doc.object().value("notes")).toArray();
    }
    file.close();
}

void MainWindow::load_to_file()
{
    if (file.open(QIODevice::WriteOnly))
    {

        QJsonDocument doc_contacts;
        doc_contacts.setArray(doc_contacts_array);
        QJsonDocument doc_notes;
        doc_notes.setArray(doc_notes_array);
        file.write("{\"contacts\":" + doc_contacts.toJson() + ", \"notes\":" + doc_notes.toJson() + "}");
    }
    file.close();
}

void MainWindow::on_load()
{
    ui->contacts->clear();
    QStringList list;
    for (int i = 0; i < doc_contacts_array.count(); i++)
    {
         list.append(doc_contacts_array[i].toObject().value("name").toString() + " " + doc_contacts_array[i].toObject().value("surname").toString());
    }
    ui->contacts->addItems(list);

    ui->notes->clear();
    list.clear();
    for (int i = 0; i < doc_notes_array.count(); i++)
    {
         list.append(doc_notes_array[i].toObject().value("title").toString());
    }
    ui->notes->addItems(list);
}

// контакты

void MainWindow::on_contacts_doubleClicked(const QModelIndex &index)
{
    emit this->giveContact(QJsonValue(doc_contacts_array.at(index.row())), index.row());
    contacts->show();
}

void MainWindow::on_add_contact_clicked()
{
    emit this->addContact(doc_contacts_array.size());
    contacts_new->show();
}

void MainWindow::on_delete_contact_clicked()
{
    int j = ui->contacts->currentRow();
    doc_contacts_array.removeAt(j);
    on_load();
}

void MainWindow::onGiveContactBack(const QJsonValue &val, const int &i)
{
   doc_contacts_array.removeAt(i);
   doc_contacts_array.insert(i, val);
   on_load();
}

// заметки

void MainWindow::on_notes_doubleClicked(const QModelIndex &index)
{
    emit this->giveNote(QJsonValue(doc_notes_array.at(index.row())), index.row());
    notes->show();
}

void MainWindow::on_add_note_clicked()
{
    emit this->addNote(doc_notes_array.size());
    notes_new->show();
}

void MainWindow::on_delete_note_clicked()
{
    int j = ui->notes->currentRow();
    doc_notes_array.removeAt(j);
    on_load();
}

void MainWindow::onGiveNoteBack(const QJsonValue &val, const int &i)
{
    doc_notes_array.removeAt(i);
    doc_notes_array.insert(i, val);
    on_load();
}
