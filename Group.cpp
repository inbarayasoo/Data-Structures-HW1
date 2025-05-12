//
// Created by Eitan Shaked on 07/05/2023.
//

#include "Group.h"

Group::Group(int groupId) :
        m_groupId(groupId),
        m_isVip(false),
        m_regularUsersCount(0),
        m_vipUsersCount(0),
        m_genreWatchCount(),
        m_totalGroupWatches(),
        m_users(AVLTree<int, User*>())
    {}

void Group::insertUser(User *user) {

    m_users.insert(user->getUserId(), user);

    for (int i = 0; i < GENRE_COUNT; i++) {
        m_totalGroupWatches[i] += user->getGenreWatchCount(static_cast<Genre>(i));
    }

    if (user->isVip()) {
        m_vipUsersCount++;
    }
    else {
        m_regularUsersCount++;
    }

    updateIsVip();
}

void Group::removeUser(int userId)
{
    User* user = *(m_users.find(userId));

    if (user == nullptr) {
        return;
    }

    for (int i = 0; i < GENRE_COUNT; i++) {
        m_totalGroupWatches[i] -= user->getGenreWatchCount(static_cast<Genre>(i));
    }

    user->removeGroup();
    if (user->isVip()) {
        assert(m_vipUsersCount > 0);
        m_vipUsersCount--;
        updateIsVip();
    }
    else {
        assert(m_regularUsersCount > 0);
        m_regularUsersCount--;
    }
    m_users.remove(userId);
}

int Group::getGroupSize() const {
    return m_users.getSize();
}

bool Group::isVip() const {
    return m_isVip;
}

void Group::updateIsVip() {
    m_isVip = (m_vipUsersCount > 0);
}

void Group::increaseGenreWatchCount(Genre genre) {
    ++m_genreWatchCount[static_cast<int>(genre)];
    increasePrivateUsersGenreWatchCount(genre, getGroupSize());
}

int Group::getGroupGenreWatchCount(Genre genre) const {
    return m_genreWatchCount[static_cast<int>(genre)];
}

void Group::removeAllUsers() {
    User** users = new User*[getGroupSize()];
    m_users.fillArrayInOrder(users, getGroupSize());
    for (int i = 0; i < getGroupSize(); ++i) {
        users[i]->removeGroup();
    }
    delete[] users;
}

Group::~Group() {
    removeAllUsers();
}

bool Group::isEmpty() const {
    return getGroupSize() == 0;
}

Genre Group::getMostWatchedGenre() {
    int maxGenreWatchCount = 0;
    Genre maxGenre = Genre::COMEDY;
    for (int i = 0; i < GENRE_COUNT; ++i) {
        int genreWatchCount = m_totalGroupWatches[i];
        if (genreWatchCount > maxGenreWatchCount) {
            maxGenreWatchCount = genreWatchCount;
            maxGenre = static_cast<Genre>(i);
        }
    }
    return maxGenre;
}

int Group::getGroupId() const {
    return m_groupId;
}

void Group::increasePrivateUsersGenreWatchCount(Genre genre, int views) {
    m_totalGroupWatches[static_cast<int>(genre)] += views;
}


