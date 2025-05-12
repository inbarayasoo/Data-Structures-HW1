//
// Created by Eitan Shaked on 08/05/2023.
//

#include "GenreAux.h"

GenreAux::GenreAux(Genre genre) :
        m_genre(genre),
        m_genreMovies(AVLTree<int, Movie*>()),
        m_ranksMovies(AVLTree<Movie::MovieRanking, Movie*>()),
        m_mostRecommendedMovie(nullptr)
        {}

void GenreAux::insertMovie(Movie *movie) {
    assert(movie != nullptr);
    m_genreMovies.insert(movie->getMovieId(), movie);
    m_ranksMovies.insert(movie->getMovieRanking(), movie);
    updateMostRecommendedMovie();
}

void GenreAux::removeMovie(Movie* movie) {

    assert(movie != nullptr);
    m_ranksMovies.remove(movie->getMovieRanking());
    m_genreMovies.remove(movie->getMovieId());
    assert(m_genreMovies.getSize() >= 0);
    updateMostRecommendedMovie();
}

int GenreAux::getMoviesCount() const {
    assert(m_genreMovies.getSize() >= 0);
    return m_genreMovies.getSize();
}

void GenreAux::updateRanking(Movie *movie, Movie::MovieRanking prevRanking) {
    assert(movie != nullptr);
    m_ranksMovies.remove(prevRanking);
    assert(movie->getMovieId() > 0);
    Movie::MovieRanking newRanking = movie->getMovieRanking();
    m_ranksMovies.insert(newRanking, movie);
    updateMostRecommendedMovie();
}

void GenreAux::fillArrayInOrder(Movie **movies, int size) const {
    assert(movies != nullptr);
    m_ranksMovies.fillArrayInOrder(movies, size);
}

bool GenreAux::isEmpty() const {
    return m_ranksMovies.isEmpty();
}

Movie* GenreAux::getMostRecommendedMovie() const {
    return m_mostRecommendedMovie;
}

Genre GenreAux::getGenre() const {
    return m_genre;
}

void GenreAux::updateMostRecommendedMovie() {
    if (m_ranksMovies.isEmpty()) {
        m_mostRecommendedMovie = nullptr;
        return;
    }
    m_mostRecommendedMovie = *(m_ranksMovies.findMin());
}
