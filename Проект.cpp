#include <string>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;
// Базовый класс пользователя
class User {
protected:
    size_t id;
    string first_name;
    string secont_name;
    string last_name;
    
public:
    User();
    User(size_t id, string first_name, string second_name, string last_name);
    size_t GetId() const;
    string GetName() const;
    void SetId(size_t new_id);
};

// Конструктор по умолчанию
User::User() {
    id = 0;
    first_name = "";
    secont_name = "";
    last_name = "";
}

// Конструктор инпициализации
User::User(size_t id, string first_name, string secont_name, string last_name) {
    this->id = id;
    this->first_name = first_name;
    this->secont_name = secont_name;
    this->last_name = last_name;
}

// Метод получения ID
size_t User::GetId() const {
    return id;
}

// Получение ФИО
string User::GetName() const {
    return first_name + " " + secont_name + " " + last_name;
}

// Создание нового ID, чтобы все были уникальными
void User::SetId(size_t new_id) {
    id = new_id;
}

// Степени обучения
enum Degree {
  Bachelaur,
  Master,
  Doctor
};

// Класс студента
class Student : public User {
private:
    Degree degree;
    string group;
    size_t enrollment_year;
    size_t manufacture_year;
    
public:
    Student();
    Student(
        size_t id,
        string first_name,
        string second_name,
        string last_name,
        string group,
        Degree,
        size_t enrollment_year,
        size_t manufacture_year
    );
    string GetGroup() const;
    Degree GetDegree() const;
    size_t GetEnrollmentYear() const;
    size_t GetManufactureYear() const;
    void SetManufactureYear(size_t year);
    bool Graduated() const;
};

// Конструтор по умолчанию для студента
Student::Student() : User() {}

// Конструтор инициалзации студента
Student::Student(
    size_t id,
    string first_name,
    string second_name,
    string last_name,
    string group,
    Degree deg,
    size_t enrollment_year,
    size_t manufacture_year
) : User(id, first_name, second_name, last_name) {
    this->group = group;
    this->degree = deg;
    this->enrollment_year = enrollment_year;
    this->manufacture_year = manufacture_year;
}

// Методы для студента
string Student::GetGroup() const {
    return group;
}

Degree Student::GetDegree() const {
    return degree;
}

size_t Student::GetEnrollmentYear() const {
    return enrollment_year;
}

size_t Student::GetManufactureYear() const {
    return manufacture_year;
}

void Student::SetManufactureYear(size_t year) {
    manufacture_year = year;
}

bool Student::Graduated() const {
    return manufacture_year != 0;
}

// Класс учитель
class Teacher : public User {
public:
    Teacher();
    Teacher(
        size_t id,
        string first_name,
        string second_name,
        string last_name
    );
};

// Конструктор по умолчанию
Teacher::Teacher() : User() {}

// Конструктор инициализации
Teacher::Teacher(
    size_t id,
    string first_name,
    string second_name,
    string last_name
) : User(id, first_name, second_name, last_name) {}

// Класс курс
class Course {
private:
    size_t id;
    unordered_set<size_t> students;
    unordered_set<size_t> teachers;
    unordered_set<size_t> assistants;
    
public:
    Course();
    Course(size_t id);
    bool AddStudent(size_t student_id);
    bool RemoveStudent(size_t student_id);
    bool AddTeacher(size_t teacher_id);
    bool RemoveTeacher(size_t teacher_id);
    size_t GetId() const;
    void SetId(size_t new_id);
};

// Конструктор по умолчанию
Course::Course() {
    id = 0;
}

// Конструктор инициализации
Course::Course(size_t id) {
    this->id = id;
}

// Методы курса
size_t Course::GetId() const {
    return id;
}

void Course::SetId(size_t new_id) {
    id = new_id;
}

bool Course::AddStudent(size_t student_id) {
    return students.insert(student_id).second;
}
bool Course::AddTeacher(size_t teacher_id) {
    return teachers.insert(teacher_id).second;
}
bool Course::RemoveStudent(size_t student_id) {
    return students.erase(student_id);
}
bool Course::RemoveTeacher(size_t teacher_id) {
    return teachers.erase(teacher_id);
}

// Перечисление типов пар
enum ScheduleEntryType {
    Lecture,
    Seminar,
    Practice,
    Exam
};

// Структура даты
struct Timestamp {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    bool operator==(const Timestamp& other) const {
        return year == other.year && \
            month == other.month && \
            day == other.day && \
            hour == other.hour && \
            minute == other.minute && \
            second == other.second;
    }
};

//Хэш функция для даты
template<>
struct std::hash<Timestamp> {
    size_t operator() (const Timestamp& ts) const {
        return hash<int>()(ts.year + ts.month + ts.day + ts.hour + ts.minute + ts.second);
    }
};

// Структура пары
struct ScheduleEntry {
    ScheduleEntryType type;
    size_t teacher_id;
    size_t course_id;
};

// Класс расписания
class Schedule {
private:
    unordered_map<Timestamp, ScheduleEntry> entries;
    
public:
    bool AddEntry(Timestamp, ScheduleEntry);
    bool RemoveEntry(Timestamp);
    bool UpdateEntry(Timestamp, ScheduleEntry);
    ScheduleEntry GetEntry(Timestamp) const;
};

