from django.urls import path

from . import views

app_name = 'movies'
urlpatterns = [
    path('', views.index, name='index'),
    path('<int:movie_id>/', views.detail, name='detail'),
    path('<int:movie_id>/results/', views.results, name='results'),
    path('<int:movie_id>/vote/', views.vote, name='vote'),
]