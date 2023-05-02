import { Card, CardActions, CardContent, IconButton } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import { BACKEND_API_URL } from "../constants";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import AddIcon from "@mui/icons-material/Add";
import ViewCarouselIcon from '@mui/icons-material/ViewCarousel';
import { Movie } from "../models/Movie";
import { Director } from "../models/Director";
import axios from 'axios';
import { Actor } from "../models/Actor";

export const ActorDetails = () => {
	const { actorId } = useParams();

	const [actor, setActor] = useState<Actor>();

	useEffect(() => {
		const fetchActor = async () => {
			const response = await fetch(`${BACKEND_API_URL}actors/${actorId}/`);
			const actor = await response.json();
            console.log(actor);
			setActor(actor);
		};
		fetchActor();
	}, [actorId]);

	return (
		<Container>
			<Card>
				<CardContent>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/actors/`}>
						<ArrowBackIcon />
					</IconButton>{" "}
					<h1>Actor Details</h1>
					<p>Actor name: {actor?.actor_name}</p>
					<p>Birth Date: {actor?.birth_date}</p>
					<p>Star Sign: {actor?.star_sign}</p>
					<p>Contact: {actor?.contact}</p>
                    <p>Votes: {actor?.votes}</p>
				</CardContent>
				<CardActions>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/actors/${actorId}/edit`}>
						<EditIcon />
					</IconButton>

					<IconButton component={Link} sx={{ mr: 3 }} to={`/actors/${actorId}/delete`}>
						<DeleteForeverIcon sx={{ color: "red" }} />
					</IconButton>

					<IconButton component={Link} sx={{ mr: 3 }} to={`/actors/${actorId}/add`}>
						<AddIcon />
					</IconButton>
					
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/actors/${actorId}/movies`}>
						<ViewCarouselIcon />
					</IconButton>
				</CardActions>
			</Card>
		</Container>
	);
};