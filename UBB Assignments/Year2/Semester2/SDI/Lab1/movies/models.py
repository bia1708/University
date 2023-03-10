from django.db import models

# Create your models here.

class Movie(models.Model):
    movie_text = models.CharField(max_length=200)
    release_date = models.IntegerField(default=2023)
    director = models.CharField(max_length=200)
    imdb_score = models.FloatField(default=0.0)
    votes = models.IntegerField(default=0)

    def __str__(self):
        return self.movie_text

