#include "keyboard_window.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QApplication>
using biv::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
	const int keyboard_width = 1160;
	resize(keyboard_width, 710);
    setWindowTitle("Клавиатура");
	
	QString imagePath = QApplication::applicationDirPath() + "/img/grustnii-smail.png";
	QPixmap pixmap(imagePath);
	QLabel* image = new QLabel(this);
	image->setFixedSize(200, 200);
	image->setPixmap(pixmap);
	image->setScaledContents(true);
	
	QHBoxLayout* smail_layout = new QHBoxLayout();
	smail_layout->addWidget(image);

    display = new QLineEdit();
	display->setMinimumHeight(80);
	display->setFont(QFont("Roboto", 40));
    display->setText("Начните ввод...");
    display->setFocus(); 

	keyboard = new KeyBoard(keyboard_width);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);

	connect(keyboard, &KeyBoard::character_pressed, this, &KeyBoardWindow::on_character_pressed);
	connect(keyboard, &KeyBoard::backspace_pressed, this, &KeyBoardWindow::on_backspace_pressed);
}

void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
	int qt_key = event->key();

	switch (qt_key) {
		case Qt::Key_Shift:
		case Qt::Key_CapsLock:
		case Qt::Key_Control:
		case Qt::Key_Alt:
		case Qt::Key_AltGr:
		case Qt::Key_Meta: 
			return;

		case Qt::Key_Backspace:
			on_backspace_pressed();
			return;
	}

	int native_key_code = event->nativeVirtualKey();
	keyboard->handle_key_press(native_key_code);
	keyboard->animate_button(native_key_code);
}

void KeyBoardWindow::on_character_pressed(const QString& character) {
	if (display->text() == "Начните ввод...") {
		display->clear();
		display->setFocus();
	}
	display->setText(display->text() + character);
	display->setFocus();
}

void KeyBoardWindow::on_backspace_pressed() {
	if (display->text() == "Начните ввод...") {
		display->clear();
		display->setFocus();
	} else {
		display->backspace();
		display->setFocus();
	}
}