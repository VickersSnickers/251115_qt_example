#include <QApplication>
#include <QMessageBox>

#include "LoginForm.hpp"
#include "keyboard_window.hpp"

 int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    biv::KeyBoardWindow* keyboard_form = new biv::KeyBoardWindow();

    LoginForm* login_form = new LoginForm();
    login_form->show();

    QObject::connect(login_form, &LoginForm::loginAccepted, [=] {
        login_form->close();
        keyboard_form->show();
    });


    return app.exec();
}


