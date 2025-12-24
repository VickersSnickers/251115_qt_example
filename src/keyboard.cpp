#include "keyboard.hpp"

using biv::KeyBoard;

KeyBoard::KeyBoard(const int width, QWidget* parent) 
	: button_width(width / 29), QWidget(parent) {

	is_caps = false;
	is_shift_pressed = false;

	keyboard_data = new KeyBoardData();
	
    QGridLayout* keys_layout = new QGridLayout(this);
	keys_layout->setContentsMargins(0, 0, 0, 0);
    keys_layout->setSpacing(5);
	
	// 1-я линия
	create_buttons(keyboard_data->get_line1(), keys_layout, 0, 0);
	
	KeyBoardButton* backspace_btn = new KeyBoardButton("Удалить");
	backspace_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(backspace_btn, 0, 26, 2, 3);
	connect(backspace_btn, &QPushButton::clicked, this, &KeyBoard::backspace_pressed);

	// 2-я линия
	KeyBoardButton* tab_btn = new KeyBoardButton("Tab");
	tab_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(tab_btn, 2, 0, 2, 3);
	connect(tab_btn, &QPushButton::clicked, this, [this](){ emit character_pressed("\t"); });

	create_buttons(keyboard_data->get_line2(), keys_layout, 2, 3);
	
	// 3-я линия
	KeyBoardButton* caps_btn = new KeyBoardButton("Caps");
	caps_btn->setMinimumSize(2 * button_width, button_width);
	caps_btn->setCheckable(true);
	keys_layout->addWidget(caps_btn, 4, 0, 2, 4);
	connect(caps_btn, &QPushButton::clicked, this, &KeyBoard::caps_toggled);
	
	create_buttons(keyboard_data->get_line3(), keys_layout, 4, 4);
	
	KeyBoardButton* enter_btn = new KeyBoardButton("Enter");
	enter_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(enter_btn, 4, 26, 2, 3);
	connect(enter_btn, &QPushButton::clicked, this, [this](){ emit character_pressed("\n"); });
	
	// 4-я линия
	KeyBoardButton* left_shift_btn = new KeyBoardButton("Shift");
	left_shift_btn->setMinimumSize(2 * button_width, button_width);
	left_shift_btn->setCheckable(true);
	keys_layout->addWidget(left_shift_btn, 6, 0, 2, 5);
	connect(left_shift_btn, &QPushButton::clicked, this, &KeyBoard::shift_toggled);
	
	create_buttons(keyboard_data->get_line4(), keys_layout, 6, 5);
	
	KeyBoardButton* right_shift_btn = new KeyBoardButton("Shift");
	right_shift_btn->setMinimumSize(2 * button_width, button_width);
	right_shift_btn->setCheckable(true);
	keys_layout->addWidget(right_shift_btn, 6, 25, 2, 4);
	connect(right_shift_btn, &QPushButton::clicked, this, &KeyBoard::shift_toggled);

	// 5-я линия
	KeyBoardButton* space = new KeyBoardButton();
	space->setMinimumSize(8 * button_width, button_width);
	keys_layout->addWidget(space, 8, 7, 2, 16);
	connect(space, &QPushButton::clicked, this, [this](){ emit character_pressed(" "); });
}

void KeyBoard::animate_button(const int code) {
	if (buttons.count(code)) {
		buttons.at(code)->animateClick();
	}
}

void KeyBoard::handle_key_press(const int code) {
    if (keyboard_data->is_key_allowed(code)) {
        bool to_upper = is_caps ^ is_shift_pressed; 
        for (const auto& key_data : keyboard_data->get_all_keys()) {
            if (key_data.code == code) {
                emit character_pressed(to_upper ? key_data.upper_text : key_data.lower_text);
                break;
            }
        }

        if (is_shift_pressed && !is_caps) {
			QList<KeyBoardButton*> shift_buttons = this->findChildren<KeyBoardButton*>();
			for(auto* btn : shift_buttons) {
				if(btn->text() == "Shift") {
					btn->setChecked(false);
				}
			}
            shift_toggled(false);
        }
    }
}

void KeyBoard::create_buttons(
	const std::vector<KeyData>& data, 
	QGridLayout* layout, 
	const int line,
	const int start_position
) {
	for (int i = 0; i < data.size(); i++) {
        KeyBoardButton* btn = new KeyBoardButton(data[i].lower_text);
		btn->setMinimumSize(button_width, button_width);
		layout->addWidget(btn, line, i * 2 + start_position, 2, 2);
		buttons[data[i].code] = btn;
		connect(btn, &QPushButton::clicked, this, &KeyBoard::on_button_clicked);
	}
}

void KeyBoard::update_keyboard_layout() {
    bool to_upper = is_caps ^ is_shift_pressed;
    for (const auto& key_data : keyboard_data->get_all_keys()) {
        if (buttons.count(key_data.code)) {
            buttons.at(key_data.code)->setText(to_upper ? key_data.upper_text : key_data.lower_text);
        }
    }
}

void KeyBoard::caps_toggled() {
    is_caps = !is_caps;
    update_keyboard_layout();
}

void KeyBoard::shift_toggled(bool checked) {
    is_shift_pressed = checked;
    update_keyboard_layout();
}

void KeyBoard::on_button_clicked() {
	auto* button = qobject_cast<KeyBoardButton*>(sender());
	if (!button) return;

	for(const auto& key_data : keyboard_data->get_all_keys()) {
		if (key_data.lower_text == button->text() || key_data.upper_text == button->text()) {
			handle_key_press(key_data.code);
			break;
		}
	}
}