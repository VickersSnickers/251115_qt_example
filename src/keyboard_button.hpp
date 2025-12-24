#pragma once

#include <QPushButton>
#include <QObject> 

namespace biv {
    class KeyBoardButton : public QPushButton {
        Q_OBJECT 

    public:
        KeyBoardButton(const QString& text = "", QWidget* parent = nullptr);
    };
}