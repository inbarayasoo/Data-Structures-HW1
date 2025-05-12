#ifndef WE1_GENREAUX_H
#define WE1_GENREAUX_H

#include "wet1util.h"
#include "Movie.h"
#include "AVLTree.h"
#include <cassert>

class GenreAux {
public:
    explicit GenreAux(Genre genre);
//    GenreAux();
    void insertMovie(Movie* movie);
    void removeMovie(Movie* movie);
    int getMoviesCount() const;
    void updateRanking(Movie* movie, Movie::MovieRanking prevRanking);
    bool isEmpty() const;
    Movie* getMostRecommendedMovie() const;
    Genre getGenre() const;

    ~GenreAux() = default;

    void fillArrayInOrder(Movie **movies, int size) const;

private:
    Genre m_genre;
    AVLTree<int, Movie*> m_genreMovies;
    AVLTree<Movie::MovieRanking, Movie*> m_ranksMovies;
    Movie* m_mostRecommendedMovie;

    void updateMostRecommendedMovie();
};

#endif //WE1_GENREAUX_H
