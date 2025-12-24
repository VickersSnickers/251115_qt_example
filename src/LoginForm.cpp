#include "LoginForm.hpp"

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QMessageBox>

LoginForm::LoginForm(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Окно входа.");
    setFixedSize(300, 200);

    QLabel *welcomeLabel = new QLabel("Добро пожаловать!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    
    QFont font = welcomeLabel->font();
    font.setPointSize(14);
    welcomeLabel->setFont(font);

    QPushButton *startButton = new QPushButton("Начать", this);
    QPushButton *cancelButton = new QPushButton("Отмена", this);

    startButton->setMinimumHeight(30);
    cancelButton->setMinimumHeight(30);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(cancelButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(welcomeLabel);
    mainLayout->addStretch(); 
    mainLayout->addLayout(buttonLayout);

    connect(startButton, &QPushButton::clicked, this, &LoginForm::onStartClicked);
    connect(cancelButton, &QPushButton::clicked, this, &LoginForm::onCancelClicked);
    
    startButton->setDefault(true);
    
    startButton->setShortcut(Qt::Key_Return);
    cancelButton->setShortcut(Qt::Key_Escape);
}

void LoginForm::onStartClicked()
{
    emit loginAccepted();
}

void LoginForm::onCancelClicked()
{
    emit loginRejected();
}