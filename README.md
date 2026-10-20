# C++17 / Qt6 Desktop Media Management System

A desktop application designed with modern C++17, Qt6, and Clean Architecture principles.

## Architecture & Features

- **Layered Architecture:** Strict separation of concerns across Domain, Template Repository, Service, and GUI presentation layers.
- **Command Pattern (Undo/Redo):** Fully polymorphic command-based undo/redo engine supporting all state-mutating operations (`add`, `remove`, `update`).
- **Qt6 Model/View:** Custom `QAbstractTableModel` implementation (`WatchlistTableModel`) paired with a `QTableView` for responsive data binding.
- **Analytics & Visualization:** Built-in dynamic data visualization using Qt Charts (`QBarSeries`, `QBarCategoryAxis`).
- **Multi-Format Persistence:** Runtime polymorphic storage supporting persistent text repositories, CSV output, and HTML table reporting with external browser launching.

## Technologies Used

- **Language:** Modern C++ (C++17)
- **Framework:** Qt6 (Widgets, Charts, Core, Gui)
- **Build System:** CMake (v3.16+)

## Build & Run

```bash
cmake -B build -S .
cmake --build build
./build/App
```
