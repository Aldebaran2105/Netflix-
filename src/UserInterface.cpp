#include "../include/UserInterface.h"
#include <iostream>

using namespace std;

UserInterface::UserInterface(MovieDatabase& db) : database(db) {}

void UserInterface::run() {
    while (true) {
        showMainMenu();
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "Enter search keyword: ";
            string keyword;
            cin >> keyword;
            auto results = database.searchByTitle(keyword);
            showSearchResults(results);
        } else if (choice == 2) {
            cout << "Enter tag: ";
            string tag;
            cin >> tag;
            auto results = database.searchByTag(tag);
            showSearchResults(results);
        } else if (choice == 3) {
            auto watch_later = database.getMoviesForWatchLater();
            showSearchResults(watch_later);
        } else {
            break;
        }
    }
}

void UserInterface::showMainMenu() {
    cout << "1. Search by title\n";
    cout << "2. Search by tag\n";
    cout << "3. Show watch later list\n";
    cout << "4. Exit\n";
    cout << "Enter choice: ";
}

void UserInterface::showSearchResults(const vector<Movie>& results) {
    for (size_t i = 0; i < results.size(); ++i) {
        cout << i + 1 << ". " << results[i].getTitle() << "\n";
    }
    cout << "Enter movie number to view details, or 0 to go back: ";
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= results.size()) {
        showMovieDetails(const_cast<Movie&>(results[choice - 1])); // Cambié para permitir modificación
    }
}

void UserInterface::showMovieDetails(Movie& movie) { // Cambié el parámetro a referencia no-const
    cout << "Title: " << movie.getTitle() << "\n";
    cout << "Synopsis: " << movie.getPlotSynopsis() << "\n";
    cout << "1. Like\n";
    cout << "2. Add to watch later\n";
    cout << "3. Back\n";
    int choice;
    cin >> choice;
    if (choice == 1) {
        movie.like();
    } else if (choice == 2) {
        movie.addToWatchLater();
    }
}
