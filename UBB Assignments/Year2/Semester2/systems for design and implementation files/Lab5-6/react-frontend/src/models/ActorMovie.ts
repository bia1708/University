import { Movie } from "./Movie";

export interface ActorMovie {
    id?: number;
    actor_id: number;
    actor_payment: number;
    actor_awarded: boolean;
    movie?: Movie;
    movie_id?: number;
}