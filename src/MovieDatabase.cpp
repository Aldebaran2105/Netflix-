#include "../include/MovieDatabase.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void MovieDatabase::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo: " + filename);
    }
    string line;
    
    while (getline(file, line)) {
        vector<string> tokens = Utils::split(line, ',');
        if (tokens.size() < 6) continue;

        string imdb_id = tokens[0];
        string title = tokens[1];
        string plot_synopsis = tokens[2];
        vector<string> tags = Utils::split(tokens[3], '|');
        string split = tokens[4];
        string synopsis_source = tokens[5];

        Movie movie(imdb_id, title, plot_synopsis, tags, split, synopsis_source);
        movies.push_back(movie);

        for (const auto& tag : tags) {
            tag_index[tag].push_back(movie);
        }
    }
}

vector<Movie> MovieDatabase::searchByTitle(const string& keyword) const {
    vector<Movie> result;
    for (const auto& movie : movies) {
        if (movie.getTitle().find(keyword) != string::npos) {
            result.emplace_back(movie);
        }
    }
    sort(result.begin(), result.end(), [](const Movie& a, const Movie& b) {
        return a.getTitle() < b.getTitle();
    });
    return result;
}

vector<Movie> MovieDatabase::searchByTag(const string& tag) const {
    if (tag_index.find(tag) != tag_index.end()) {
        return tag_index.at(tag);
    }
    return {};
}

vector<Movie> MovieDatabase::getMoviesForWatchLater() const {
    vector<Movie> result;
    for (const auto& movie : movies) {
        if (movie.isWatchLater()) {
            result.push_back(movie);
        }
    }
    return result;
}

vector<Movie> MovieDatabase::getSimilarMovies(const vector<Movie>& liked_movies) const {
    unordered_set<string> liked_tags;
    for (const auto& movie : liked_movies) {
        const auto& tags = movie.getTags();
        liked_tags.insert(tags.begin(), tags.end());
    }

    vector<Movie> result;
    for (const auto& movie : movies) {
        const auto& tags = movie.getTags();
        for (const auto& tag : tags) {
            if (liked_tags.find(tag) != liked_tags.end()) {
                result.push_back(movie);
                break;
            }
        }
    }
    return result;
}
