#ifndef WE1_MOVIE_H
#define WE1_MOVIE_H
#include "wet1util.h"
#include <cassert>

/**
 * @class Movie
 * @brief Represents a movie in the streaming database.
 */
class Movie {

public:
    class MovieRanking;

    /**
     * @brief Constructs a Movie object.
     *
     * @param movieId The ID of the movie.
     * @param genre The genre of the movie.
     * @param views The initial number of views of the movie.
     * @param isVipOnly Indicates whether the movie is only available to VIP users.
     */
    Movie(int movieId, Genre m_genre, int views, bool isVipOnly);

    /**
     * @brief Destructor.
     */
    ~Movie() = default;

    /**
     * @brief Get the ID of the movie.
     *
     * @return int The ID of the movie.
     */
    int getMovieId() const;

    /**
     * @brief Get the genre of the movie.
     *
     * @return Genre The genre of the movie.
     */
    Genre getGenre() const;

    /**
     * @brief Check if the movie is available only to VIP users.
     *
     * @return bool True if the movie is VIP-only, false otherwise.
     */
    bool isVipOnly() const;
    /**
     * @brief Add views to the movie.
     *
     * @param viewsToAdd The number of views to add (default is 1).
     */
    void addViews(int viewsToAdd = 1);

    /**
     * @brief Get the ranking of the movie.
     *
     * @return MovieRanking The ranking of the movie.
     */
    MovieRanking getMovieRanking() const;

    /**
     * @brief Update the rating of the movie.
     *
     * @param rating The rating to update.
     */
    void updateRating(int rating);


private:
    int m_movieId;          /**< The ID of the movie. */
    Genre m_genre;          /**< The genre of the movie. */
    int m_views;            /**< The number of views of the movie. */
    bool m_isVipOnly;       /**< Indicates if the movie is available only to VIP users. */
    double m_averageRating; /**< The average rating of the movie. */
    int m_numberOfRaters;   /**< The number of users who have rated the movie. */
};


/**
 * @class Movie::MovieRanking
 * @brief Represents the ranking of a movie.
 */
class Movie::MovieRanking {
public:

    /**
     * @brief Constructs a MovieRanking object.
     *
     * @param movieId The ID of the movie.
     * @param views The number of views of the movie.
     * @param averageRating The average rating of the movie.
     */
    MovieRanking(int movieId, int views, double averageRating);

    /**
     * @brief Destructor.
     */
    ~MovieRanking() = default;

    /**
     * @brief Copy constructor.
     *
     * @param movieRanking The MovieRanking object to copy.
     */
    MovieRanking(const MovieRanking& movieRanking) = default;

    /**
     * @brief Assignment operator.
     *
     * @param other The MovieRanking object to assign.
     * @return MovieRanking& The reference to the assigned MovieRanking object.
     */
    MovieRanking& operator=(const MovieRanking& other) = default;

    /**
     * @brief Less than operator.
     * @param movieRanking The MovieRanking object to compare with.
     *
     * @return bool True if this ranking is less than the given ranking, false otherwise.
     */
    bool operator<(const MovieRanking& movieRanking) const;

    /**
     * @brief Equality operator.
     *
     * @param movieRanking The MovieRanking object to compare with.
     * @return bool True if this ranking is equal to the given ranking, false otherwise.
     */
    bool operator==(const MovieRanking& movieRanking) const;

    /**
     * @brief Greater than operator.
     *
     * @param movieRanking The MovieRanking object to compare with.
     * @return bool True if this ranking is greater than the given ranking, false otherwise.
     */
    bool operator>(const MovieRanking& movieRanking) const;

private:
    int m_movieId;          /**< The ID of the movie. */
    int m_views;            /**< The number of views of the movie. */
    double m_averageRating; /**< The average rating of the movie. */
};

#endif //WE1_MOVIE_H
