#include <cassert>
#include "User.h"

User::User(int userId, bool isVip) :
    m_userId(userId),
    m_isVip(isVip),
    m_isInGroup(false),
    m_group(nullptr),
    m_genreWatchCount(),
    m_previousGroupGenreWatchCount()
    {}

int User::getUserId() const {
    return m_userId;
}

void User::setGroup(Group *group) {

    assert(!isInGroup() && group != nullptr);

    if (!isInGroup()) {
        m_isInGroup = true;

        for (int i = 0; i < GENRE_COUNT; ++i) {
            m_previousGroupGenreWatchCount[i] = group->getGroupGenreWatchCount(static_cast<Genre>(i));
        }

        m_group = group;
    }
}

bool User::isInGroup() const {
    return m_isInGroup;
}

bool User::isVip() const {
    return m_isVip;
}

Group *User::getGroup() const {
    return m_group;
}

void User::increaseGenreWatchCount(Genre genre) {
    m_genreWatchCount[static_cast<int>(genre)]++;

    if (isInGroup()) {
        m_group->increasePrivateUsersGenreWatchCount(genre);
    }
}


int User::getGenreWatchCount(Genre genre) const {

    int count = 0;
    if (genre == Genre::NONE) {

        for (int i = 0; i < GENRE_COUNT; ++i) {
            count += getGenreWatchCountAux(static_cast<Genre>(i));
        }
    }
    else {
        count = getGenreWatchCountAux(genre);
    }
    return count;
}

int User::getGenreWatchCountAux(Genre genre) const {
    int groupGenreWatchCount = 0;

    if (isInGroup()) {
        groupGenreWatchCount = m_group->getGroupGenreWatchCount(genre) - m_previousGroupGenreWatchCount[static_cast<int>(genre)];
    }

    return m_genreWatchCount[static_cast<int>(genre)] + groupGenreWatchCount;
}

void User::removeGroup() {
    assert(isInGroup() == true);
    for (int i = 0; i < GENRE_COUNT; ++i) {
        m_genreWatchCount[i] += m_group->getGroupGenreWatchCount(static_cast<Genre>(i)) - m_previousGroupGenreWatchCount[i];
    }
    m_isInGroup = false;
    m_group = nullptr;
}
