from django.shortcuts import render, get_object_or_404
from django.http import HttpResponseRedirect
from django.urls import reverse

from .models import Movie

# Create your views here.


def index(request):
    movies_list = Movie.objects.order_by('votes')[:5]
    context = {
        'movies_list': movies_list,
    }
    return render(request, 'index.html', context)


def detail(request, movie_id):
    movie = get_object_or_404(Movie, pk=movie_id)
    return render(request, 'detail.html', {'movie': movie})


def results(request, movie_id):
    movie = get_object_or_404(Movie, pk=movie_id)
    return render(request, 'results.html', {'movie': movie})


def vote(request, movie_id):
    movie = get_object_or_404(Movie, pk=movie_id)
    movie.votes += 1
    movie.save()
    # Always return an HttpResponseRedirect after successfully dealing
    # with POST data. This prevents data from being posted twice if a
    # user hits the Back button.
    return HttpResponseRedirect(reverse('movies:results', args=(movie.id,)))