import { Director } from "./Director";

export interface Movie {
    id?: number;
    movie_text: string;
    release_date: number;
    director_id: number;
    director?: Director;
    imdb_score: number;
    votes: number;
    actors_count?: number;
}