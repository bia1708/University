import { Card, CardActions, CardContent, IconButton } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import { BACKEND_API_URL } from "../constants";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { Movie } from "../models/Movie";
import { Director } from "../models/Director";
import axios from 'axios';

export const DirectorDetails = () => {
	const { directorId } = useParams();

	const [director, setDirector] = useState<Director>();

	useEffect(() => {
		const fetchDirector = async () => {
			const response = await fetch(`${BACKEND_API_URL}directors/${directorId}/`);
			const director = await response.json();
            console.log(director);
			setDirector(director);
		};
		fetchDirector();
	}, [directorId]);

	return (
		<Container>
			<Card>
				<CardContent>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/directors/`}>
						<ArrowBackIcon />
					</IconButton>{" "}
					<h1>Director Details</h1>
					<p>Director name: {director?.director_name}</p>
					<p>Birth Date: {director?.birth_date}</p>
					<p>Star Sign: {director?.star_sign}</p>
					<p>Contact: {director?.contact}</p>
                    <p>Votes: {director?.votes}</p>
				</CardContent>
				<CardActions>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/directors/${directorId}/edit`}>
						<EditIcon />
					</IconButton>

					<IconButton component={Link} sx={{ mr: 3 }} to={`/directors/${directorId}/delete`}>
						<DeleteForeverIcon sx={{ color: "red" }} />
					</IconButton>
				</CardActions>
			</Card>
		</Container>
	);
};