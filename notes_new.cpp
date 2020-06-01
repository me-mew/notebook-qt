#include "notes_new.h"
#include "ui_notes_new.h"

Notes_new::Notes_new(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Notes_new)
{
    ui->setupUi(this);

}

Notes_new::~Notes_new()
{
    delete ui;
}

void Notes_new::onAddNote(const int &i)
{
    this->i = i;
}

void Notes_new::on_save_clicked()
{
    QJsonObject note;
    note.insert("title", ui->title->text());
    note.insert("note", ui->note->toPlainText());

    emit this->giveNoteBack(QJsonValue(note), i);

    this->close();
}
