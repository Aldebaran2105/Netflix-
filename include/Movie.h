#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>

using namespace std;

class Movie {
public:
    Movie(const string& imdb_id, const string& title, const string& plot_synopsis, const vector<string>& tags, const string& split, const string& synopsis_source);

    string getImdbId() const;
    string getTitle() const;
    string getPlotSynopsis() const;
    vector<string> getTags() const;
    string getSplit() const;
    string getSynopsisSource() const;

    void like();
    void addToWatchLater();
    bool isLiked() const;
    bool isWatchLater() const;

private:
    string imdb_id;
    string title;
    string plot_synopsis;
    vector<string> tags;
    string split;
    string synopsis_source;
    bool liked = false; 
    bool watch_later = false;
};

#endif // MOVIE_H
