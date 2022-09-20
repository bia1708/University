from src.services.services import MovieService, ClientService, RentalService
from src.settings import Properties
from src.ui.console import Console

file_type = 'bin'
movie_validator, client_validator, rental_validator = Properties(file_type).validator_settings()
movie_repo, client_repo, rental_repo = Properties(file_type).repository_settings()

# SERVICES:
movie_service = MovieService(movie_repo, movie_validator)
client_service = ClientService(client_repo, client_validator)
rental_service = RentalService(rental_repo, client_repo, movie_repo, rental_validator)

# CONSOLE:
console = Console(movie_service, client_service, rental_service)
if file_type != 'txt':
    console.populate()
console.startup()
