#ifndef MOVIEDATABASE_H
#define MOVIEDATABASE_H

#include "Movie.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <memory>
#include <mutex>
using namespace std;

class MovieDatabase{
public:
    static MovieDatabase& getInstance();

    void loadFromCSV(const string& filename);
    template <typename Predicate>
    vector<Movie> search(Predicate predicate) const;
    vector<Movie> searchByTitle(const string& keyword) const;
    vector<Movie> searchByTag(const string& tag) const;
    vector<Movie> getMoviesForWatchLater() const;
    vector<Movie> getSimilarMovies(const vector<Movie>& liked_movies) const;

private:
    MovieDatabase() = default;
    vector<Movie> movies;
    unordered_map<string, vector<Movie>> tag_index;
    mutable mutex mtx;
};

#endif // MOVIEDATABASE_H