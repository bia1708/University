from django.urls import path, include
from movies import views, statistics

urlpatterns = [
    path('movies/', views.MovieList.as_view()),
    path('movies/<int:page>', views.MovieList.as_view()),
    path('movies/<int:pk>/', views.MovieDetail.as_view()),
    path('actors/', views.ActorList.as_view()),
    path('actors/<int:pk>/', views.ActorDetail.as_view()),
    path('actors/<int:pk>/movies/', views.ActorMovieAddView.as_view()),
    path('directors/', views.DirectorList.as_view()),
    path('directors/<int:pk>/', views.DirectorDetail.as_view()),
    # path('actors_movies/', views.ActorMovieAddView.as_view()),
    # path('actors_movies/<int:pk>/', views.ActorMovieView.as_view()),
    path('directors_movies/<int:pk>/', views.MoviesWithDirector.as_view()),
    path('stat/1/', statistics.GetDirectorsWithBestMovies.as_view()),
    path('stat/2/', statistics.GetDirectorsWithNewestMovies.as_view())
]
