#ifndef NOTES_NEW_H
#define NOTES_NEW_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class Notes_new;
}

class Notes_new : public QWidget
{
    Q_OBJECT

public:
    explicit Notes_new(QWidget *parent = nullptr);
    ~Notes_new();

public slots:
    void onAddNote(const int &i);

signals:
    void giveNoteBack(const QJsonValue &val, const int &i);

private slots:
    void on_save_clicked();

private:
    Ui::Notes_new *ui;
    int i;
};

#endif // NOTES_NEW_H
