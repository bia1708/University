from rest_framework import generics, mixins
from rest_framework.pagination import PageNumberPagination
from rest_framework.response import Response
from movies.models import  *
from movies.serializer import *


class Pagination(PageNumberPagination):
    page_size = 10
    page_size_query_param = 'page_size'
    max_page_size = 100


class GetDirectorsWithBestMovies(generics.ListAPIView):
    queryset = Director.objects.annotate(avg_rating=Avg('movie__imdb_score')) \
            .order_by('-avg_rating')
    serializer_class = DirectorsWithBestMoviesSerializer
    pagination_class = Pagination

    def list(self, request, *args, **kwargs):
        queryset = self.filter_queryset(self.get_queryset())
        page = self.paginate_queryset(queryset)
        if page is not None:
            serializer = self.get_serializer(page, many=True)
            # calculate the total number of pages based on the page size
            total_pages = queryset.count() // self.paginator.page_size + 1
            return self.get_paginated_response(serializer.data, total_pages)

        serializer = self.get_serializer(queryset, many=True)
        return Response(serializer.data)

    def get_paginated_response(self, data, total_pages):
        return Response({
            'results': data,
            'page_count': total_pages
        })


class GetDirectorsWithNewestMovies(generics.ListAPIView):
    queryset = Director.objects.annotate(avg_release_date=Avg('movie__release_date')) \
            .order_by('-avg_release_date').filter(avg_release_date__gt=0)
    serializer_class = DirectorsWithNewestMoviesSerializer
