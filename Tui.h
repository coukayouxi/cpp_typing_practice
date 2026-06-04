#pragma once
#include <iostream>
#include <sstream>
#include <string>

// --- Define Colors and Cursor Operations in the TUI namespace ---
namespace TUI {

    // Color Enum Class (Strongly Typed Enum)
    enum class ColorCode {
        FG_RED = 31,
        FG_GREEN = 32,
        FG_BLUE = 34,
        FG_DEFAULT = 39,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_BLUE = 44,
        BG_DEFAULT = 49,
        FG_YELLOW = 33,
        FG_MAGENTA = 35,
        FG_CYAN = 36,
        FG_WHITE = 37,
        BG_YELLOW = 43,
        BG_MAGENTA = 45,
        BG_CYAN = 46,
        BG_WHITE = 47,
    };

    // Color Struct
    struct Color {
        ColorCode code;
        explicit Color(ColorCode c);
    };

    // GotoXY Struct
    struct GotoXY {
        int x, y;
        GotoXY(int px, int py);
    };

    // ClearScreen Struct
    struct ClearScreen {};

} // namespace TUI

// Forward declaration
class BuffIO;

// StdIO 类：直接操作 std::cin/std::cout
class StdIO {
private:
    StdIO() = default;

public:
    static StdIO& instance();

    template<typename T>
    StdIO& operator>>(T& value) {
        std::cin >> value;
        return *this;
    }

    template<typename T>
    StdIO& operator<<(const T& value) {
        std::cout << value;
        return *this;
    }

    static StdIO& endl(StdIO& io);

    StdIO& operator<<(StdIO& (*manip_func)(StdIO&));

    // --- Use types from TUI namespace ---
    StdIO& operator<<(const TUI::Color& col);

    StdIO& operator<<(const TUI::GotoXY& pos);

    static StdIO& clear(StdIO& io);

    StdIO& operator<<(const TUI::ClearScreen&);
};

// BuffIO 类：带缓冲区的 I/O
class BuffIO {
private:
    std::ostringstream buffer;
    BuffIO() = default;

public:
    static BuffIO& instance();

    template<typename T>
    BuffIO& operator>>(T& value) {
        std::cin >> value;
        return *this;
    }

    template<typename T>
    BuffIO& operator<<(const T& value) {
        buffer << value;
        return *this;
    }

    using manip_func_type = BuffIO & (*)(BuffIO&);
    BuffIO& operator<<(manip_func_type manip_func);

    void flush_to_stdout();

    // --- Use types from TUI namespace ---
    BuffIO& operator<<(const TUI::Color& col);

    BuffIO& operator<<(const TUI::GotoXY& pos);

    BuffIO& operator<<(const TUI::ClearScreen&);

    friend BuffIO& FLUSH(BuffIO& fio_obj);
};

// Function declarations
BuffIO& FLUSH(BuffIO& fio_obj);

// Global instances
extern inline StdIO& IO = StdIO::instance();
extern inline BuffIO& FIO = BuffIO::instance();