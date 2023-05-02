import { Button, Card, CardActions, CardContent, IconButton, MenuItem, TextField } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useNavigate, useParams } from "react-router-dom";
import { BACKEND_API_URL } from "../constants";
import { Movie } from "../models/Movie";
import { Director } from "../models/Director";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { ReactSearchAutocomplete } from 'react-search-autocomplete';
import Autosuggest from 'react-autosuggest';
import axios from "axios";

export const MovieAdd = () => {
	const navigate = useNavigate();
	const [directors, setDirectors] = useState<Director[]>([]);

	useEffect(() => {
		fetch(`${BACKEND_API_URL}/directors`)
			.then((response) => response.json())
			.then((data) => {
				setDirectors(data);
			});
	}, []);

	const [movie, setMovie] = useState<Movie>({
		movie_text: "",
		release_date: 0,
		director_id: 0,
		//director: directors[0],
		imdb_score: 0,
		votes: 0,
	});

	const addMovie = async (event: React.FormEvent<HTMLFormElement>) => {
		event.preventDefault();
		try {
			console.log(movie);
			// await axios.post(`${BACKEND_API_URL}/movies`, movie);
			const response = await fetch(`${BACKEND_API_URL}/movies/`, {
				method: "POST",
				headers: { "Content-Type": "application/json" },
				body: JSON.stringify(movie),
			  });
			navigate("/movies");
		} catch (error) {
			console.log(error);
		}
	};

	const items = directors.map(dir => dir.director_name).map((option) => ({
		target: { value: option }}));

	// const inputProps = {
	// 	value,
	// 	onChange,
	// 	placeholder: 'Type a name',
	// 	};

	return (
		<Container>
			<Card>
				<CardContent>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/movies`}>
						<ArrowBackIcon />
					</IconButton>{" "}
					<form onSubmit={addMovie}>
						<TextField
							id="movie_text"
							label="Title"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event) => setMovie({ ...movie, movie_text: event.target.value })}
						/>
						<TextField
							id="release_date"
							label="Release Date"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event) => setMovie({ ...movie, release_date: parseInt(event.target.value) })}
						/>
						{/* <Autosuggest
						suggestions={directors}
						// onSuggestionsFetchRequested={onSuggestionsFetchRequested}
						// onSuggestionsClearRequested={onSuggestionsClearRequested}
						getSuggestionValue={(suggestion: Director) => suggestion.id}
						renderSuggestion={(suggestion: Director) => <span>{suggestion.director_name}</span>}
						// inputProps={inputProps}
						/> */}
						<TextField
							id="director"
							label="Director"
							variant="outlined"
							name="director"
							fullWidth
							sx={{ mb: 2 }}
							select
							// value={movie.director.id}
							onChange={(event) => setMovie({ ...movie, director_id: parseInt(event.target.value) })} // setMovie({ ...movie, director: getDirectorById(parseInt(event.target.value)) })}
						>
						{directors.map((director) => (
							<MenuItem key={director.id} value={director.id}>
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
							onChange={(event) => setMovie({ ...movie, imdb_score: parseInt(event.target.value) })}
						/>
						<TextField
							id="votes"
							label="Votes"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event) => setMovie({ ...movie, votes: parseInt(event.target.value) })}
						/>

						<Button type="submit">Add Movie</Button>
					</form>
				</CardContent>
				<CardActions></CardActions>
			</Card>
		</Container>
	);
};