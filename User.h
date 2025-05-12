#ifndef WE1_USER_H
#define WE1_USER_H
#include "wet1util.h"
#include "Group.h"
class Group;

/**
 * @class User
 * @brief Represents a user in the streaming database.
 */
class User {
public:
    /**
     * @brief Constructs a User object.
     *
     * @param userId The ID of the user.
     * @param isVip Indicates if the user is VIP.
     */
    User(int userId, bool isVip);

    /**
     * @brief Destructor.
     */
    ~User() = default;
    /**
     * @brief Set the group of the user.
     *
     * @param group Pointer to the Group object to set as the user's group.
     */
    void setGroup(Group* group);

    /**
     * @brief Remove the group of the user.
     */
    void removeGroup();

    /**
     * @brief Get the group of the user.
     *
     * @return Group* Pointer to the user's group.
     */
    Group* getGroup() const;

    /**
     * @brief Get the ID of the user.
     *
     * @return int The ID of the user.
     */
    int getUserId() const;

    /**
     * @brief Check if the user is currently in a group.
     *
     * @return bool True if the user is in a group, false otherwise.
     */
    bool isInGroup() const;

    /**
     * @brief Get the watch count of a specific genre for the user.
     *
     * @param genre The genre to get the watch count for.
     * @return int The watch count of the genre for the user.
     */
    int getGenreWatchCount(Genre genre) const;

    /**
     * @brief Check if the user is VIP.
     *
     * @return bool True if the user is VIP, false otherwise.
     */
    bool isVip() const;


    /**
     * @brief Increase the watch count of a specific genre for the user.
     *
     * @param genre The genre to increase the watch count for.
     */
    void increaseGenreWatchCount(Genre genre);


private:
    int m_userId;                       /**< The ID of the user. */
    bool m_isVip;                       /**< Indicates if the user is VIP. */
    bool m_isInGroup;                   /**< Indicates if the user is in a group. */
    Group* m_group;                     /**< Pointer to the user's group. */
    static const int GENRE_COUNT = 4;
    int m_genreWatchCount[GENRE_COUNT];                  /**< The watch count for each genre for the user. */
    int m_previousGroupGenreWatchCount[GENRE_COUNT];     /**< The previous watch count for each genre when the user was in a group. */

    /**
     * @brief Get the watch count of a specific genre for the user (helper function).
     *
     * @param genre The genre to get the watch count for.
     * @return int The watch count of the genre for the user.
     */
    int getGenreWatchCountAux(Genre genre) const;

};

#endif //WE1_USER_H
