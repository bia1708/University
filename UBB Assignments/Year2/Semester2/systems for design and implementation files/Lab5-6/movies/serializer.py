from django.db.models import Avg
from rest_framework import serializers
from movies.models import *
from django.db import connection


class DirectorSerializer(serializers.ModelSerializer):
    no_movies = serializers.SerializerMethodField("get_no_movies")

    def get_no_movies(self, obj: Director):
        movies = Movie.objects.filter(director_id=obj.id)
        return movies.count()

    def validate_votes(self, value):
        if value < 0:
            raise serializers.ValidationError('Vote count cannot be negative.')
        else:
            return value

    def validate_star_sign(self, value):
        stars = ['taurus', 'pisces', 'leo', 'gemini', 'aquarius', 'libra', 'scorpio', 'sagittarius', 'aries', 'cancer',
                 'capricorn', 'virgo']
        if value not in stars:
            raise serializers.ValidationError(f"{value} is not a star sign!")
        return value

    class Meta:
        model = Director
        fields = ('id', 'director_name', 'birth_date', 'star_sign', 'contact', 'votes', 'no_movies')


class MovieSerializer(serializers.ModelSerializer):
    director_id = serializers.IntegerField(write_only=True)
    director = DirectorSerializer(read_only=True)

    actors_count = serializers.SerializerMethodField("get_actors_count")

    def get_actors_count(self, obj):
        result = 0
        with connection.cursor() as cursor:
            cursor.execute(f"SELECT COUNT(*) FROM movies_ActorMovie WHERE movie_id = {obj.id};")
            result = cursor.fetchall()[0][0]
        return result

    def validate_director_id(self, value):
        filter = Director.objects.filter(id=value)
        if not filter.exists():
            raise serializers.ValidationError(f"Director with id {value} does not exist")
        return value

    class Meta:
        model = Movie
        fields = ('id', 'movie_text', 'release_date', 'director', 'director_id', 'imdb_score', 'votes', 'actors_count')


class ActorSerializer(serializers.ModelSerializer):
    # movies = serializers.SerializerMethodField("get_movies")
    movie_count = serializers.SerializerMethodField("get_movie_count")

    def get_movie_count(self, obj):
        result = 0
        with connection.cursor() as cursor:
            cursor.execute(f"SELECT COUNT(*) FROM movies_ActorMovie WHERE actor_id = {obj.id};")
            result = cursor.fetchall()[0][0]
        return result

    def validate_votes(self, value):
        if value < 0:
            raise serializers.ValidationError('Vote count cannot be negative.')
        else:
            return value

    def validate_star_sign(self, value):
        stars = ['taurus', 'pisces', 'leo', 'gemini', 'aquarius', 'libra', 'scorpio', 'sagittarius', 'aries', 'cancer',
                 'capricorn', 'virgo']
        if value not in stars:
            raise serializers.ValidationError(f"{value} is not a star sign!")
        return value

    def get_movies(self, obj):
        movies = Movie.objects.all()
        am = ActorMovie.objects.filter(actor_id=obj.id)
        result = []
        for m in movies:
            if am.filter(movie_id=m.id).exists():
                result.append([MovieSerializer(m).data])
        return result

    class Meta:
        model = Actor
        fields = ('id', 'actor_name', 'birth_date', 'star_sign', 'contact', 'votes', 'movie_count')


class DirectorWithMoviesSerializer(serializers.ModelSerializer):
    director_id = serializers.IntegerField(read_only=True)
    movie_id = serializers.IntegerField(read_only=True)
    movies = serializers.SerializerMethodField("get_movies")

    def get_movies(self, obj: Director):
        return [MovieSerializer(movie).data for movie in Movie.objects.all().filter(director_id=obj.id)]

    class Meta:
        model = Movie
        fields = ('director_id', 'movie_id', 'movies')


class ActorMovieSerializer(serializers.ModelSerializer):
    actor_id = serializers.IntegerField()
    movie_id = serializers.IntegerField(write_only=True)

    actor_payment = serializers.IntegerField()
    actor_awarded = serializers.BooleanField()

    movie = MovieSerializer(read_only=True)

    def validate_actor_payment(self, value):
        if value < 0:
            raise serializers.ValidationError('Actor payment cannot be negative.')
        else:
            return value

    def validate_actor_id(self, data):
        actor_id = self.context['view'].kwargs['pk']
        if actor_id is not None and data != actor_id:
            raise serializers.ValidationError('Actor ID does not match URL')
        return data

    def validate_movie_id(self, value):
        filter = Movie.objects.filter(id=value)
        if not filter.exists():
            raise serializers.ValidationError(f"Movie with id {value} does not exist")
        return value

    class Meta:
        model = ActorMovie
        fields = ('actor_id', 'actor_payment', 'actor_awarded', 'movie_id', 'movie')


class DirectorsWithBestMoviesSerializer(serializers.ModelSerializer):
    avg_score = serializers.SerializerMethodField("get_avg")

    def get_avg(self, obj: Director):
        avg = 0
        movies = Movie.objects.all().filter(director_id=obj.id)
        if len(movies) == 0:
            return None
        for movie in movies:
            avg += movie.imdb_score
        return avg / len(movies.values())

    class Meta:
        model = Director
        fields = '__all__'


class DirectorsWithNewestMoviesSerializer(serializers.ModelSerializer):
    avg_release_date = serializers.SerializerMethodField("get_avg_release_date")

    def get_avg_release_date(self, obj: Director):
        avg = 0
        movies = Movie.objects.all().filter(director_id=obj.id)
        if len(movies) == 0:
            return 0
        for movie in movies:
            avg += movie.release_date
        return avg / len(movies.values())

    class Meta:
        model = Director
        fields = '__all__'
