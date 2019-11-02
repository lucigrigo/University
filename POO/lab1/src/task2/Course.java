package task2;

import java.util.ArrayList;


public class Course {
    private String title, description;
    private ArrayList<Student> students = new ArrayList<>();

    public void setTitle(String title) {
        this.title = title;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setStudents(ArrayList<Student> students) {
        this.students = students;
    }

    public String getTitle() {
        return title;
    }

    public String getDescription() {
        return description;
    }

    public ArrayList<Student> getStudents() {
        return students;
    }

    public ArrayList<Student> filterYear(ArrayList<Student> students, int year){
        ArrayList<Student> resultList = new ArrayList<>();
        for(Student student : students){
            if(student.getYear() == year){
                resultList.add(student);
            }
        }
        return resultList;
    }
}