// Перечисление методов
bool Schedule::AddEntry(Timestamp date, ScheduleEntry entry) {
    return entries.insert({ date, entry }).second;
}

bool Schedule::RemoveEntry(Timestamp date) {
    return entries.erase(date) == 1;
}

bool Schedule::UpdateEntry(Timestamp date, ScheduleEntry entry) {
    if (entries.count(date) == 0) return false;
    entries[date] = entry;
    return true;
}

ScheduleEntry Schedule::GetEntry(Timestamp date) const {
    return entries.at(date);   
}

// Структура записи в журнале
struct JournalEntry {
    Course course;
    int grade;
    Timestamp date;

    JournalEntry(const Course& course, int grade, const Timestamp& date) {
        this->course = course;
        this->grade = grade;
        this->date = date;
    }

    bool operator==(const JournalEntry& other) const {
        return course.GetId() == other.course.GetId() && \
            grade == other.grade && \
            date == other.date;
    }
};

// Класс журнал
class Journal {
private:
    unordered_map<size_t, vector<JournalEntry>> data;
    
public:
    void AddEntry(size_t student_id, JournalEntry);
    void RemoveEntry(size_t student_id, JournalEntry);
    vector<JournalEntry> GetEntries(size_t student_id) const;
    vector<size_t> GetStudentsBelowThreshold(double threshold) const;
    double GetAverageGrade(size_t student_id) const;
};

// Методы для журнала
void Journal::AddEntry(size_t student_id, JournalEntry entry) {
    data[student_id].push_back(entry);
}

void Journal::RemoveEntry(size_t student_id, JournalEntry entry) {
    vector<JournalEntry> entries = data[student_id];
    entries.erase(find(entries.begin(), entries.end(), entry));
}

vector<JournalEntry> Journal::GetEntries(size_t student_id) const {
    return data.at(student_id);
}

//Основной класс системы
class UniversitySystem {
private:
    Journal journal;
    Schedule schedule;

    unordered_map<size_t, Course> courses;
    unordered_map<size_t, Student> students;
    unordered_map<size_t, Teacher> teachers;

    size_t last_student_id = -1;
    size_t last_teacher_id = -1;
    size_t last_course_id = -1;

    size_t GenerateStudentId();
    size_t GenerateTeacherId();
    size_t GenerateCourseId();
    
public:
    UniversitySystem(const Journal& journal, const Schedule& schedule);

    void AddStudent(Student&);
    void AddTeacher(Teacher&);
    void AddCourse(Course&);

    Student GetStudent(size_t id) const;
    Teacher GetTeacher(size_t id) const;
    Course GetCourse(size_t id) const;
};

// Методы для системы
UniversitySystem::UniversitySystem(const Journal& journal, const Schedule& schedule) {
    this->journal = journal;
    this->schedule = schedule;
}

size_t UniversitySystem::GenerateStudentId() {
    return ++last_student_id;
}
size_t UniversitySystem::GenerateTeacherId() {
    return ++last_teacher_id;
}
size_t UniversitySystem::GenerateCourseId() {
    return ++last_course_id;
}

void UniversitySystem::AddStudent(Student& student) {
    size_t new_id = GenerateStudentId();
    student.SetId(new_id);
    students.insert({ new_id, student });
}
void UniversitySystem::AddTeacher(Teacher& teacher) {
    size_t new_id = GenerateTeacherId();
    teachers.insert({ new_id, teacher });
}
void UniversitySystem::AddCourse(Course& course) {
    size_t new_id = GenerateCourseId();
    course.SetId(new_id);
    courses.insert({ new_id, course });
}
// Методы для аналитики
Student UniversitySystem::GetStudent(size_t student_id) const {
    return students.at(student_id);
}
Teacher UniversitySystem::GetTeacher(size_t teacher_id) const {
    return teachers.at(teacher_id);
}
Course UniversitySystem::GetCourse(size_t course_id) const {
    return courses.at(course_id);
}

// Метод для получения среднего балла студента
double Journal::GetAverageGrade(size_t student_id) const {
    const auto& entries = data.at(student_id);
    if (entries.empty()) return 0.0;

    int total_grade = 0;
    for (const auto& entry : entries) {
        total_grade += entry.grade;
    }
    return static_cast<double>(total_grade) / entries.size();
}

// Метод для получения списка студентов, у которых средний балл ниже порогового
vector<size_t> Journal::GetStudentsBelowThreshold(double threshold) const {
    vector<size_t> result;
    for (const auto& [student_id, entries] : data) {
        double average = GetAverageGrade(student_id);
        if (average < threshold) {
            result.push_back(student_id);
        }
    }
    return result;
}

