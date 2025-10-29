#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Movie {
    string title;
    double imdbRating;
    int releaseYear;
    int watchTime;
};

int partition(vector<Movie>& movies, int low, int high, int choice) {
    double pivot;
    if (choice == 1) pivot = movies[high].imdbRating;
    else if (choice == 2) pivot = movies[high].releaseYear;
    else pivot = movies[high].watchTime;

    int i = low - 1;
    for (int j = low; j < high; j++) {
        double val;
        if (choice == 1) val = movies[j].imdbRating;
        else if (choice == 2) val = movies[j].releaseYear;
        else val = movies[j].watchTime;

        if (val < pivot) {
            i++;
            swap(movies[i], movies[j]);
        }
    }
    swap(movies[i + 1], movies[high]);
    return i + 1;
}

void quickSort(vector<Movie>& movies, int low, int high, int choice) {
    if (low < high) {
        int pi = partition(movies, low, high, choice);
        quickSort(movies, low, pi - 1, choice);
        quickSort(movies, pi + 1, high, choice);
    }
}

int main() {
    int n;
    cout << "Enter total number of movies: ";
    cin >> n;

    vector<Movie> movies(n);
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << "Movie " << i + 1 << " details:\n";
        cin.ignore(); // to avoid input issues
        cout << "Title: ";
        getline(cin, movies[i].title);
        cout << "IMDB Rating: ";
        cin >> movies[i].imdbRating;
        cout << "Release Year: ";
        cin >> movies[i].releaseYear;
        cout << "Watch Time (in hours): ";
        cin >> movies[i].watchTime;
        cout << endl;
    }

    cout << "choose by which parameter to sort:\n";
    cout << "1 - IMDB Rating\n2 - Release Year\n3 - Watch Time\n";
    cout << "Your choice: ";
    int choice;
    cin >> choice;
    cout << endl;

    quickSort(movies, 0, n - 1, choice);

    cout << "sorted movies\n";
    for (auto& m : movies) {
        cout << left << setw(15) << m.title 
             << " | Rating: " << m.imdbRating 
             << " | Year: " << m.releaseYear 
             << " | Watch Time: " << m.watchTime << " hrs" << endl;
    }

    cout << "\nMovies sorted successfully using QuickSort!\n";
    cout << "Time Complexity: O(n log n) on average.\n";

    return 0;
}
