#ifndef MOVIEDATABASE_H
#define MOVIEDATABASE_H

#include "Movie.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class MovieDatabase {
public:
    void loadFromCSV(const string& filename);
    vector<Movie> searchByTitle(const string& keyword) const;
    vector<Movie> searchByTag(const string& tag) const;
    vector<Movie> getMoviesForWatchLater() const;
    vector<Movie> getSimilarMovies(const vector<Movie>& liked_movies) const;

private:
    vector<Movie> movies;
    unordered_map<string, vector<Movie>> tag_index;
};

#endif // MOVIEDATABASE_H
