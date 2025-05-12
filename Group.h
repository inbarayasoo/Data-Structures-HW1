#ifndef WE1_GROUP_H
#define WE1_GROUP_H
#include "AVLTree.h"
#include "User.h"
#include <cassert>

class User;
/**
 * @class Group
 * @brief Represents a group of users in the streaming database.
 */
class Group {
public:
    /**
     * @brief Constructs a Group object.
     *
     * @param groupId The ID of the group.
     */
    explicit Group(int groupId);

    /**
     * @brief Destructor.
     */
    ~Group();

    /**
     * @brief Insert a user into the group.
     *
     * @param user Pointer to the User object to insert.
     */
    void insertUser(User* user);

    /**
     * @brief Remove a user from the group.
     *
     * @param userId The ID of the user to remove.
     */
    void removeUser(int userId);


    /**
     * @brief Get the size of the group.
     *
     * @return int The size of the group.
     */
    int getGroupSize() const;

    /**
     * @brief Check if the group is VIP.
     *
     * @return bool True if the group is VIP, false otherwise.
     */
    bool isVip() const;

    /**
     * @brief Get the watch count of a specific genre in the group.
     *
     * @param genre The genre to get the watch count for.
     * @return int The watch count of the genre in the group.
     */
    int getGroupGenreWatchCount(Genre genre) const;

    /**
     * @brief Increase the watch count of a specific genre in the group.
     *
     * @param genre The genre to increase the watch count for.
     */
    void increaseGenreWatchCount(Genre genre);

    /**
     * @brief Check if the group is empty.
     *
     * @return bool True if the group is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Get the ID of the group.
     *
     * @return int The ID of the group.
     */

    /**
     * @brief Get the ID of the group.
     *
     * @return int The ID of the group.
     */
    int getGroupId() const;

    /**
     * @brief Get the most watched genre in the group.
     *
     * @return Genre The most watched genre in the group.
     */
    Genre getMostWatchedGenre();

    /**
     * @brief Increase the watch count of a specific genre for private users in the group.
     *
     * @param genre The genre to increase the watch count for.
     * @param views The number of views to increase (default is 1).
     */
    void increasePrivateUsersGenreWatchCount(Genre genre, int views = 1);

private:
    int m_groupId;                  /**< The ID of the group. */
    bool m_isVip;                   /**< Indicates if the group is VIP. */
    int m_regularUsersCount;        /**< The count of regular users in the group. */
    int m_vipUsersCount;            /**< The count of VIP users in the group. */
    static const int GENRE_COUNT = 4;
    int m_genreWatchCount[GENRE_COUNT];         /**< The watch count for each genre in the group. */
    int m_totalGroupWatches[GENRE_COUNT];       /**< The total watch count for each genre in the group. */
    AVLTree<int, User*> m_users;    /**< The AVL tree of users in the group. */

    /**
     * @brief Update the VIP status of the group based on the number of VIP users.
     */
    void updateIsVip();
    /**
     * @brief Remove all users from the group.
     */
    void removeAllUsers();
};

#endif //WE1_GROUP_H
