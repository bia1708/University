from src.services.services import MovieService, ClientService, RentalService
from src.repository.repo import Repository
from src.domain.validators import MovieValidator, ClientValidator, RentalValidator
from ui.console import Console

# VALIDATORS:
movie_validator = MovieValidator()
client_validator = ClientValidator()
rental_validator = RentalValidator()

# REPOS:
movie_repo = Repository(movie_validator)
client_repo = Repository(client_validator)
rental_repo = Repository(rental_validator)

# SERVICES:
movie_service = MovieService(movie_repo)
client_service = ClientService(client_repo)
rental_service = RentalService(rental_repo, client_repo, movie_repo)

# CONSOLE:
console = Console(movie_service, client_service, rental_service)
console.startup()
