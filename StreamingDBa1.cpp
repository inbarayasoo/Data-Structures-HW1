#include "StreamingDBa1.h"

streaming_database::streaming_database() :
        m_users(AVLTree<int, User*>()),
        m_movies(AVLTree<int, Movie*>()),
        m_groups(AVLTree<int, Group*>()),
        m_ranksAllMovies(AVLTree<Movie::MovieRanking, Movie*>()),
        m_genreAux()
{
	for(int i = 0; i < GENRE_COUNT; ++i)
    {
        m_genreAux[i] = new GenreAux(static_cast<Genre>(i));
    }
}

streaming_database::~streaming_database()
{
    for (int i = 0; i < GENRE_COUNT; ++i) {
        delete m_genreAux[i];
    }
    deleteAllocatedObjects(m_groups);
    deleteAllocatedObjects(m_users);
    deleteAllocatedObjects(m_movies);
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if (movieId <= 0 || views < 0 || genre == Genre::NONE) {
        return StatusType::INVALID_INPUT;
    }
    else if (m_movies.contains(movieId)) {
        return StatusType::FAILURE;
    }

    try {
        Movie* movie = new Movie(movieId, genre, views, vipOnly);
        m_movies.insert(movieId, movie);
        m_ranksAllMovies.insert(movie->getMovieRanking(), movie);
        m_genreAux[static_cast<int>(genre)]->insertMovie(movie);
    }
    catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    if (movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    else if (!(m_movies.contains(movieId))) {
        return StatusType::FAILURE;
    }

    Movie* movieToDelete = *(m_movies.find(movieId));
    assert(movieToDelete != nullptr);

    try{
        m_movies.remove(movieId);
        m_ranksAllMovies.remove(movieToDelete->getMovieRanking());
        m_genreAux[static_cast<int>(movieToDelete->getGenre())]->removeMovie(movieToDelete);
        delete movieToDelete;
    }
    catch (std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    if (userId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    else if (m_users.contains(userId)) {
        return StatusType::FAILURE;
    }

    try {
        User* user = new User(userId, isVip);
        m_users.insert(userId, user);
    }
    catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
    if (userId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    else if (!(m_users.contains(userId))) {
        return StatusType::FAILURE;
    }

    User* userToDelete = *(m_users.find(userId));
    assert(userToDelete != nullptr);

    try{
        if (userToDelete->isInGroup()) {
            userToDelete->getGroup()->removeUser(userId);
        }

        m_users.remove(userId);
        delete userToDelete;
    }
    catch (std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
    if (groupId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    else if (m_groups.contains(groupId)) {
        return StatusType::FAILURE;
    }

    try {
        Group* group = new Group(groupId);
        m_groups.insert(groupId, group);
    }
    catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
    if (groupId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    else if (!(m_groups.contains(groupId))) {
        return StatusType::FAILURE;
    }

    Group* groupToDelete = *(m_groups.find(groupId));
    assert(groupToDelete != nullptr);

    try{
        m_groups.remove(groupId);
        delete groupToDelete;
    }
    catch (std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if (userId <= 0 || groupId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    else if (!(m_users.contains(userId)) || !(m_groups.contains(groupId))) {
        return StatusType::FAILURE;
    }

    User* user = *(m_users.find(userId));
    Group* group = *(m_groups.find(groupId));
    assert(user != nullptr && group != nullptr);

    if (user->isInGroup()) {
        return StatusType::FAILURE;
    }

    try{
        group->insertUser(user);
        user->setGroup(group);
    }
    catch (std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if (userId <= 0 || movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    else if (!(m_users.contains(userId)) || !(m_movies.contains(movieId))) {
        return StatusType::FAILURE;
    }
    User* user = *(m_users.find(userId));
    Movie* movie = *(m_movies.find(movieId));
    assert(user != nullptr && movie != nullptr);

    if(movie->isVipOnly() && !(user->isVip())) {
        return StatusType::FAILURE;
    }

    Genre genre = movie->getGenre();
    user->increaseGenreWatchCount(genre);
    Movie::MovieRanking prevRanking = movie->getMovieRanking();
    movie->addViews();
    updateRanking(movie, prevRanking);

    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if (groupId <= 0 || movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    else if (!(m_groups.contains(groupId)) || !(m_movies.contains(movieId))) {
        return StatusType::FAILURE;
    }

    Movie* movie = *(m_movies.find(movieId));
    Group* group = *(m_groups.find(groupId));
    assert(group != nullptr && movie != nullptr);
    int groupSize = group->getGroupSize();

    if (groupSize <= 0 || (movie->isVipOnly() && !(group->isVip()))) {
        return StatusType::FAILURE;
    }
    Genre genre = movie->getGenre();
    group->increaseGenreWatchCount(genre);
    Movie::MovieRanking prevRanking = movie->getMovieRanking();
    movie->addViews(groupSize);

    updateRanking(movie, prevRanking);

	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    if (genre < Genre::COMEDY || genre > Genre::NONE) {
        return {StatusType::INVALID_INPUT};
    }

    int count = 0;
    if (genre != Genre::NONE){
        count = m_genreAux[static_cast<int>(genre)]->getMoviesCount();
    }

    else {
        for (int i = 0; i < GENRE_COUNT; i++) {
            count += m_genreAux[i]->getMoviesCount();
        }
    }
    return {count};
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    if (output == nullptr) {
        return StatusType::INVALID_INPUT;
    }
    output_t<int> moviesCountObject = get_all_movies_count(genre);
    int moviesCount = moviesCountObject.ans();
    if (moviesCount == 0) {
        return StatusType::FAILURE;
    }
    try {
        Movie **movies = new Movie *[moviesCount];

        fillArrayInOrderAux(movies, genre, moviesCount);

        for (int i = 0; i < moviesCount; ++i) {
            output[i] = movies[i]->getMovieId();
        }
        delete[] movies;
    }
    catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    if (userId <= 0) {
        return {StatusType::INVALID_INPUT};
    }
    else if (!(m_users.contains(userId))) {
        return {StatusType::FAILURE};
    }

    User* user = *(m_users.find(userId));
    assert(user != nullptr);

    return {user->getGenreWatchCount(genre)};
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if (userId <= 0 || movieId <= 0 || rating < MIN_RANK || rating > MAX_RANK) {
        return StatusType::INVALID_INPUT;
    }
    else if (!(m_users.contains(userId)) || !(m_movies.contains(movieId))) {
        return StatusType::FAILURE;
    }

    Movie* movie = *(m_movies.find(movieId));
    User* user = *(m_users.find(userId));
    assert(user != nullptr && movie != nullptr);

    if (movie->isVipOnly() && !(user->isVip())) {
        return StatusType::FAILURE;
    }
    Movie::MovieRanking prevRanking = movie->getMovieRanking();
    movie->updateRating(rating);
    updateRanking(movie, prevRanking);

    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    if (groupId <= 0) {
        return {StatusType::INVALID_INPUT};
    }
    else if (!(m_groups.contains(groupId))) {
        return {StatusType::FAILURE};
    }

    Group* group = *(m_groups.find(groupId));
    assert(group != nullptr);
    if (group->isEmpty()) {
        return {StatusType::FAILURE};
    }

    Genre genre = group->getMostWatchedGenre();

    GenreAux* genreAux = m_genreAux[static_cast<int>(genre)];

    if (genreAux->isEmpty()) {
        return {StatusType::FAILURE};
    }

    Movie* movie = genreAux->getMostRecommendedMovie();
    assert(movie != nullptr);

    return {movie->getMovieId()};
}

void streaming_database::updateRanking(Movie* movie, Movie::MovieRanking prevRanking) {
    assert(movie != nullptr);

    m_ranksAllMovies.remove(prevRanking);
    Movie::MovieRanking newRanking = movie->getMovieRanking();
    m_ranksAllMovies.insert(newRanking, movie);

    GenreAux* genreAux = m_genreAux[static_cast<int>(movie->getGenre())];
    genreAux->updateRanking(movie, prevRanking);
}

void streaming_database::fillArrayInOrderAux(Movie **movies, Genre genre, int size) const {

    if (genre != Genre::NONE) {
        m_genreAux[static_cast<int>(genre)]->fillArrayInOrder(movies, size);
    }
    else {
        m_ranksAllMovies.fillArrayInOrder(movies, size);
    }
}

template<class Key, class T>
void streaming_database::deleteAllocatedObjects(AVLTree<Key, T> &tree) {

    T* array = new T[tree.getSize()];
    tree.fillArrayInOrder(array, tree.getSize());
    for (int i = 0; i < tree.getSize(); ++i) {
        delete array[i];
    }
    delete[] array;
}
