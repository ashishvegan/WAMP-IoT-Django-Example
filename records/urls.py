from django.urls import path
from . import views

urlpatterns = [
    path('temperature/<str:temp_value>/', views.temperature_view, name='temperature_view'),
]
