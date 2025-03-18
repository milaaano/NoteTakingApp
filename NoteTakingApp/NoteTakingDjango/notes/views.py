from django.shortcuts import render
from django.views.generic import ListView, DetailView, CreateView, UpdateView, DeleteView
from .models import Note
from django.urls import reverse_lazy
from django.conf import settings
import os
import subprocess
import json
import tempfile


class NoteListView(ListView):
    template_name = 'index.html'
    context_object_name = "notes"

    def get_queryset(self):
        query = self.request.GET.get('q', '').strip()
        if query:
            # Here we put all the information about notes in json format to prepare it for the C++ engine
            notes_data = [
                {"id": note.id, "content": note.content}
                for note in Note.objects.all()
            ]
            # Now we need to write json data in a temporary file,
            # cuz we want to have a new input for C++ engine for each query
            with tempfile.NamedTemporaryFile(mode='w+', delete=False) as tmp:
                # .dump put the first argument (python object)
                # in tmp (json file)
                json.dump(notes_data, tmp)
                # tmp_path is the absolute path of the tmp file
                tmp_path = tmp.name

            project_root = os.path.dirname(settings.BASE_DIR)
            cpp_search_executable = os.path.join(project_root, "cpp_search")

            try:
                # Here we try to execute the following code
                # Subprocess allows us to run other programs, in our case its bash script
                # which executes binary executable cpp search with query and tmp_path as arguments
                output = subprocess.check_output([cpp_search_executable, query, tmp_path], stderr=subprocess.STDOUT)
                print("Raw output from C++ engine:", output.decode('utf-8'))
                results = json.loads(output.decode('utf-8'))
            except Exception as e:
                print("Error in calling C++ engine:", e)
                results = []

            # This list is what we are gonna return
            notes_with_snippet = []
            for result in results:
                try:
                    # Here we get a note with id, returned from C++ engine
                    note = Note.objects.get(id=result["id"])
                    # Here we create a temporary model field "snipped"
                    # it will not be stored in database
                    note.snippet = result.get("snippet", "")
                    notes_with_snippet.append(note)
                except Note.DoesNotExist:
                    continue
            return notes_with_snippet
        else:
            return Note.objects.all().order_by('-created_at')


class NoteDetailView(DetailView):
    model = Note
    template_name = 'detail.html'
    context_object_name = 'note'


class NoteCreateView(CreateView):
    model = Note
    fields = ['title', 'content']
    template_name = 'note_form.html'
    success_url = reverse_lazy('notes:index')


class NoteUpdateView(UpdateView):
    model = Note
    fields = ['title', 'content']
    template_name = 'note_form.html'
    success_url = reverse_lazy('notes:index')


class NoteDeleteView(DeleteView):
    model = Note
    template_name = 'note_confirm_delete.html'
    success_url = reverse_lazy('notes:index')
