import { useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import './App.css'
import React from 'react'
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import { AppMenu } from './components/AppMenu'
import { MovieDetails } from './components/MovieDetails'
import { MovieAdd } from './components/MovieAdd'
import { AllMovies } from './components/AllMovies'
import { FilterMovies } from './components/FilterMovies'
import { MovieDelete } from './components/MovieDelete'
import { MovieEdit } from './components/MovieEdit'
import { SortMovies } from './components/MoviesSort'
import { AllDirectors } from './components/AllDirectors'
import { AllActors } from './components/AllActors'
import { DirectorAdd } from './components/DirectorAdd'
import { DirectorDetails } from './components/DirectorDetail'
import { ActorAdd } from './components/ActorAdd'
import { ActorDetails } from './components/ActorDetails'
import { ActorMovies } from './components/AllActorMovie'
import { ActorMovieAdd } from './components/ActorMovieAdd'
import { DirectorDelete } from './components/DirectorDelete'
import { ActorDelete } from './components/ActorDelete'



function App() {
  const [count, setCount] = useState(0)

  return (
		<React.Fragment>
			<Router>
				<AppMenu />

				<Routes>
					{/* <Route path="/" element={<AppHome />} /> */}
					<Route path="/movies/" element={<AllMovies />} />
					<Route path="/movies/:movieId/details" element={<MovieDetails />} />
					<Route path="/movies/:movieId/edit" element={<MovieEdit />} />
					<Route path="/movies/:movieId/delete" element={<MovieDelete />} />
					<Route path="/movies/add" element={<MovieAdd />} />
					<Route path="/movies/filter" element={<FilterMovies />} />
					<Route path="/movies/sort" element={<SortMovies />} />

					<Route path="/directors/" element={<AllDirectors />} />
					<Route path="/directors/add" element={<DirectorAdd />} />
					<Route path="/directors/:directorId/delete" element={<DirectorDelete />} />
					<Route path="/directors/:directorId/details" element={<DirectorDetails />} />

					<Route path="/actors/" element={<AllActors />} />
					<Route path="/actors/add" element={<ActorAdd />} />
					<Route path="/actors/:actorId/details" element={<ActorDetails />} />
					<Route path="/actors/:actorId/add" element={<ActorMovieAdd />} />
					<Route path="/actors/:actorId/delete" element={<ActorDelete />} />
					<Route path="/actors/:actorId/movies" element={<ActorMovies />} />


				</Routes>
			</Router>
		</React.Fragment>
	);
}

export default App
