#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "MovieDatabase.h"

using namespace std;

class UserInterface {
public:
    UserInterface(MovieDatabase& db);
    void run();

private:
    void showMainMenu();
    void showSearchResults(const vector<Movie>& results);
    void showMovieDetails(Movie& movie);

    MovieDatabase& database;
};

#endif // USERINTERFACE_H