from rest_framework import generics, mixins
from rest_framework.response import Response
from movies.models import  *
from movies.serializer import *


class GetDirectorsWithBestMovies(generics.ListAPIView):
    queryset = Director.objects.annotate(avg_rating=Avg('movie__imdb_score')) \
            .order_by('-avg_rating')
    serializer_class = DirectorsWithBestMoviesSerializer


class GetDirectorsWithNewestMovies(generics.ListAPIView):
    queryset = Director.objects.annotate(avg_release_date=Avg('movie__release_date')) \
            .order_by('-avg_release_date').filter(avg_release_date__gt=0)
    serializer_class = DirectorsWithNewestMoviesSerializer
