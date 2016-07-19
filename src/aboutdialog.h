/*
*This file is part of Ultimate-Media-Downloader.
*
*Ultimate-Media-Downloader is not a free software: you can't redistribute it nor modify
*it without the author <keshavnrj@gmail.com> Keshav Bhatt permission.
*
*Ultimate-Media-Downloader is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QNetworkReply>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private:
    Ui::AboutDialog *ui;

private slots:
    void slot_netwManagerFinished(QNetworkReply *reply);
    void    netwManagerFinished(QNetworkReply *reply);
    void closeEvent(QCloseEvent *);
    void on_donate_clicked();
    void on_twitter_clicked();
    void on_facebook_clicked();
    void on_gmail_clicked();
};

#endif // ABOUTDIALOG_H
