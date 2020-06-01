#include "notes.h"
#include "ui_notes.h"

Notes::Notes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Notes)
{
    ui->setupUi(this);



    connect(ui->save, SIGNAL(clicked), this, SIGNAL(on_saveButton_clicked()));
}

Notes::~Notes()
{
    delete ui;
}

void Notes::onGiveNote(const QJsonValue &val, const int &i)
{
    this->i = i;
    edit = false;
    ui->edit->setDefault(false);

    ui->title->setReadOnly(true);
    ui->note->setReadOnly(true);

    ui->title->setText(val.toObject().value("title").toString());
    ui->note->setText(val.toObject().value("note").toString());
}

void Notes::on_save_clicked()
{
    QJsonObject note;
    note.insert("title", ui->title->text());
    note.insert("note", ui->note->toPlainText());

    emit this->giveNoteBack(QJsonValue(note), i);

    this->close();
}

void Notes::on_edit_clicked()
{
    if (edit == false)
    {
        edit = true;
        ui->edit->setDefault(true);
        ui->title->setReadOnly(false);
        ui->note->setReadOnly(false);

    }
    else
    {
        edit = false;
        ui->edit->setDefault(false);
        ui->title->setReadOnly(true);
        ui->note->setReadOnly(true);
    }
}
