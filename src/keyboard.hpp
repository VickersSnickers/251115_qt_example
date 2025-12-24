#pragma once

#include <cstddef>
#include <unordered_map>

#include <QGridLayout>
#include <QWidget>

#include "keyboard_button.hpp"
#include "keyboard_data.hpp"
#include "key_data.hpp"

namespace biv {
	class KeyBoard : public QWidget {
		Q_OBJECT

		private:
			const int button_width;
			std::unordered_map<int, KeyBoardButton*> buttons;
			
			KeyBoardData* keyboard_data;

			bool is_caps = false;
			bool is_shift_pressed = false;
		
		public:
			KeyBoard(const int width, QWidget* parent = nullptr);
			
			void animate_button(const int code);
			void handle_key_press(const int code);
			
		signals:
			void character_pressed(const QString& character);
			void backspace_pressed();

		private:
			void create_buttons(
				const std::vector<KeyData>& data, 
				QGridLayout* layout, 
				const int line,
				const int start_position
			);
			
			void update_keyboard_layout();

		private slots:
			void on_button_clicked();
			void caps_toggled();
			void shift_toggled(bool checked);
	};
}