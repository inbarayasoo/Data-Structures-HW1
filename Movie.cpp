#include <cassert>
#include "Movie.h"



int Movie::getMovieId() const {
    return m_movieId;
}

Movie::Movie(int movieId, Genre m_genre, int views, bool isVipOnly) :
        m_movieId(movieId),
        m_genre(m_genre),
        m_views(views),
        m_isVipOnly(isVipOnly),
        m_averageRating(0),
        m_numberOfRaters(0)
    {}

Genre Movie::getGenre() const {
    return m_genre;
}

bool Movie::isVipOnly() const {
    return m_isVipOnly;
}

void Movie::addViews(int viewsToAdd) {

    assert(viewsToAdd > 0);
    m_views += viewsToAdd;

}

void Movie::updateRating(int rating) {

    m_numberOfRaters++;
    m_averageRating = (m_averageRating * (m_numberOfRaters - 1) + rating) / m_numberOfRaters;
}

Movie::MovieRanking Movie::getMovieRanking() const {
    return {m_movieId, m_views, m_averageRating};
}


Movie::MovieRanking::MovieRanking(int movieId, int views, double averageRating) :
        m_movieId(movieId),
        m_views(views),
        m_averageRating(averageRating)
        {}


bool Movie::MovieRanking::operator>(const Movie::MovieRanking &movieRanking) const {

    if (m_averageRating > movieRanking.m_averageRating) {
        return false;
    }

    if (m_averageRating == movieRanking.m_averageRating) {
        if (m_views > movieRanking.m_views) {
            return false;
        }
    }

    if (m_averageRating == movieRanking.m_averageRating && m_views == movieRanking.m_views) {
        if (m_movieId <= movieRanking.m_movieId) {
            return false;
        }
    }
    return true;
}

bool Movie::MovieRanking::operator==(const Movie::MovieRanking &movieRanking) const {
    return m_movieId == movieRanking.m_movieId;
}

bool Movie::MovieRanking::operator<(const Movie::MovieRanking &movieRanking) const {
    return !(*this > movieRanking) && !(*this == movieRanking);
}

