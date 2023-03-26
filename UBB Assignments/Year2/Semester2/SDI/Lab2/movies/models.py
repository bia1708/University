from django.db import models

# Create your models here.

class Director(models.Model):
    director_name = models.CharField(max_length=200)
    birth_date = models.DateField()
    star_sign = models.CharField(max_length=100)
    contact = models.EmailField()
    votes = models.IntegerField(default=0)

    def __str__(self):
        return self.director_name


class Movie(models.Model):
    movie_text = models.CharField(max_length=200)
    release_date = models.IntegerField(default=2023)
    director = models.ForeignKey(Director, on_delete=models.CASCADE)
    imdb_score = models.FloatField(default=0.0)
    votes = models.IntegerField(default=0)

    def __str__(self):
        return self.movie_text


class Actor(models.Model):
    actor_name = models.CharField(max_length=200)
    birth_date = models.DateField()
    star_sign = models.CharField(max_length=100)
    contact = models.EmailField()
    votes = models.IntegerField(default=0)

    def __str__(self):
        return self.actor_name


class DirectorMovie(models.Model):
    director = models.ForeignKey(Director, on_delete=models.CASCADE)
    movie = models.ForeignKey(Movie, on_delete=models.CASCADE)
    release_date = models.IntegerField(default=0)

    def __str__(self):
        return f"{self.director.director_name} - {self.movie.movie_text}"
