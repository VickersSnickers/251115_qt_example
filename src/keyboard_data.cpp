#include "keyboard_data.hpp"
#include <algorithm>

using biv::KeyData;
using biv::KeyBoardData;

const std::vector<KeyData> KeyBoardData::KEYS = {
	{192, "ё", "Ё"}, {49, "1", "!"}, {50, "2", "\""}, {51, "3", "№"}, {52, "4", ";"}, {53, "5", "%"}, {54, "6", ":"}, 
		{55, "7", "?"}, {56, "8", "*"}, {57, "9", "("}, {48, "0", ")"}, {189, "-", "_"}, {187, "=", "+"}, 
	{81, "й", "Й"}, {87, "ц", "Ц"}, {69, "у", "У"}, {82, "к", "К"}, {84, "е", "Е"}, {89, "н", "Н"}, {85, "г", "Г"}, 
		{73, "ш", "Ш"}, {79, "щ", "Щ"}, {80, "з", "З"}, {219, "х", "Х"}, {221, "ъ", "Ъ"}, {220, "\\", "/"}, 
	{65, "ф", "Ф"}, {83, "ы", "Ы"}, {68, "в", "В"}, {70, "а", "А"}, {71, "п", "П"}, {72, "р", "Р"}, {74, "о", "О"}, 
		{75, "л", "Л"}, {76, "д", "Д"}, {186, "ж", "Ж"}, {222, "э", "Э"}, 
	{90, "я", "Я"}, {88, "ч", "Ч"}, {67, "с", "С"}, {86, "м", "М"}, {66, "и", "И"}, {78, "т", "Т"}, {77, "ь", "Ь"}, 
		{188, "б", "Б"}, {190, "ю", "Ю"}, {191, ".", ","}
};

std::vector<KeyData> KeyBoardData::get_line1() const {
	return {KEYS.begin(), KEYS.begin() + 13};
}

std::vector<KeyData> KeyBoardData::get_line2() const {
	return {KEYS.begin() + 13, KEYS.begin() + 26};
}

std::vector<KeyData> KeyBoardData::get_line3() const {
	return {KEYS.begin() + 26, KEYS.begin() + 37};
}

std::vector<KeyData> KeyBoardData::get_line4() const {
	return {KEYS.begin() + 37, KEYS.begin() + 47};
}

const std::vector<KeyData>& KeyBoardData::get_all_keys() const {
	return KEYS;
}

bool KeyBoardData::is_key_allowed(const int code) const noexcept {
	return std::any_of(KEYS.begin(), KEYS.end(), [code](const KeyData& key_data){
		return key_data.code == code;
	});
}