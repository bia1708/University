from django.test import TestCase, RequestFactory
from django.http import HttpRequest
from movies.models import *
from movies.statistics import *
from movies.serializer import DirectorsWithBestMoviesSerializer, DirectorsWithNewestMoviesSerializer
# Create your tests here.

class MovieTestCase(TestCase):
    def setUp(self):
        Director.objects.create(director_name="Christopher Nolan", birth_date="1970-07-30", star_sign="Leo", contact="contact@contact.com", votes=5000)
        Director.objects.create(director_name="Steven Spielberg", birth_date="1946-12-18", star_sign="Saggitarius", contact="contact@contact.com", votes=8000)
        Director.objects.create(director_name="Spike Lee", birth_date="1957-03-20", star_sign="Pisces", contact="contact@contact.com", votes=4500)
        Director.objects.create(director_name="misc", birth_date="1957-03-20", star_sign="Pisces", contact="contact@contact.com", votes=4500)


        Movie.objects.create(movie_text="Inception", release_date=2010, imdb_score=8.8, votes=218, director_id=1)
        Movie.objects.create(movie_text="The Dark Knight", release_date=2008, imdb_score=9.0, votes=220, director_id=1)
        Movie.objects.create(movie_text="Jaws", release_date=1975, imdb_score=8.0, votes=537, director_id=2)
        Movie.objects.create(movie_text="Schindler's List", release_date=1993, imdb_score=8.9, votes=122, director_id=2)
        Movie.objects.create(movie_text="Raiders of the Lost Ark", release_date=1981, imdb_score=8.4, votes=870, director_id=2)
        Movie.objects.create(movie_text="Do the Right Thing", release_date=1989, imdb_score=7.9, votes=694, director_id=3)


    def test_statistic_1(self):
        """Get directors with best movies (order descending by imdb rating avg across all movies)"""

        # Instantiate the view
        request = HttpRequest()
        request.method = 'GET'
        request.path = '/'
        view = GetDirectorsWithBestMovies.as_view()

        # Call the view with an empty request
        response = view(request)

        # Check the response status code
        self.assertEqual(response.status_code, 200)

        # Check that the response contains the correct number of directors
        self.assertEqual(len(response.data), 4)

        # Check that the response is ordered by avg_rating
        self.assertEqual(response.data[0]['director_name'], "Christopher Nolan")
        self.assertEqual(response.data[1]['director_name'], "Steven Spielberg")
        self.assertEqual(response.data[2]['director_name'], "Spike Lee")
        self.assertEqual(response.data[3]['director_name'], "misc")


        self.assertEqual(response.data[0]['avg_score'], 8.9)
        self.assertEqual(response.data[1]['avg_score'], 8.433333333333332)
        self.assertEqual(response.data[2]['avg_score'], 7.9)
        self.assertEqual(response.data[3]['avg_score'], None)



    def test_statistic_2(self):
        """Get directors with newest movies (order descending by release date avg across all movies)"""

        # Instantiate the view
        request = HttpRequest()
        request.method = 'GET'
        request.path = '/'
        view = GetDirectorsWithNewestMovies.as_view()

        # Call the view with an empty request
        response = view(request)

        # Check the response status code
        self.assertEqual(response.status_code, 200)

        # Check that the response contains the correct number of directors
        self.assertEqual(len(response.data), 3)

        # Check that the response is ordered by avg_rating
        self.assertEqual(response.data[0]['director_name'], "Christopher Nolan")
        self.assertEqual(response.data[1]['director_name'], "Spike Lee")
        self.assertEqual(response.data[2]['director_name'], "Steven Spielberg")

        self.assertEqual(response.data[0]['avg_release_date'], 2009.0)
        self.assertEqual(response.data[1]['avg_release_date'], 1989.0)
        self.assertEqual(response.data[2]['avg_release_date'], 1983.0)
