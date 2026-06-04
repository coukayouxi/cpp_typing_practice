#include "TUI.h"

// TUI namespace implementations
TUI::Color::Color(ColorCode c) : code(c) {}

TUI::GotoXY::GotoXY(int px, int py) : x(px), y(py) {}

// StdIO class implementations
StdIO& StdIO::instance() {
    static StdIO s_instance;
    return s_instance;
}

StdIO& StdIO::endl(StdIO& io) {
    std::cout << '\n';
    return io;
}

StdIO& StdIO::operator<<(StdIO& (*manip_func)(StdIO&)) {
    return manip_func(*this);
}

StdIO& StdIO::operator<<(const TUI::Color& col) {
    std::cout << "\033[" << static_cast<int>(col.code) << "m";
    return *this;
}

StdIO& StdIO::operator<<(const TUI::GotoXY& pos) {
    std::cout << "\033[" << pos.y << ";" << pos.x << "f";
    return *this;
}

StdIO& StdIO::clear(StdIO& io) {
    std::cout << "\033[2J\033[H";
    return io;
}

StdIO& StdIO::operator<<(const TUI::ClearScreen&) {
    std::cout << "\033[2J\033[H";
    return *this;
}

// BuffIO class implementations
BuffIO& BuffIO::instance() {
    static BuffIO s_instance;
    return s_instance;
}

BuffIO& BuffIO::operator<<(BuffIO& (*manip_func)(BuffIO&)) {
    return manip_func(*this);
}

void BuffIO::flush_to_stdout() {
    std::cout << buffer.str();
    buffer.str("");
    buffer.clear();
}

BuffIO& BuffIO::operator<<(const TUI::Color& col) {
    buffer << "\033[" << static_cast<int>(col.code) << "m";
    return *this;
}

BuffIO& BuffIO::operator<<(const TUI::GotoXY& pos) {
    buffer << "\033[" << pos.y << ";" << pos.x << "f";
    return *this;
}

BuffIO& BuffIO::operator<<(const TUI::ClearScreen&) {
    buffer << "\033[2J\033[H";
    return *this;
}

// FLUSH manipulator function
BuffIO& FLUSH(BuffIO& fio_obj) {
    fio_obj.flush_to_stdout();
    return fio_obj;
}