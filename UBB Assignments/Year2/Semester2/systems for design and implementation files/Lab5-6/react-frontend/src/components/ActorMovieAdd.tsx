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
import axios from "axios";
import { Actor } from "../models/Actor";
import { ActorMovie } from "../models/ActorMovie";

export const ActorMovieAdd = () => {
    const star_signs = ['taurus', 'pisces', 'leo', 'gemini', 'aquarius', 'libra', 'scorpio', 'sagittarius', 'aries', 'cancer',
    'capricorn', 'virgo'];

	const navigate = useNavigate();
    const { actorId } = useParams();

	const [actor_movie, setActorMovie] = useState<ActorMovie>({
        actor_id: parseInt(actorId ?? '0'),
		actor_payment: 0,
        actor_awarded: false,
        movie_id: 0,
	});

	const addActorMovie = async (event: React.FormEvent<HTMLFormElement>) => {
		event.preventDefault();
		try {
            console.log(actor_movie);
			const response = await fetch(`${BACKEND_API_URL}actors/${actorId}/movies/`, {
				method: "POST",
				headers: { "Content-Type": "application/json" },
				body: JSON.stringify(actor_movie),
			  });
			navigate("${BACKEND_API_URL}actors/");
		} catch (error) {
			console.log(error);
		}
	};

    const bools = ['true', 'false'];

    const [error, setError] = useState('');

	const handleChange = (event: { target: { value: string; }; }) => {
		const newValue = event.target.value;

		// Validate input value
		if (isNaN(parseInt(newValue)) || Number(newValue) < 0) {
		  setError('Please enter a positive number');
		} else {
		  setError('');
		}
        setActorMovie({ ...actor_movie, actor_payment: parseInt(event.target.value) })
    };

	return (
		<Container>
			<Card>
				<CardContent>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/actors`}>
						<ArrowBackIcon />
					</IconButton>{" "}
					<form onSubmit={addActorMovie}>
						<TextField
							id="payment"
							label="Actor Payment"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
                            onChange={handleChange}
							// onChange={(event) => setActorMovie({ ...actor_movie, actor_payment: parseInt(event.target.value) })}
						/>
						<TextField
							id="actor_awarded"
							label="The Actor was Awarded"
							variant="outlined"
							fullWidth
                            select
							sx={{ mb: 2 }}
							onChange={(event) => setActorMovie({ ...actor_movie, actor_awarded: Boolean(event.target.value) })}
						>
                            {bools.map((bool) => (
                                <MenuItem key={bool} value={bool}>
                                {bool}
                                </MenuItem>
                            ))}
                        </TextField>
						<TextField
							id="movie_id"
							label="Movie"
							variant="outlined"
							name="director"
							fullWidth
							sx={{ mb: 2 }}
							// value={movie.director.id}
							onChange={(event) => setActorMovie({ ...actor_movie, movie_id: parseInt(event.target.value) })} // setMovie({ ...movie, director: getDirectorById(parseInt(event.target.value)) })}
                        >
        				</TextField>
                        {error && <div style={{ color: 'red' }}>{error}</div>}

						<Button type="submit">Add ActorMovie</Button>
					</form>
				</CardContent>
				<CardActions></CardActions>
			</Card>
		</Container>
	);
};