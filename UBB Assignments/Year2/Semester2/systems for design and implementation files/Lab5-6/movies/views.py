from rest_framework import generics, mixins
from rest_framework.response import Response
from movies.models import  *
from movies.serializer import *
from rest_framework.pagination import PageNumberPagination


class Pagination(PageNumberPagination):
    page_size = 10
    page_size_query_param = 'page_size'
    max_page_size = 100


class MovieList(generics.ListCreateAPIView):
    queryset = Movie.objects.all()
    serializer_class = MovieSerializer
    # pagination_class = Pagination

    def get(self, request):
        page = request.GET.get('page', 1)
        # page_size = 10
        page_size = int(request.GET.get('page_size', 10))
        start_index = (int(page) - 1) * page_size
        end_index = int(page) * page_size

        movies = Movie.objects.all().order_by('id')[start_index:end_index]
        serializer = MovieSerializer(movies, many=True)

        # get total number of directors
        total_movies = Movie.objects.count()

        # calculate total number of pages
        page_count = int(total_movies / page_size)
        if total_movies % page_size > 0:
            page_count += 1

        # construct response data
        response_data = {
            'results': serializer.data,
            'page': int(page),
            'page_count': page_count
        }

        return Response(response_data)

    # def list(self, request, *args, **kwargs):
    #     queryset = self.filter_queryset(self.get_queryset())
    #     page = self.paginate_queryset(queryset)
    #     if page is not None:
    #         serializer = self.get_serializer(page, many=True)
    #         # calculate the total number of pages based on the page size
    #         total_pages = queryset.count() // self.paginator.page_size + 1
    #         return self.get_paginated_response(serializer.data, total_pages)
    #
    #     serializer = self.get_serializer(queryset, many=True)
    #     return Response(serializer.data)
    #
    # def get_paginated_response(self, data, total_pages):
    #     return Response({
    #         'results': data,
    #         'page_count': total_pages
    #     })


class MovieDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Movie.objects.all()
    serializer_class = MovieSerializer


class DirectorList(generics.ListCreateAPIView):
    queryset = Director.objects.all().order_by('id')
    serializer_class = DirectorSerializer
    # pagination_class = Pagination

    def get(self, request):
        page = request.GET.get('page', 1)
        page_size = 10
        start_index = (int(page) - 1) * page_size
        end_index = int(page) * page_size

        directors = Director.objects.all().order_by('id')[start_index:end_index]
        serializer = DirectorSerializer(directors, many=True)

        # get total number of directors
        total_directors = Director.objects.count()

        # calculate total number of pages
        page_count = int(total_directors / page_size)
        if total_directors % page_size > 0:
            page_count += 1

        # construct response data
        response_data = {
            'results': serializer.data,
            'page': int(page),
            'page_count': page_count
        }

        return Response(response_data)

    # def list(self, request, *args, **kwargs):
    #     queryset = self.filter_queryset(self.get_queryset())
    #     page = self.paginate_queryset(queryset)
    #     if page is not None:
    #         serializer = self.get_serializer(page, many=True)
    #         # calculate the total number of pages based on the page size
    #         total_pages = queryset.count() // self.paginator.page_size + 1
    #         return self.get_paginated_response(serializer.data, total_pages)
    #
    #     serializer = self.get_serializer(queryset, many=True)
    #     return Response(serializer.data)
    #
    # def get_paginated_response(self, data, total_pages):
    #     return Response({
    #         'results': data,
    #         'page_count': total_pages
    #     })


class DirectorDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Director.objects.all()
    serializer_class = DirectorSerializer


class ActorList(generics.ListCreateAPIView):
    queryset = Actor.objects.all()
    serializer_class = ActorSerializer
    # pagination_class = Pagination

    def get(self, request):
        page = request.GET.get('page', 1)
        page_size = int(request.GET.get('page_size', 10))
        start_index = (int(page) - 1) * page_size
        end_index = int(page) * page_size

        actors = Actor.objects.all().order_by('id')[start_index:end_index]
        serializer = ActorSerializer(actors, many=True)

        # get total number of directors
        total_actors = Actor.objects.count()

        # calculate total number of pages
        page_count = int(total_actors / page_size)
        if total_actors % page_size > 0:
            page_count += 1

        # construct response data
        response_data = {
            'results': serializer.data,
            'page': int(page),
            'page_count': page_count
        }

        return Response(response_data)

    # def list(self, request, *args, **kwargs):
    #     queryset = self.filter_queryset(self.get_queryset())
    #     page = self.paginate_queryset(queryset)
    #     if page is not None:
    #         serializer = self.get_serializer(page, many=True)
    #         # calculate the total number of pages based on the page size
    #         total_pages = queryset.count() // self.paginator.page_size + 1
    #         return self.get_paginated_response(serializer.data, total_pages)
    #
    #     serializer = self.get_serializer(queryset, many=True)
    #     return Response(serializer.data)
    #
    # def get_paginated_response(self, data, total_pages):
    #     return Response({
    #         'results': data,
    #         'page_count': total_pages
    #     })


class ActorDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Actor.objects.all()
    serializer_class = ActorSerializer


class MoviesWithDirector(generics.RetrieveUpdateDestroyAPIView):
    queryset = Director.objects.all()
    serializer_class = DirectorWithMoviesSerializer
    pagination_class = Pagination


class ActorMovieAddView(generics.ListCreateAPIView):
    queryset = ActorMovie.objects.all()
    serializer_class = ActorMovieSerializer
    # pagination_class = Pagination

    # def get_queryset(self):
    #     queryset = super().get_queryset()
    #     pk = self.kwargs.get('pk')
    #     if pk is not None:
    #         queryset = queryset.filter(actor_id=pk)
    #     return queryset

    def get(self, request, *args, **kwargs):
        page = request.GET.get('page', 1)
        page_size = int(request.GET.get('page_size', 10))
        start_index = (int(page) - 1) * page_size
        end_index = int(page) * page_size

        actor_movies = super().get_queryset()
        pk = self.kwargs.get('pk')
        if pk is not None:
            actor_movies = actor_movies.filter(actor_id=pk)

        # get total number of directors
        total_actor_movies = actor_movies.count()
        actor_movies = actor_movies[start_index:end_index]

        serializer = ActorMovieSerializer(actor_movies, many=True)

        # calculate total number of pages
        page_count = int(total_actor_movies / page_size)
        if total_actor_movies % page_size > 0:
            page_count += 1

        # construct response data
        response_data = {
            'results': serializer.data,
            'page': int(page),
            'page_count': page_count
        }

        return Response(response_data)

    # def list(self, request, *args, **kwargs):
    #     queryset = self.filter_queryset(self.get_queryset())
    #     page = self.paginate_queryset(queryset)
    #     if page is not None:
    #         serializer = self.get_serializer(page, many=True)
    #         # calculate the total number of pages based on the page size
    #         total_pages = queryset.count() // self.paginator.page_size + 1
    #         return self.get_paginated_response(serializer.data, total_pages)
    #
    #     serializer = self.get_serializer(queryset, many=True)
    #     return Response(serializer.data)
    #
    # def get_paginated_response(self, data, total_pages):
    #     return Response({
    #         'results': data,
    #         'page_count': total_pages
    #     })

