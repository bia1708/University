import {
	TableContainer,
	Paper,
	Table,
	TableHead,
	TableRow,
	TableCell,
	TableBody,
	CircularProgress,
	Container,
	IconButton,
	Tooltip,
    TextField,
} from "@mui/material";
import React from "react";
import { useEffect, useState } from "react";
import { Link } from "react-router-dom";
import ReadMoreIcon from "@mui/icons-material/ReadMore";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import AddIcon from "@mui/icons-material/Add";
import FilterAltIcon from '@mui/icons-material/FilterAlt';
import { BACKEND_API_URL } from "../constants";
import { Movie } from "../models/Movie";
import { Director } from "../models/Director";

export const FilterMovies = () => {
	const [directors, setDirectors] = useState<Director[]>([]);
    const [input, setInput] = useState<number | undefined>();

	useEffect(() => {
		fetch(`${BACKEND_API_URL}/directors`)
			.then((response) => response.json())
			.then((data) => {
				setDirectors(data);
			});
	}, []);

    const [loading, setLoading] = useState(false);
	const [movies, setMovies] = useState<Movie[]>([]);

	useEffect(() => {
        setLoading(true);
		fetch(`${BACKEND_API_URL}/movies/`)
			.then((response) => response.json())
			.then((data) => {
				setMovies(data);
				setLoading(false);
			});
	}, []);

	const [filteredMovies, setFiltered] = useState<Movie[]>([]);
	useEffect(() => {
        setLoading(true);
		fetch(`${BACKEND_API_URL}/movies/`)
			.then((response) => response.json())
			.then((data) => {
				setFiltered(data);
				setLoading(false);
			});
	}, []);


    const getDirectorById = (id: number) => {
		return directors.find((director) => director.id === id) || directors[0];
	};

    const getMoviesByReleaseDate = (release_date: number | undefined) => {
        if(typeof release_date == "undefined")
            return [];
		return movies.filter((movie) => movie.release_date === release_date);
	  };

    const filterMovies = async (event: React.FormEvent<HTMLFormElement>) => {
		event.preventDefault();
		try {
			setFiltered(filteredMovies => getMoviesByReleaseDate(input))
		} catch (error) {
			console.log(error);
		}
	};

	return (
		<Container>
			<h1>Movie List</h1>

            <form onSubmit={filterMovies}>
                <TextField
                    id="movie_release"
                    label="Release Date"
                    variant="outlined"
                    fullWidth
                    sx={{ mb: 2 }}
                    onChange={(event) => {
						setInput(input => parseInt(event.target.value)),
						setFiltered(filteredMovies => movies)}}
                />
            </form>

			{loading && <CircularProgress />}
			{!loading && filteredMovies.length === 0 && <p>No movies found</p>}
			{filteredMovies.length > 0 && (
				<TableContainer component={Paper}>
					<Table sx={{ minWidth: 650 }} aria-label="simple table">
						<TableHead>
							<TableRow>
								<TableCell>#</TableCell>
								<TableCell align="right">Title</TableCell>
								<TableCell align="right">Release Date</TableCell>
								<TableCell align="right">Director</TableCell>
								<TableCell align="center">Imdb Score</TableCell>
                                <TableCell align="center">Votes</TableCell>
							</TableRow>
						</TableHead>
						<TableBody>
							{filteredMovies.map((movie, index) => (
								<TableRow key={movie.id}>
									<TableCell component="th" scope="row">
										{index + 1}
									</TableCell>
									<TableCell component="th" scope="row">
										<Link to={`/movies/${movie.id}/details`} title="View movie details">
											{movie.movie_text}
										</Link>
									</TableCell>
									<TableCell align="right">{movie.release_date}</TableCell>
									<TableCell align="right">{getDirectorById(movie.director_id).director_name}</TableCell>
                                    <TableCell align="right">{movie.imdb_score}</TableCell>
                                    <TableCell align="right">{movie.votes}</TableCell>
								</TableRow>
							))}
						</TableBody>
					</Table>
				</TableContainer>
			)}
		</Container>
	);
};