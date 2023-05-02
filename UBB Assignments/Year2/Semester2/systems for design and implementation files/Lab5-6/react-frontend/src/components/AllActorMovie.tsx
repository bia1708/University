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
} from "@mui/material";
import React from "react";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
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
import { ActorMovie } from "../models/ActorMovie";
import { Actor } from "../models/Actor";

export const ActorMovies = () => {
	// const [directors, setDirectors] = useState<Director[]>([]);
    const { actorId } = useParams();
    const [actor, setActor] = useState<Actor>();
	const [actor_movies, setMovies] = useState<ActorMovie[]>([]);
	const [loading, setLoading] = useState(false);
	const [pageCount, setPageCount] = useState(0);
  	const [currentPage, setCurrentPage] = useState(0);

	const fetchData = async () => {
		setLoading(true);
		const response = await axios.get(`${BACKEND_API_URL}actors/${actorId}/movies?page=${currentPage + 1}`);
		setMovies(response.data.results);

        const response_actor = await axios.get(`${BACKEND_API_URL}actors/${actorId}/`);
        setActor(response_actor.data);
        console.log(actor);

		setPageCount(response.data.page_count);
		setLoading(false);
		console.log("Page count:", pageCount);
	};

	const handlePageClick = (selectedPage: { selected: React.SetStateAction<number>; }) => {
		console.log(currentPage);
		setCurrentPage(selectedPage.selected);
	};

	useEffect(() => {
		fetchData();
	}, [currentPage]);

	return (
		<Container>
			<h1>{actor?.actor_name}</h1>

			{loading && <CircularProgress />}
			{!loading && actor_movies.length === 0 && <p>No movies found</p>}
			{!loading && (
				<IconButton component={Link} sx={{ mr: 3 }} to={`/actors/${actorId}/add`}>
					<Tooltip title="Add a new movie to actor" arrow>
						<AddIcon color="primary" />
					</Tooltip>
				</IconButton>
			)}
			{/* {!loading && (
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
			)} */}
			{actor_movies.length > 0 && (
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
								<TableCell align="center">Actor Payment</TableCell>
								<TableCell align="center">Actor Awarded</TableCell>
								<TableCell align="center">Actions</TableCell>

							</TableRow>
						</TableHead>
						<TableBody>
							{actor_movies.map((am, index) => (
								<TableRow key={am.id}>
									<TableCell component="th" scope="row">
										{index + 1}
									</TableCell>
									<TableCell component="th" scope="row">
										<Link to={`/movies/${am.id}/details`} title="View movie details">
											{am.movie?.movie_text}
										</Link>
									</TableCell>
									<TableCell align="right">{am.movie?.release_date}</TableCell>
									<TableCell align="right">{am.movie?.director?.director_name}</TableCell>
                                    <TableCell align="right">{am.movie?.imdb_score}</TableCell>
                                    <TableCell align="right">{am.movie?.votes}</TableCell>
                                    <TableCell align="right">{am.movie?.actors_count}</TableCell>
                                    <TableCell align="right">{am.actor_payment}</TableCell>
                                    <TableCell align="right">{am.actor_awarded.toString()}</TableCell>

									<TableCell align="right">
										<IconButton
											component={Link}
											sx={{ mr: 3 }}
											to={`/movies/${am.id}/details`}>
											<Tooltip title="View movie details" arrow>
												<ReadMoreIcon color="primary" />
											</Tooltip>
										</IconButton>

										<IconButton component={Link} sx={{ mr: 3 }} to={`/movies/${am.id}/edit`}>
											<EditIcon />
										</IconButton>

										<IconButton component={Link} sx={{ mr: 3 }} to={`/movies/${am.id}/delete`}>
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
