package work1;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class StudentDao {
    public static boolean updatePhone(String studentId, String newPhone) throws SQLException {
        String sql = "UPDATE students SET phone = ? WHERE student_id = ?";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, newPhone);
            pstmt.setString(2, studentId);
            return pstmt.executeUpdate() > 0;
        }
    }

    public static List<Student> getAllStudents() throws SQLException {
        List<Student> students = new ArrayList<>();
        String sql = "SELECT * FROM students";
        try (Connection conn = DBUtil.getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            while (rs.next()) {
                students.add(new Student(
                        rs.getString("student_id"),
                        rs.getString("name"),
                        rs.getString("phone")
                ));
            }
        }
        return students;
    }


}

