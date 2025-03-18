from django.urls import path
from .views import (
    NoteListView,
    NoteDetailView,
    NoteCreateView,
    NoteUpdateView,
    NoteDeleteView,
)

# Define a namespace
app_name = 'notes'

urlpatterns = [
    path('', NoteListView.as_view(), name='index'),
    path('note/<int:pk>/', NoteDetailView.as_view(), name='detail'),
    path('note/create', NoteCreateView.as_view(), name='create'),
    path('note/<int:pk>/update', NoteUpdateView.as_view(), name='update'),
    path('note/<int:pk>/delete', NoteDeleteView.as_view(), name='delete'),
]