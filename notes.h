#ifndef NOTES_H
#define NOTES_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class Notes;
}

class Notes : public QWidget
{
    Q_OBJECT

public:
    explicit Notes(QWidget *parent = nullptr);
    ~Notes();

public slots:
    void onGiveNote(const QJsonValue &val, const int &i);

signals:
    void giveNoteBack(const QJsonValue &val, const int &i);

private slots:
    void on_save_clicked();

    void on_edit_clicked();

private:
    Ui::Notes *ui;
    int i;
    bool edit;
};

#endif // NOTES_H
