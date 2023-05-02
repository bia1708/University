import { Movie } from "./Movie";

export interface Actor {
    id?: number;
    actor_name: string;
    birth_date: string;
    star_sign: string;
    contact: string;
    votes: number;
    movies?: Movie[];
    movie_count?: number;
}