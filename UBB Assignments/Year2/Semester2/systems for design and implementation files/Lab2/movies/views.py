from rest_framework import generics
from rest_framework.response import Response
from movies.models import  *
from movies.serializer import *

class MovieList(generics.ListCreateAPIView):
    queryset = Movie.objects.all()
    serializer_class = MovieSerializer


class MovieDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Movie.objects.all()
    serializer_class = MovieSerializer


class DirectorList(generics.ListCreateAPIView):
    queryset = Director.objects.all()
    serializer_class = DirectorSerializer


class DirectorDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Director.objects.all()
    serializer_class = DirectorSerializer


class ActorList(generics.ListCreateAPIView):
    queryset = Actor.objects.all()
    serializer_class = ActorSerializer


class ActorDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Actor.objects.all()
    serializer_class = ActorSerializer


class DirectorMovieView(generics.CreateAPIView):
    serializer_class = DirectorMovieSerializer


class MoviesWithDirector(generics.RetrieveUpdateDestroyAPIView):
    queryset = Director.objects.all()
    serializer_class = DirectorWithMoviesSerializer
