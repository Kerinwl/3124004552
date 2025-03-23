package work1;

public class Courses {
     int courseId;
     String courseName;
     int credit;
     boolean startStatus;

    public Courses(int courseId, String courseName,int credit ) {
        this.courseId = courseId;
        this.courseName = courseName;
        this.credit =credit;
        this.startStatus = startStatus;

    }


   public Object getCourseName() {
        return courseName;
    }
    public Object getCredit() {
        return credit;
    }
    public Object getCourseId() {
        return courseId;
    }
}
