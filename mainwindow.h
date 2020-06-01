#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "contacts.h"
#include "contacts_new.h"
#include "notes.h"
#include "notes_new.h"

#include <QTabWidget>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QFileDialog>

#include <QStandardItem>
#include <QMessageBox>

#include "QStandardItemModel"
#include "QStandardItem"

namespace Ui {
class MainWindow;
}

class Contacts;
class Contacts_new;
class Notes;
class Notes_new;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QJsonArray doc_contacts_array;
    QJsonArray doc_notes_array;
    QJsonParseError doc_error;

    QString global_path;
    QFile file;

private slots:
    void load_from_file();

    void load_to_file();

    void on_load();

    void on_contacts_doubleClicked(const QModelIndex &index);

    void on_add_contact_clicked();

    void on_delete_contact_clicked();

    void onGiveContactBack(const QJsonValue &val, const int &i);

    void on_notes_doubleClicked(const QModelIndex &index);

    void on_add_note_clicked();

    void on_delete_note_clicked();

    void onGiveNoteBack(const QJsonValue &val, const int &i);

signals:
    void giveContact(const QJsonValue &val, const int &i);

    void addContact(const int &i);

    void giveNote(const QJsonValue &val, const int &i);

    void addNote(const int &i);

private:
    Ui::MainWindow *ui;
    Contacts *contacts;
    Contacts_new *contacts_new;
    Notes *notes;
    Notes_new *notes_new;
    int i;
};

#endif // MAINWINDOW_H
