//
// Created by szili on 3/24/26.
//

#include "Service/MovieService.h"
#include "Repo/FileRepo.h"
#include <fstream>
#include <memory>
#include <QApplication>
#include "UI/GUI.h"
#include "UI/WatchlistDialog.h"


std::string getRepositoryFilename() {
    std::ifstream configFile("config.txt");
    if (!configFile.is_open()) return "Data/movies.txt";
    if (std::string line; std::getline(configFile, line)) {
        if (size_t pos = line.find("repository_file="); pos != std::string::npos) {
            std::string res = line.substr(pos + 16);
            return res;
        }
    }
    return "Data/movies.txt";
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    std::unique_ptr<Repo<Movie>> repo = std::make_unique<FileRepo<Movie>>(getRepositoryFilename());
    
    MovieService service(std::move(repo));

    if (WatchlistDialog dialog; dialog.exec() == QDialog::Accepted) {
        if (dialog.selectedType == 1) {
            service.setWatchlist(std::make_unique<CSVWatchlist>("Data/watchlist.csv"));
        } else {
            service.setWatchlist(std::make_unique<HTMLWatchList>("Data/watchlist.html"));
        }
    } else {
        return 0;
    }

    GUI gui(service);
    gui.show();
    return QApplication::exec();
}
