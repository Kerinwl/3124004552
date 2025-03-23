package work1;

public class Student {
    private String studentId;
    private String name;
    private String phone;

    public Student(String studentId, String name, String phone) {
        this.studentId = studentId;
        this.name = name;
        this.phone = phone;
    }

    public  Object getStudentId() {
        return studentId;
    }
    public Object getName() {
        return name;
    }
    public String getPhone() {
        return phone;
    }
}
