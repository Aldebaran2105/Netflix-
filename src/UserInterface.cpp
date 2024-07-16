#include "../include/UserInterface.h"
#include <iostream>
#include <cctype>
#include <iomanip> 

using namespace std;

UserInterface::UserInterface(MovieDatabase& db) : database(db){}

void UserInterface::run(){
    cout << "*********************************\n";
    cout << "*        WELCOME TO THE         *\n";
    cout << "*          NETFLIX++            *\n";
    cout << "*********************************\n\n";

    bool running = true;
    while (running){
        showMainMenu();
        int choice;
        cin >> choice;

        switch (choice){
            case 1:{
                cout << "Enter search keyword: ";
                string keyword;
                cin.ignore();
                getline(cin, keyword);
                auto results = database.searchByTitle(keyword);
                showSearchResults(results);
                break;
            }
            case 2:{
                cout << "Enter tag: ";
                string tag;
                cin.ignore();
                getline(cin, tag);
                auto results = database.searchByTag(tag);
                showSearchResults(results);
                break;
            }
            case 3:{
                auto watch_later = database.getMoviesForWatchLater();
                showSearchResults(watch_later);
                break;
            }
            case 4:{
                running = false;
                break;
            }
            default:{
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
}

void UserInterface::showMainMenu(){
    cout << "\n--- Main Menu ---\n";
    cout << "1. Search by title\n";
    cout << "2. Search by tag\n";
    cout << "3. Show watch later list\n";
    cout << "4. Exit\n";
    cout << "Enter choice: ";
}

void UserInterface::showSearchResults(const vector<Movie>& results){
    if (results.empty()){
        cout << "No results found.\n";
        return;
    }

    size_t start = 0;
    bool showingResults = true;
    while (showingResults) {
        size_t end = min(start + 5, results.size());
        for (size_t i = start; i < end; ++i) {
            cout << i + 1 << ". " << results[i].getTitle();
            if (results[i].isLiked()) cout << " (Like)";
            if (results[i].isWatchLater()) cout << " (Watch Later)";
            cout << "\n";
        }
        if (end < results.size()){
            cout << "n. Next 5 results\n";
        }
        cout << "b. Back to main menu\n";
        cout << "Enter choice: ";
        string choice;
        cin >> choice;

        if (choice == "b"){
            showingResults = false;
        } else if (choice == "n" && end < results.size()){
            start += 5;
        } else if (isdigit(choice[0])){
            int index = stoi(choice) - 1;
            if (index >= 0 && index < results.size()){
                showMovieDetails(const_cast<Movie&>(results[index]));
            } else{
                cout << "Invalid choice. Please try again.\n";
            }
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void UserInterface::showMovieDetails(Movie& movie) {
    cout << "\n--- Movie Details ---\n";
    cout << "Title: " << movie.getTitle() << "\n";
    cout << "Synopsis: " << movie.getPlotSynopsis() << "\n";
    cout << "1. Like\n";
    cout << "2. Add to watch later\n";
    cout << "3. Back\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            movie.like();
            cout << "Movie liked!\n";
            break;
        case 2:
            movie.addToWatchLater();
            cout << "Movie added to watch later list!\n";
            break;
        case 3:
            break;
        default:
            cout << "Invalid choice. Returning to main menu.\n";
            break;
    }
}