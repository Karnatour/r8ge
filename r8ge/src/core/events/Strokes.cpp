#include "Strokes.h"

namespace r8ge {
    std::string to_string(const Key& code) {
        switch (code) {
            case Key::UNKNOWN: return "unknown";
            case Key::MBUTTON_1: return "mouse 1";
            case Key::MBUTTON_2: return "mouse 2";
            case Key::MBUTTON_3: return "mouse 3";
            case Key::MBUTTON_4: return "mouse 4";
            case Key::MBUTTON_5: return "mouse 5";
            case Key::MBUTTON_6: return "mouse 6";
            case Key::MBUTTON_7: return "mouse 7";
            case Key::MBUTTON_8: return "mouse 8";
            case Key::MBUTTON_LEFT: return "mouse left";
            case Key::MBUTTON_RIGHT: return "mouse right";
            case Key::MBUTTON_MIDDLE: return "mouse middle";
            case Key::SPACE: return "space";
            case Key::APOSTROPHE: return "\'";
            case Key::COMMA: return ",";
            case Key::MINUS: return "-";
            case Key::PERIOD: return ".";
            case Key::SLASH: return "/";
            case Key::N0: return "0";
            case Key::N1: return "1";
            case Key::N2: return "2";
            case Key::N3: return "3";
            case Key::N4: return "4";
            case Key::N5: return "5";
            case Key::N6: return "6";
            case Key::N7: return "7";
            case Key::N8: return "8";
            case Key::N9: return "9";
            case Key::SEMICOLON: return ";";
            case Key::EQUAL: return "=";
            case Key::A: return "A";
            case Key::B: return "B";
            case Key::C: return "C";
            case Key::D: return "D";
            case Key::E: return "E";
            case Key::F: return "F";
            case Key::G: return "G";
            case Key::H: return "H";
            case Key::I: return "I";
            case Key::J: return "J";
            case Key::K: return "K";
            case Key::L: return "L";
            case Key::M: return "M";
            case Key::N: return "N";
            case Key::O: return "O";
            case Key::P: return "P";
            case Key::Q: return "Q";
            case Key::R: return "R";
            case Key::S: return "S";
            case Key::T: return "T";
            case Key::U: return "U";
            case Key::V: return "V";
            case Key::W: return "W";
            case Key::X: return "X";
            case Key::Y: return "Y";
            case Key::Z: return "Z";
            case Key::LEFT_BRACKET: return "[";
            case Key::BACKSLASH: return "\\";
            case Key::RIGHT_BRACKET: return "]";
            case Key::GRAVE_ACCENT: return "`";
            case Key::ESCAPE: return "ESC";
            case Key::ENTER: return "enter";
            case Key::TAB: return "tab";
            case Key::BACKSPACE: return "backspace";
            case Key::INSERT: return "insert";
            case Key::DELETE: return "delete";
            case Key::RIGHT: return "right";
            case Key::LEFT: return "left";
            case Key::DOWN: return "down";
            case Key::UP: return "up";
            case Key::PAGE_UP: return "page up";
            case Key::PAGE_DOWN: return "page down";
            case Key::HOME: return "home";
            case Key::END: return "end";
            case Key::CAPS_LOCK: return "caps lock";
            case Key::SCROLL_LOCK: return "scroll lock";
            case Key::NUM_LOCK: return "num lock";
            case Key::PRINT_SCREEN: return "print screen";
            case Key::PAUSE: return "pause";
            case Key::F1: return "F1";
            case Key::F2: return "F2";
            case Key::F3: return "F3";
            case Key::F4: return "F4";
            case Key::F5: return "F5";
            case Key::F6: return "F6";
            case Key::F7: return "F7";
            case Key::F8: return "F8";
            case Key::F9: return "F9";
            case Key::F10: return "F10";
            case Key::F11: return "F11";
            case Key::F12: return "F12";
            case Key::F13: return "F13";
            case Key::F14: return "F14";
            case Key::F15: return "F15";
            case Key::F16: return "F16";
            case Key::F17: return "F17";
            case Key::F18: return "F18";
            case Key::F19: return "F19";
            case Key::F20: return "F20";
            case Key::F21: return "F21";
            case Key::F22: return "F22";
            case Key::F23: return "F23";
            case Key::F24: return "F24";
            case Key::F25: return "F25";
            case Key::KP_0: return "KP 0";
            case Key::KP_1: return "KP 1";
            case Key::KP_2: return "KP 2";
            case Key::KP_3: return "KP 3";
            case Key::KP_4: return "KP 4";
            case Key::KP_5: return "KP 5";
            case Key::KP_6: return "KP 6";
            case Key::KP_7: return "KP 7";
            case Key::KP_8: return "KP 8";
            case Key::KP_9: return "KP 9";
            case Key::KP_DECIMAL: return "KP decimal";
            case Key::KP_DIVIDE: return "KP divide";
            case Key::KP_MULTIPLY: return "KP multiply";
            case Key::KP_SUBTRACT: return "KP subtract";
            case Key::KP_ADD: return "KP add";
            case Key::KP_ENTER: return "KP enter";
            case Key::KP_EQUAL: return "KP equal";
            case Key::LEFT_SHIFT: return "left shift";
            case Key::LEFT_CONTROL: return "left control";
            case Key::LEFT_ALT: return "left alt";
            case Key::LEFT_SUPER: return "left super";
            case Key::RIGHT_SHIFT: return "right shift";
            case Key::RIGHT_CONTROL: return "right control";
            case Key::RIGHT_ALT: return "right alt";
            case Key::RIGHT_SUPER: return "right super";
            case Key::MENU: return "menu";
        }
        return "unknown";
    }

    std::string to_string(Modifier action) {
        std::string ret;

        if(action==Modifier::NONE) ret+="none";
        if(action&Modifier::SHIFT) ret+="shift";
        if(action&Modifier::CTRL)  ret+="control";
        if(action&Modifier::ALT)   ret+="alt";
        if(action&Modifier::SUPER) ret+="super";

        return ret;
    }

    Modifier operator|(Modifier lhs, Modifier rhs) {
        return static_cast<Modifier>(static_cast<int>(lhs) | static_cast<int>(rhs));
    }

    bool operator&(Modifier lhs, Modifier rhs) {
        return static_cast<bool>(static_cast<int>(lhs) & static_cast<int>(rhs));
    }
}