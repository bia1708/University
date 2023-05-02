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

export const ActorAdd = () => {
    const star_signs = ['taurus', 'pisces', 'leo', 'gemini', 'aquarius', 'libra', 'scorpio', 'sagittarius', 'aries', 'cancer',
    'capricorn', 'virgo'];

	const navigate = useNavigate();

	const [actor, setActor] = useState<Actor>({
		actor_name: "",
		birth_date: "",
        star_sign: "",
		contact: "",
		votes: 0,
	});

	const addActor = async (event: React.FormEvent<HTMLFormElement>) => {
		event.preventDefault();
		try {
			// await axios.post(`${BACKEND_API_URL}/movies`, movie);
			const response = await fetch(`${BACKEND_API_URL}actors/`, {
				method: "POST",
				headers: { "Content-Type": "application/json" },
				body: JSON.stringify(actor),
			  });
			navigate("/actors/");
		} catch (error) {
			console.log(error);
		}
	};

    const [error, setError] = useState('');

	const handleChange = (event: { target: { value: string; }; }) => {
		const newValue = event.target.value;

		// Validate input value
		if (isNaN(parseInt(newValue)) || Number(newValue) < 0) {
		  setError('Please enter a positive number');
		} else {
		  setError('');
		}
		setActor({ ...actor, votes: parseInt(event.target.value) })
	};


	return (
		<Container>
			<Card>
				<CardContent>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/actors`}>
						<ArrowBackIcon />
					</IconButton>{" "}
					<form onSubmit={addActor}>
						<TextField
							id="name"
							label="Actor Name"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event) => setActor({ ...actor, actor_name: event.target.value })}
						/>
						<TextField
							id="birth_date"
							label="Birth Date"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event) => setActor({ ...actor, birth_date: event.target.value })}
						/>
						<TextField
							id="star_sign"
							label="Star Sign"
							variant="outlined"
							name="director"
							fullWidth
							sx={{ mb: 2 }}
							select
							// value={movie.director.id}
							onChange={(event) => setActor({ ...actor, star_sign: event.target.value })} // setMovie({ ...movie, director: getDirectorById(parseInt(event.target.value)) })}
                        >
                            {star_signs.map((star) => (
                                <MenuItem key={star} value={star}>
                                {star}
                                </MenuItem>
                            ))}
        				</TextField>
						<TextField
							id="contact"
							label="Contact"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={(event) => setActor({ ...actor, contact: event.target.value })}
						/>
						<TextField
							id="votes"
							label="Votes"
							variant="outlined"
							fullWidth
							sx={{ mb: 2 }}
							onChange={handleChange}
							// onChange={(event) => setActor({ ...actor, votes: parseInt(event.target.value) })}
						/>
                        {error && <div style={{ color: 'red' }}>{error}</div>}

						<Button type="submit">Add Actor</Button>
					</form>
				</CardContent>
				<CardActions></CardActions>
			</Card>
		</Container>
	);
};