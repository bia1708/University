from django.urls import path, include
from movies import views

urlpatterns = [
    path('movies/', views.MovieList.as_view()),
    path('movies/<int:pk>/', views.MovieDetail.as_view()),
    path('actors/', views.ActorList.as_view()),
    path('actors/<int:pk>/', views.ActorDetail.as_view()),
    path('directors/', views.DirectorList.as_view()),
    # path('directors_movies/<int:pk>/', views.DirectorDetail.as_view()),
    path('director_movies/', views.DirectorMovieView.as_view()),
    path('directors/<int:pk>/', views.MoviesWithDirector.as_view())
]
