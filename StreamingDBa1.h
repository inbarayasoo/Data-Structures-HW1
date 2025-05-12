// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_

#include "wet1util.h"
#include "AVLTree.h"
#include "User.h"
#include "Movie.h"
#include "Group.h"
#include "GenreAux.h"
#include <cassert>

class streaming_database {
private:
    AVLTree<int, User*> m_users;                     // AVL tree to store users
    AVLTree<int, Movie*> m_movies;                   // AVL tree to store movies
    AVLTree<int, Group*> m_groups;                   // AVL tree to store groups
    AVLTree<Movie::MovieRanking, Movie*> m_ranksAllMovies;    // AVL tree to store movie rankings
    static const int GENRE_COUNT = 4;                // Number of genres
    GenreAux* m_genreAux[GENRE_COUNT];                // Array of genre auxiliary structures
    static const int MAX_RANK = 100;                 // Maximum movie ranking
    static const int MIN_RANK = 0;                   // Minimum movie ranking

    // Private helper methods
    /**
    * @brief Updates the ranking of a movie in the database.
    *
    * @param movie Pointer to the movie object.
    * @param prevRanking The previous ranking of the movie.
    */
    void updateRanking(Movie* movie, Movie::MovieRanking prevRanking);

    /**
     * @brief Fills an array with the IDs of movies in a specific genre in ascending order.
     *
     * @param movies Pointer to the array of movie IDs.
     * @param genre The genre of the movies.
     * @param size The size of the array.
     */
    void fillArrayInOrderAux(Movie** movies, Genre genre, int size) const;

    /**
     * @brief Deletes all allocated objects in the AVL tree.
     *
     * @tparam Key The key type of the AVL tree.
     * @tparam T The value type of the AVL tree.
     * @param tree Reference to the AVL tree.
     */
    template<class Key, class T>
    void deleteAllocatedObjects(AVLTree<Key, T>& tree);

	
public:


	// <DO-NOT-MODIFY> {
    // Constructor
	streaming_database();

    // Destructor
	virtual ~streaming_database();

    /**
     * @brief Add a movie to the database.
     *
     * @param movieId The ID of the movie to add.
     * @param genre The genre of the movie.
     * @param views The initial number of views of the movie.
     * @param vipOnly Indicates whether the movie is only available to VIP users.
     * @return StatusType The status of the operation (SUCCESS, FAILURE, ALLOCATION_ERROR).
     */
	StatusType add_movie(int movieId, Genre genre, int views, bool vipOnly);

    /**
     * @brief Remove a movie from the database.
     *
     * @param movieId The ID of the movie to remove.
     * @return StatusType The status of the operation (SUCCESS, FAILURE).
     */
	StatusType remove_movie(int movieId);

    /**
     * @brief Add a user to the database.
     *
     * @param userId The ID of the user to add.
     * @param isVip Indicates whether the user is a VIP user.
     * @return StatusType The status of the operation (SUCCESS, FAILURE, ALLOCATION_ERROR).
     */
	StatusType add_user(int userId, bool isVip);

    /**
     * @brief Remove a user from the database.
     *
     * @param userId The ID of the user to remove.
     * @return StatusType The status of the operation (SUCCESS, FAILURE).
     */
	StatusType remove_user(int userId);

    /**
     * @brief Add a group to the database.
     *
     * @param groupId The ID of the group to add.
     * @return StatusType The status of the operation (SUCCESS, FAILURE, ALLOCATION_ERROR).
     */
	StatusType add_group(int groupId);

    /**
     * @brief Remove a group from the database.
     *
     * @param groupId The ID of the group to remove.
     * @return StatusType The status of the operation (SUCCESS, FAILURE).
     */
	StatusType remove_group(int groupId);

    /**
     * @brief Add a user to a group.
     *
     * @param userId The ID of the user to add to the group.
     * @param groupId The ID of the group to add the user to.
     * @return StatusType The status of the operation (SUCCESS, FAILURE).
     */
	StatusType add_user_to_group(int userId, int groupId);

    /**
     * @brief Simulate a user watching a movie.
     *
     * @param userId The ID of the user watching the movie.
     * @param movieId The ID of the movie being watched.
     * @return StatusType The status of the operation (SUCCESS, FAILURE).
     */
	StatusType user_watch(int userId, int movieId);

    /**
     * @brief Simulate a group watching a movie.
     *
     * @param groupId The ID of the group watching the movie.
     * @param movieId The ID of the movie being watched.
     * @return StatusType The status of the operation (SUCCESS, FAILURE).
     */
    StatusType group_watch(int groupId,int movieId);

    /**
     * @brief Get the count of all movies in a given genre.
     *
     * @param genre The genre of the movies.
     * @return output_t<int> The output structure containing the result count and the status of the operation.
     */
    output_t<int> get_all_movies_count(Genre genre);

    /**
     * @brief Get the IDs of all movies in a given genre.
     *
     * @param genre The genre of the movies.
     * @param output Pointer to the output array to store the movie IDs.
     * @return StatusType The status of the operation (SUCCESS, FAILURE).
     */
    StatusType get_all_movies(Genre genre, int *const output);

    /**
     * @brief Get the number of views of a user for a given genre.
     *
     * @param userId The ID of the user.
     * @param genre The genre of the movies.
     * @return output_t<int> The output structure containing the result count and the status of the operation.
     */
	output_t<int> get_num_views(int userId, Genre genre);

    /**
    * @brief Rate a movie by a user.
    *
    * @param userId The ID of the user rating the movie.
    * @param movieId The ID of the movie being rated.
    * @param rating The rating given by the user (between 1 and 10).
    * @return StatusType The status of the operation (SUCCESS, FAILURE).
    */
    StatusType rate_movie(int userId, int movieId, int rating);

    /**
     * @brief Get a recommended movie for a group.
     *
     * @param groupId The ID of the group.
     * @return output_t<int> The output structure containing the recommended movie ID and the status of the operation.
     */
	output_t<int> get_group_recommendation(int groupId);

	// } </DO-NOT-MODIFY>
};

#endif // STREAMINGDBA1_H_