// Тесты
bool test(size_t test_id) {
    switch (test_id) {
    case 1: {
        User u1(0, "A", "B", "C");
        assert(u1.GetId() == 0);
        assert(u1.GetName() == "A B C");
    }
          break;

    case 2: {
        Student s1(1, "D", "E", "F", "BIV235", Degree::Bachelaur, 2020, 2024);
        assert(s1.GetGroup() == "BIV235");
    }
          break;

    case 3: {
        Student s1(0, "A", "B", "C", "BOBA", Degree::Bachelaur, 2020, 2024);
        Timestamp ts{
            2024, 11, 1, 19, 12, 0
        };
        JournalEntry entry(Course(0), 10, ts);
        Journal journal;
        journal.AddEntry(0, entry);
        auto entries = journal.GetEntries(0);
        assert(entries[0].grade == 10);
        assert(entries[0].date == ts);
        assert(entries[0].course.GetId() == 0);
    }
          break;

    case 4: {
        // Тест на добавление записей в расписание
        Schedule schedule;
        Timestamp ts{ 2024, 12, 2, 10, 0, 0 };
        ScheduleEntry entry{ Lecture, 1, 101 };
        assert(schedule.AddEntry(ts, entry));
        assert(!schedule.AddEntry(ts, entry)); // Повторное добавление того же времени не должно сработать
        assert(schedule.RemoveEntry(ts));     // Удаление должно пройти успешно
        assert(!schedule.RemoveEntry(ts));    // Повторное удаление не должно сработать
    }
          break;

    case 5: {
        // Тест на аналитику: средний балл
        Journal journal;
        Timestamp ts{ 2024, 11, 1, 19, 12, 0 };
        journal.AddEntry(1, JournalEntry(Course(101), 5, ts));
        journal.AddEntry(1, JournalEntry(Course(102), 7, ts));
        journal.AddEntry(1, JournalEntry(Course(103), 9, ts));
        assert(journal.GetAverageGrade(1) == 7.0); // Средний балл: (5+7+9)/3
    }
          break;

    case 6: {
        // Тест на аналитику: список студентов ниже порогового значения
        Journal journal;
        Timestamp ts{ 2024, 11, 1, 19, 12, 0 };
        journal.AddEntry(1, JournalEntry(Course(101), 5, ts));
        journal.AddEntry(2, JournalEntry(Course(102), 8, ts));
        journal.AddEntry(3, JournalEntry(Course(103), 6, ts));
        auto below_threshold = journal.GetStudentsBelowThreshold(7.0);
        assert(below_threshold.size() == 2); // Студенты 1 и 3 имеют средний балл ниже 7.0
        assert(find(below_threshold.begin(), below_threshold.end(), 1) != below_threshold.end());
        assert(find(below_threshold.begin(), below_threshold.end(), 3) != below_threshold.end());
    }
          break;

    case 7: {
        // Тест на добавление студентов, преподавателей и курсов в систему
        Journal journal;
        Schedule schedule;
        UniversitySystem uniSystem(journal, schedule);
        Student student(0, "John", "M.", "Doe", "BIV202", Degree::Master, 2024, 2026);
        Teacher teacher(0, "Dr.", "Jane", "Smith");
        Course course(0);
        uniSystem.AddStudent(student);
        uniSystem.AddTeacher(teacher);
        uniSystem.AddCourse(course);

        assert(uniSystem.GetStudent(0).GetName() == "John M. Doe");
        assert(uniSystem.GetTeacher(0).GetName() == "Dr. Jane Smith");
        assert(uniSystem.GetCourse(0).GetId() == 0);
    }
          break;

    case 8: {
        // Тест на добавление студента к курсу
        Course course(101);
        assert(course.AddStudent(1));
        assert(!course.AddStudent(1)); // Повторное добавление одного и того же студента
        assert(course.RemoveStudent(1));
        assert(!course.RemoveStudent(1)); // Удаление студента, которого уже нет
    }
    break;

    case 9: {
        // Тест на обновление записи в расписании
        Schedule schedule;
        Timestamp ts{ 2024, 12, 2, 10, 0, 0 };
        ScheduleEntry entry1{ Lecture, 1, 101 };
        ScheduleEntry entry2{ Seminar, 2, 102 };
        assert(schedule.AddEntry(ts, entry1));
        assert(schedule.UpdateEntry(ts, entry2)); // Обновление существующей записи
        ScheduleEntry updated_entry = schedule.GetEntry(ts);
        assert(updated_entry.type == Seminar);
        assert(updated_entry.teacher_id == 2);
        assert(updated_entry.course_id == 102);
    }
    break;
    case 10: {
        //Зачисление и выпуск студента
        Student s1(0, "A", "B", "C", "BIV235", Degree::Bachelaur, 2024, 0);
        assert(s1.GetDegree() == Degree::Bachelaur);
        assert(s1.GetEnrollmentYear() == 2024);
        assert(s1.Graduated() == false);
        s1.SetManufactureYear(2028);
        assert(s1.Graduated());
    }
    break;

    default:
        return false; // Если номер теста не соответствует ни одному из сценариев
    }
    return true; // Если тест выполнен успешно
}

int main() {
    size_t cur_test = 1;
    while (test(cur_test)) {
        cout << "Test #" << cur_test << " passed" << endl;
        cur_test++;
    }
    cout << "ALL TESTS PASSED" << endl;
}
