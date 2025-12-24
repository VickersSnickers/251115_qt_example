#ifndef LOGINFORM_HPP
#define LOGINFORM_HPP

#include <QDialog>

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);

signals:
    void loginAccepted();
    void loginRejected();

private slots:
    void onStartClicked();
    void onCancelClicked();
};

#endif 