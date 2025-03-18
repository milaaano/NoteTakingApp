# NoteTaking App

A note taking web-application built with Django, designed for effortless note creation, management, and searching. This application is built for simplicity—all files are openly accessible without an authentication layer.

## Features

- **CRUD Operations:** Create, read, update, and delete notes seamlessly.
- **Advanced Search:**
  - **Default AND Operator:** By default, the search functionality uses the AND operator between words. Only notes containing all the specified words are returned.
  - **OR Operator Support:** Users can include the keyword `or` in their queries to retrieve notes that contain at least one of the words.
- **Snippets:** Each note displays a snippet, providing a quick preview of its content.
- **Responsive Design:** An intuitive interface that adapts to both desktop and mobile devices.

## Technical Tools & External Libraries

- **Python 3.x:** The primary programming language.
- **Django:** The high-level Python web framework used to build the application.
- **SQLite3:** The default database engine for development.
- **HTML/CSS/JavaScript:** Core technologies for building the front-end.
- **Bootstrap:** (Optional) Utilized for responsive and modern design elements.
- **Makefile:** Supports separate compilation. Run `make all` in the root directory to compile necessary components.
- **nlohmann/json:** External C++ library used to transfer data from Django to the C++ engine in JSON format. The JSON data is stored in a temporary file for further processing.
  
## Installation

1. **Clone the Repository:**

   ```bash
   git clone <repository-url>
   ```

2. **Create a Virtual Environment:**

   It is recommended to use a virtual environment for dependency management.

   ```bash
   pip3 install pipenv
   ```

3. **Install Dependencies:**

   Install the required packages using pip.

   ```bash
   pipenv install django
   ```

4. **Compile the Project:**

   Use the Makefile to perform separate C++ code compilation. Run the following command in the root directory:

   ```bash
   make all
   ```

## Running the Application

Start the application locally by running:

```bash
python NoteTakingDjango/manage.py runserver
```

Then, open your web browser and navigate to [http://127.0.0.1:8000/](http://127.0.0.1:8000/) to start using the app.

## Project Structure

```
.
├── Makefile
├── NoteTakingDjango
│   ├── NoteTakingDjango
│   │   ├── __init__.py
│   │   ├── asgi.py
│   │   ├── settings.py
│   │   ├── urls.py
│   │   └── wsgi.py
│   ├── db.sqlite3
│   ├── manage.py
│   └── notes
│       ├── __init__.py
│       ├── admin.py
│       ├── apps.py
│       ├── migrations
│       │   ├── 0001_initial.py
│       │   └── __init__.py
│       ├── models.py
│       ├── templates
│       │   ├── base.html
│       │   ├── detail.html
│       │   ├── index.html
│       │   ├── note_confirm_delete.html
│       │   └── note_form.html
│       ├── tests.py
│       ├── urls.py
│       └── views.py
├── Pipfile
├── Pipfile.lock
├── build
├── cpp_engine
│   ├── include
│   │   ├── note.h
│   │   └── search_engine.h
│   ├── src
│   │   ├── cpp_search.cpp
│   │   ├── cpp_search.o
│   │   ├── search_engine.cpp
│   │   └── search_engine.o
│   └── vendor
│       └── json.hpp
├── cpp_search
├── cpp_search.o
└── search_engine.o
```

## Contributing

Contributions are welcome! To contribute:
- Fork the repository.
- Create a new branch for your feature or bug fix.
- Commit your changes and push to your branch.
- Open a pull request detailing your modifications.

## License

This project is licensed under the [MIT License](LICENSE).

Happy Notetaking!
