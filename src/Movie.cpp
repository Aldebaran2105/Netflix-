#include "../include/Movie.h"
#include <sstream>
#include <algorithm>

using namespace std;

Movie::Movie(const string& imdb_id, const string& title, const string& plot_synopsis, const vector<string>& tags, const string& split, const string& synopsis_source)
    : imdb_id(imdb_id), title(title), plot_synopsis(plot_synopsis), tags(tags), split(split), synopsis_source(synopsis_source), liked(false), watch_later(false) {}

string Movie::getImdbId() const {
    return imdb_id;
}

string Movie::getTitle() const {
    return title;
}

string Movie::getPlotSynopsis() const {
    return plot_synopsis;
}

vector<string> Movie::getTags() const {
    return tags;
}

string Movie::getSplit() const {
    return split;
}

string Movie::getSynopsisSource() const {
    return synopsis_source;
}

void Movie::like() {
    liked = true;
}

void Movie::addToWatchLater() {
    watch_later = true;
}

bool Movie::isLiked() const {
    return liked;
}

bool Movie::isWatchLater() const {
    return watch_later;
}
