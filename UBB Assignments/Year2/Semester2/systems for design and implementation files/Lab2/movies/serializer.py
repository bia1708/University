from rest_framework import serializers
from movies.models import *


class DirectorSerializer(serializers.ModelSerializer):
    class Meta:
        model = Director
        fields = '__all__'


class MovieSerializer(serializers.ModelSerializer):
    director_id = serializers.IntegerField(write_only=True)
    director = DirectorSerializer(read_only=True)

    def validate_director_id(self, value):
        filter = Director.objects.filter(id=value)
        if not filter.exists():
            raise serializers.ValidationError(f"Director with id {value} does not exist")
        return value

    class Meta:
        model = Movie
        fields = ('id', 'movie_text', 'release_date', 'director', 'director_id', 'imdb_score', 'votes')


class DirectorWithMoviesSerializer(serializers.ModelSerializer):
    director_id = serializers.IntegerField(read_only=True)
    movie_id = serializers.IntegerField(read_only=True)
    movies = serializers.SerializerMethodField("get_movies")

    def get_movies(self, obj:Director):
        return [MovieSerializer(movie).data for movie in Movie.objects.all().filter(director_id=obj.id)]

    class Meta:
        model = Movie
        fields = ('director_id', 'movie_id', 'movies')


class ActorSerializer(serializers.ModelSerializer):
    class Meta:
        model = Actor
        fields = '__all__'


class DirectorMovieSerializer(serializers.ModelSerializer):
    director_id = serializers.IntegerField(write_only=True)
    movie_id = serializers.IntegerField(write_only=True)
    movie = MovieSerializer(read_only=True)

    def validate_director_id(self, value):
        filter = Director.objects.filter(id=value)
        if not filter.exists():
            raise serializers.ValidationError(f"Director with id {value} does not exist")
        return value

    def validate_movie_id(self, value):
        filter = Movie.objects.filter(id=value)
        if not filter.exists():
            raise serializers.ValidationError(f"Movie with id {value} does not exist")
        return value

    class Meta:
        model = DirectorMovie
        fields = ('director_id', 'movie_id', 'movie')