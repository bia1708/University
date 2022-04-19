from enum import Enum


def add_movie_handler(movie_service, movie_id):
    movie_service.remove_movie(movie_id)


def delete_movie_handler(movie_service, id, title, description, genre):
    movie_service.add_movie(id, title, description, genre)


def update_movie_handler(movie_service, id, title, description, genre):
    movie_service.update_movie(id, title, description, genre)


def add_client_handler(client_service, client_id):
    client_service.remove_client(client_id)


def remove_client_handler(client_service, id, name):
    client_service.add_client(id, name)


def update_client_handler(client_service, id, name):
    client_service.update_client(id, name)


def add_rental_handler(rental_service, id):
    rental_service.remove_rental(id)


def delete_rental_handler(rental_service, movie_id, client_id, rental_date):
    rental_service.rent_movie(movie_id, client_id, rental_date)


def return_movie_handler(rental_service, movie_id, client_id):
    rental_service.reverse_return_movie(movie_id, client_id)


class UndoHandler(Enum):
    ADD_MOVIE = add_movie_handler
    DELETE_MOVIE = delete_movie_handler
    UPDATE_MOVIE = update_movie_handler
    ADD_CLIENT = add_client_handler
    REMOVE_CLIENT = remove_client_handler
    UPDATE_CLIENT = update_client_handler
    ADD_RENTAL = add_rental_handler
    RETURN_MOVIE = return_movie_handler


class RedoHandler(Enum):
    ADD_MOVIE = delete_movie_handler
    DELETE_MOVIE = add_movie_handler
    UPDATE_MOVIE = update_movie_handler
    ADD_CLIENT = remove_client_handler
    REMOVE_CLIENT = add_client_handler
    UPDATE_CLIENT = update_client_handler
    ADD_RENTAL = delete_rental_handler
    RETURN_MOVIE = return_movie_handler


