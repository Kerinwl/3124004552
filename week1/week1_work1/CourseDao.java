package work1;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.Callable;

//import static work1.mainsystem.scanner;


public class CourseDao {
    public static boolean addCourse(String courseName, int credit) throws SQLException {
        String sql = "INSERT INTO courses (course_name, credit) VALUES (?, ?)";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, courseName);
            pstmt.setInt(2, credit);
            return pstmt.executeUpdate() > 0;
        }
    }

    public static boolean deleteCourse(int courseId) throws SQLException {
        String sql = "DELETE FROM courses WHERE course_id = ?";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setInt(1, courseId);
            return pstmt.executeUpdate() > 0;
        }
    }


    public static List<Courses> getAllcourses() throws SQLException {
        List<Courses> courses = new ArrayList<>();
        String sql = "SELECT * FROM courses";
        try (Connection conn = DBUtil.getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            while (rs.next()) {
                courses.add(new Courses(rs.getInt("course_id"),
                        rs.getString("course_name"),
                        rs.getInt("credit")));

            }
        }
        return courses;
    }

    public static boolean courseChoice(int student_id, int course_id) throws SQLException {
        String sql = "INSERT INTO student_courses (student_id,course_id) VALUES (?, ?)";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setInt(1, student_id);
            pstmt.setInt(2, course_id);

            return pstmt.executeUpdate() > 0;
        }
    }

    public static boolean dropCourse(int student_id, int course_id) throws SQLException {
        String sql = "DELETE FROM student_courses WHERE (student_id,course_id) values = (?,?)";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setInt(1, student_id);
            pstmt.setInt(2, course_id);
            return pstmt.executeUpdate() > 0;
        }
    }

    public static List<Courses> getSelectedCourses(String studentId) throws SQLException {
        List<Courses> courses = new ArrayList<>();
        String sql = "SELECT c.course_id, c.course_name, c.credit " +
                "FROM courses c " +
                "JOIN student_courses sc ON c.course_id = sc.course_id " +
                "WHERE sc.student_id = ?";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, studentId);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                courses.add(new Courses(
                        rs.getInt("course_id"),
                        rs.getString("course_name"),
                        rs.getInt("credit")
                ));
            }
        }
        return courses;
    }
}



