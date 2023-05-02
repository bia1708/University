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
	Button,
} from "@mui/material";
import React from "react";
import { useEffect, useState } from "react";
import { Link } from "react-router-dom";
import ReactPaginate from 'react-paginate';
import ReadMoreIcon from "@mui/icons-material/ReadMore";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import AddIcon from "@mui/icons-material/Add";
import FilterAltIcon from '@mui/icons-material/FilterAlt';
import { BACKEND_API_URL } from "../constants";
import { Movie } from "../models/Movie";
import { Director } from "../models/Director";
import axios from 'axios';
import SortIcon from '@mui/icons-material/Sort';

export const AllMovies = () => {
	// const [directors, setDirectors] = useState<Director[]>([]);
	const [movies, setMovies] = useState<Movie[]>([]);
	const [loading, setLoading] = useState(false);
	const [pageCount, setPageCount] = useState(0);
  	const [currentPage, setCurrentPage] = useState(0);

	const fetchData = async () => {
		setLoading(true);
		const response = await axios.get(`${BACKEND_API_URL}movies?page=${currentPage + 1}&page_size=${pageSize}`);
		setMovies(response.data.results);
		setPageCount(response.data.page_count);
		setLoading(false);
		console.log("Page count:", pageCount);
	};

	const handlePageClick = (selectedPage: { selected: React.SetStateAction<number>; }) => {
		console.log(currentPage);
		setCurrentPage(selectedPage.selected);
	};

	const [pageSize, setPageSize] = useState(10);
	const handleChange = (event: React.ChangeEvent<HTMLInputElement | HTMLTextAreaElement>) => {
		event.preventDefault();
		const newValue = event.target.value;
		setPageSize(parseInt(newValue));
	};

	useEffect(() => {
		fetchData();
	}, [currentPage, pageSize]);


	return (
		<Container>
			<h1>Movie List</h1>

			{loading && <CircularProgress />}
			{!loading && movies.length === 0 && <p>No movies found</p>}
			{!loading && (
				<IconButton component={Link} sx={{ mr: 3 }} to={`/movies/add`}>
					<Tooltip title="Add a new movie" arrow>
						<AddIcon color="primary" />
					</Tooltip>
				</IconButton>
			)}
			{!loading && (
				<IconButton component={Link} sx={{ mr: 5 }} to={`/movies/filter/`}>
					<Tooltip title="Filter Movies" arrow>
						<FilterAltIcon color="primary" />
					</Tooltip>
				</IconButton>
			)}
			{!loading && (
				<IconButton component={Link} sx={{ mr: 5 }} to={`/movies/sort/`}>
					<Tooltip title="Sort Movies" arrow>
						<SortIcon color="primary" />
					</Tooltip>
				</IconButton>
			)}
			{movies.length > 0 && (
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
								<TableCell align="center">No. of Actors</TableCell>
								<TableCell align="center">Actions</TableCell>

							</TableRow>
						</TableHead>
						<TableBody>
							{movies.map((movie, index) => (
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
									<TableCell align="right">{movie.director?.director_name}</TableCell>
                                    <TableCell align="right">{movie.imdb_score}</TableCell>
                                    <TableCell align="right">{movie.votes}</TableCell>
                                    <TableCell align="right">{movie.actors_count}</TableCell>

									<TableCell align="right">
										<IconButton
											component={Link}
											sx={{ mr: 2 }}
											to={`/movies/${movie.id}/details`}>
											<Tooltip title="View movie details" arrow>
												<ReadMoreIcon color="primary" />
											</Tooltip>
										</IconButton>

										<IconButton component={Link} sx={{ mr: 2 }} to={`/movies/${movie.id}/edit`}>
											<EditIcon />
										</IconButton>

										<IconButton component={Link} sx={{ mr: 2 }} to={`/movies/${movie.id}/delete`}>
											<DeleteForeverIcon sx={{ color: "red" }} />
										</IconButton>
									</TableCell>
								</TableRow>
							))}
						</TableBody>
					</Table>
				</TableContainer>
			)}
			<ReactPaginate
			previousLabel={'previous'}
			nextLabel={'next'}
			pageCount={pageCount}
			onPageChange={handlePageClick}
			containerClassName={'pagination'}
			activeClassName={'active'}
			/>
			<form onSubmit={(e) => {e.preventDefault()}}>
						<TextField
							id="page_size"
							label="Page Size"
							variant="outlined"
							sx={{ mb: 2 }}
							onChange={handleChange}
						/>
						<Button type="submit">Change Page Size</Button>

			</form>
		</Container>
	);
};

// 	useEffect(() => {
// 		fetch(`${BACKEND_API_URL}/directors`)
// 			.then((response) => response.json())
// 			.then((data) => {
// 				setDirectors(data);
// 			});
// 	}, []);

// 	const [movies, setMovies] = useState<Movie[]>([]);
// 	const [loading, setLoading] = useState(false);

// 	useEffect(() => {
//         setLoading(true);
// 		fetch(`${BACKEND_API_URL}/movies`)
// 			.then((response) => response.json())
// 			.then((data) => {
// 				setMovies(data);
// 				setLoading(false);
// 			});
// 	}, []);

//     const getDirectorById = (id: number) => {
// 		return directors.find((director) => director.id === id) || directors[0];
// 	};
