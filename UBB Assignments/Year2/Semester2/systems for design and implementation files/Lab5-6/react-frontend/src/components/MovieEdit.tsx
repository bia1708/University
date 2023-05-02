import { Button, Card, CardActions, CardContent, IconButton, MenuItem, TextField } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link,  useNavigate, useParams } from "react-router-dom";
import { BACKEND_API_URL } from "../constants";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { Movie } from "../models/Movie";
import { Director } from "../models/Director";
import axios from "axios";


export const MovieEdit = () => {
	const [directors, setDirectors] = useState<Director[]>([]);
	const navigate = useNavigate();

	useEffect(() => {
		fetch(`${BACKEND_API_URL}/directors`)
			.then((response) => response.json())
			.then((data) => {
				setDirectors(data);
			});
	}, []);

	const getDirectorById = (id: number) => {
		return directors.find((director) => director.id === id) || directors[0];
	  };

	const { movieId } = useParams();
	const [movie, setMovie] = useState<Movie>({
		movie_text: "",
		release_date: 0,
		director_id: 0, // TODO: also read the teacher_id from the form (NOT from the user!)
		// director: directors[0],
		imdb_score: 0,
		votes: 0,
	});

	useEffect(() => {
		const fetchMovie = async () => {
			const response = await fetch(`${BACKEND_API_URL}/movies/${movieId}`);
			const movie = await response.json();
			setMovie({...movie, director_id: movie.director.id, director: undefined});
		};
		fetchMovie();
	}, [movieId]);

    const editMovie = async (event: React.FormEvent<HTMLFormElement>) => {
		event.preventDefault();
		try {
			console.log(JSON.stringify(movie));
			// await axios.put(`${BACKEND_API_URL}/movies`, movie);
			const response = await fetch(`${BACKEND_API_URL}/movies/${movieId}/`, {
				method: "PUT",
				headers: { "Content-Type": "application/json" },
				body: JSON.stringify(movie),
			});
			navigate("/movies");
		} catch (error) {
			console.log(error);
		}
	};


	return (
		<Container>
			<Card>
				<CardContent>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/movies/`}>
						<ArrowBackIcon />
					</IconButton>{" "}
					<h1>Movie Details</h1>
					<p>Movie Title: {movie?.movie_text}</p>
					<p>Movie Release Date: {movie?.release_date}</p>
					<p>Movie Director: {movie.director?.director_name}</p>
					<p>Movie Imdb Score: {movie?.imdb_score}</p>
                    <p>Movie Votes: {movie?.votes}</p>

                    <form onSubmit={editMovie}>
						<TextField
							id="movie_text"
							label="Title"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							value={movie.movie_text}
							onChange={(event) => setMovie({ ...movie, movie_text: event.target.value })}
						/>
						<TextField
							id="release_date"
							label="Release Date"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							value={movie.release_date}
							onChange={(event) => setMovie({ ...movie, release_date: parseInt(event.target.value) })}
						/>
						<TextField
							id="director"
							label="Director"
							variant="outlined"
							name="director"
							fullWidth
							sx={{ mb: 2 }}
							select
							value={movie.director}
							onChange={(event) => {
								setMovie({ ...movie, director_id: parseInt(event.target.value) }),
								setMovie({ ...movie, director: getDirectorById(parseInt(event.target.value)) }),
								console.log(movie.director)}}
						>
						{directors.map((director) => (
							<MenuItem key={director.id} value={director.id}>
								console.log(director.id)
							{director.director_name}
							</MenuItem>
						))}
        				</TextField>
						<TextField
							id="imdb_score"
							label="Imdb Score"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							value={movie.imdb_score}
							onChange={(event) => setMovie({ ...movie, imdb_score: parseInt(event.target.value) })}
						/>
						<TextField
							id="votes"
							label="Votes"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							value={movie.votes}
							onChange={(event) => setMovie({ ...movie, votes: parseInt(event.target.value) })}
						/>

						<Button type="submit">Edit Movie</Button>
					</form>
				</CardContent>
				<CardActions>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/movies/${movieId}/edit`}>
						<EditIcon />
					</IconButton>

					<IconButton component={Link} sx={{ mr: 3 }} to={`/movies/${movieId}/delete`}>
						<DeleteForeverIcon sx={{ color: "red" }} />
					</IconButton>
				</CardActions>
			</Card>
		</Container>
	);
};