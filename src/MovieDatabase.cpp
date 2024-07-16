#include "../include/MovieDatabase.h"
#include "../include/Utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <thread>

using namespace std;

MovieDatabase& MovieDatabase::getInstance(){
    static MovieDatabase instance;
    return instance;
}

void MovieDatabase::loadFromCSV(const string& filename){
    thread([this, filename](){
        ifstream file(filename);
        if (!file.is_open()){
            throw runtime_error("No se pudo abrir el archivo: " + filename);
        }

        string line;
        getline(file, line);

        while (getline(file, line)){
            vector<string> tokens = Utils::split(line, ',');
            if (tokens.size() < 6) continue; 

            string imdb_id = tokens[0];
            string title = tokens[1];
            string plot_synopsis = tokens[2];
            vector<string> tags = Utils::split(tokens[3], '|');
            string split = tokens[4];
            string synopsis_source = tokens[5];

            Movie movie(imdb_id, title, plot_synopsis, tags, split, synopsis_source);

            lock_guard<mutex> lock(mtx);
            movies.push_back(movie);

            for (const auto& tag : tags) {
                tag_index[tag].push_back(movie);
            }
        }
    }).detach();
}

template <typename Predicate>
vector<Movie> MovieDatabase::search(Predicate predicate) const{
    vector<Movie> result;
    lock_guard<mutex> lock(mtx);
    for (const auto& movie : movies){
        if (predicate(movie)) {
            result.emplace_back(movie);
        }
    }
    return result;
}

vector<Movie> MovieDatabase::searchByTitle(const string& keyword) const{
    return search([&keyword](const Movie& movie) {
        return movie.getTitle().find(keyword) != string::npos;
    });
}

vector<Movie> MovieDatabase::searchByTag(const string& tag) const{
    auto it = tag_index.find(tag);
    if (it != tag_index.end()){
        return it->second;
    }
    return {};
}

vector<Movie> MovieDatabase::getMoviesForWatchLater() const{
    return search([](const Movie& movie){
        return movie.isWatchLater();
    });
}

vector<Movie> MovieDatabase::getSimilarMovies(const vector<Movie>& liked_movies) const{
    unordered_set<string> liked_tags;
    for (const auto& movie : liked_movies){
        const auto& tags = movie.getTags();
        liked_tags.insert(tags.begin(), tags.end());
    }

    return search([&liked_tags](const Movie& movie){
        const auto& tags = movie.getTags();
        return any_of(tags.begin(), tags.end(), [&liked_tags](const string& tag){
            return liked_tags.find(tag) != liked_tags.end();
        });
    });
}
