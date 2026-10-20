cmake_minimum_required(VERSION 3.16)
project(App LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets Charts REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    Domain/Movie.cpp Domain/Movie.h
    Domain/Link.cpp Domain/Link.h
    Repo/Watchlist.cpp Repo/Watchlist.h
    Service/MovieService.cpp Service/MovieService.h
    Service/MovieValidator.cpp Service/MovieValidator.h
    UI/GUI.cpp UI/GUI.h
    UI/AdminGUI.cpp UI/AdminGUI.h
    UI/UserGUI.cpp UI/UserGUI.h
    UI/BrowseGUI.cpp UI/BrowseGUI.h
    UI/ChartWidget.cpp UI/ChartWidget.h
    UI/WatchlistDialog.h
    UI/WatchlistWindow.h
    UI/WatchlistTableModel.cpp UI/WatchlistTableModel.h
    Domain/Exceptions.cpp Domain/Exceptions.h
        UI/WatchlistWindow.cpp
)

include_directories(Domain Repo Service UI .)

add_executable(App ${PROJECT_SOURCES})
target_link_libraries(App PRIVATE Qt6::Widgets Qt6::Charts)