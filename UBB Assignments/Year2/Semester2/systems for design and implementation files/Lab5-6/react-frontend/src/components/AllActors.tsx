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
import { Actor } from "../models/Actor";

export const AllActors = () => {
	const [actors, setActors] = useState<Actor[]>([]);
	// const [movies, setMovies] = useState<Movie[]>([]);
	const [loading, setLoading] = useState(false);
	const [pageCount, setPageCount] = useState(0);
  	const [currentPage, setCurrentPage] = useState(0);

	const fetchData = async () => {
		setLoading(true);
		console.log(pageSize);
		const url = `${BACKEND_API_URL}actors?page=${currentPage + 1}&page_size=${pageSize}`;
		const response = await axios.get(url);
		console.log(response.data.results.length, url);
		setActors(response.data.results);
		setPageCount(response.data.page_count);
		setLoading(false);
	};

	const [pageSize, setPageSize] = useState(10);

	const handlePageClick = (selectedPage: { selected: React.SetStateAction<number>; }) => {
		console.log(currentPage);
		setCurrentPage(selectedPage.selected);
	};

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
			<h1>Actor List</h1>

			{loading && <CircularProgress />}
			{!loading && actors.length === 0 && <p>No actors found</p>}
			{!loading && (
				<IconButton component={Link} sx={{ mr: 3 }} to={`/actors/add`}>
					<Tooltip title="Add a new actor" arrow>
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
			{actors.length > 0 && (
				<TableContainer component={Paper}>
					<Table sx={{ minWidth: 650 }} aria-label="simple table">
						<TableHead>
							<TableRow>
								<TableCell>#</TableCell>
								<TableCell align="right">Name</TableCell>
								<TableCell align="right">Birth Date</TableCell>
								<TableCell align="right">Star Sign</TableCell>
								<TableCell align="center">Contact</TableCell>
                                <TableCell align="center">Votes</TableCell>
								<TableCell align="center">No. of Movies</TableCell>
								<TableCell align="center">Actions</TableCell>

							</TableRow>
						</TableHead>
						<TableBody>
							{actors.map((actor, index) => (
								<TableRow key={actor.id}>
									<TableCell component="th" scope="row">
										{index + 1}
									</TableCell>
									<TableCell component="th" scope="row">
										<Link to={`/actors/${actor.id}/details`} title="View actor details">
											{actor.actor_name}
										</Link>
									</TableCell>
									<TableCell align="right">{actor.birth_date}</TableCell>
									<TableCell align="right">{actor.star_sign}</TableCell>
                                    <TableCell align="right">{actor.contact}</TableCell>
                                    <TableCell align="right">{actor.votes}</TableCell>
                                    <TableCell align="right">{actor.movie_count}</TableCell>

									<TableCell align="right">
										<IconButton
											component={Link}
											sx={{ mr: 3 }}
											to={`/actors/${actor.id}/details`}>
											<Tooltip title="View actor details" arrow>
												<ReadMoreIcon color="primary" />
											</Tooltip>
										</IconButton>

										<IconButton component={Link} sx={{ mr: 3 }} to={`/actors/${actor.id}/edit`}>
											<EditIcon />
										</IconButton>

										<IconButton component={Link} sx={{ mr: 3 }} to={`/actors/${actor.id}/delete`}>
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
