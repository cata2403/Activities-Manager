# Activities Manager - C++ & Qt

A desktop activities management application developed during the Object-Oriented Programming (OOP) course. Through this project, I explored core C++ mechanisms beyond the basics, while gaining hands-on experience in building UIs with Qt.

---

## Key Features

* **Full CRUD System:** Add, delete, modify, and view tasks.
* **Undo Functionalitly:** Elegantly implemented via **polymorphism**, allowing users to revert previous actions.
* **Filtering & Sorting:** Algorithms for organizing data based on various criteria.
* **Multiple Windows:** Synchronized data visualization across multiple UI windows.
* **Custom Model (Qt Model-View Architecture):** Utilized a custom model to efficiently manage large volumes of data, optimizing memory usage and rendering speed.

---

## Architecture & OOP Concepts

* **Layered Architecture:** Clear separation between Domain, Repository, Service, and UI (Qt).
* **Polymorphism:** Leveraged for the **Undo** system using abstract `UndoAction` classes.
* **Memory Management:** Rigorous handling of resources (pointers, dynamic memory) to prevent memory leaks.
* **Unit Testing:** Extensive code coverage through unit tests to ensure business logic integrity.

---

## Tech Stack

* **Language:** C++
* **UI Framework:** Qt Framework
* **IDE:** Microsoft Visual Studio
