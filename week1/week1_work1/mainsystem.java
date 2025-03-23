package work1;
import java.util.*;
import java.sql.SQLException;
import java.util.Scanner;

//import static mainsystem.scanner;

public class mainsystem {
    private static Scanner scanner = new Scanner(System.in);
    private static UserDAO userDAO = new UserDAO();

    public static void main(String[] args) {
        while (true) {
            System.out.println("===========================\n🎓 学生选课管理系统\n===========================");
            System.out.println("1. 登录");
            System.out.println("2. 注册");
            System.out.println("3.修改密码");
            System.out.println("4.查看基本信息");
            System.out.println("5.退出");
            System.out.print("请选择操作（输入 1-5）：");
            //System.out.println("===========================\n🎓 学生选课管理系统\n===========================");
            int choice = scanner.nextInt();
            scanner.nextLine(); // 清除缓冲区

            switch (choice) {
                case 1:
                    login();
                    break;
                case 2:
                    register();
                    break;
                case 3:
                    System.out.print("请输入用户姓名：");
                    String userName = scanner.nextLine();
                    System.out.print("请输入新密码：");
                    String newPassword = scanner.nextLine();
                    try {
                        UserDAO.updatePassword(userName, newPassword);
                    } catch (SQLException e) {
                        e.printStackTrace();
                    }
                    break;
                case 4:
                    System.out.print("请输入用户姓名: ");
                    String username = scanner.next();
                    System.out.println("请输入用户密码");
                    String password = scanner.next();
                    UserDAO userDAO = new UserDAO();
                    try {
                        List<User>list= (List<User>) UserDAO.getUserInformation(username,password);
                        for (User user : list) {
                            System.out.println("User ID: " + User.getId() + "\nName: " + User.getUsername()
                                    +"\nPassword:" + User.getPassword()+"\nRole:"+User.getRole());
                        }
                    } catch (SQLException ex) {
                        throw new RuntimeException(ex);
                    }
                    break;
                case 5:
                    System.exit(0);
                default:
                    System.out.println("输入无效，请重新选择！");
            }
        }
    }

    private static void login() {
        System.out.print("请输入用户名：");
        String username = scanner.nextLine();
        System.out.print("请输入密码：");
        String password = scanner.nextLine();

        try {
            User user = userDAO.login(username, password);
            if (user != null) {
                System.out.println("登录成功！你的角色是：" + user.getRole());
                if (user.getRole().equals("admin")) {
                    adminMenu();
                } else {
                    studentMenu();
                }
            } else {
                System.out.println("用户名或密码错误！");
                System.out.println("请重新输入用户信息");
                 String repassword = scanner.nextLine();//重新输入的密码
               relogin();

            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }//登录

    private static void relogin() {
        System.out.print("请输入用户名：");
        String username = scanner.nextLine();
        System.out.print("请输入密码：");
        String password = scanner.nextLine();

        try {
            User user = userDAO.login(username, password);
            if (user != null) {
                System.out.println("登录成功！你的角色是：" + user.getRole());
                if (user.getRole().equals("admin")) {
                    adminMenu();
                } else {
                    studentMenu();
                }
            } else {
                System.exit(0);
            }
        } catch (SQLException e) {
            System.out.println("登录失败!");
            e.printStackTrace();
        }
    }//重新登录

    private static void register() {
        System.out.print("请输入用户名：");
        String username = scanner.nextLine();
        System.out.print("请输入密码：");
        String password = scanner.nextLine();
        System.out.print("请选择角色（1 学生，2 管理员）：");
        int roleChoice = scanner.nextInt();
        scanner.nextLine(); // 清除缓冲区
        String role = roleChoice == 1 ? "student" : "admin";

        try {
            if (userDAO.register(username, password, role)) {
                System.out.println("注册成功！请返回主界面登录。");
            } else {
                System.out.println("注册失败，请重试！");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }//注册
/*--------------------------------------------------------------------------------------------------------------------------*/
private static void adminMenu() {
    while (true) {
        System.out.println("===========================\n 管理员菜单\n===========================");
        System.out.println("1. 查询所有学生");
        System.out.println("2. 修改学生手机号");
        System.out.println("3. 查询所有课程");
        System.out.println("4. 删除课程");
        System.out.println("5. 增加课程");
        System.out.println("6. 退出");
        int choice = scanner.nextInt();
        scanner.nextLine(); // 清除缓冲区

        switch (choice) {
            case 1:
                try {
                    List<Student> students = StudentDao.getAllStudents();
                    students.forEach(s -> System.out.println(s.getName() + " - " + s.getPhone()));
                } catch (SQLException e) {
                    e.printStackTrace();
                }
                break;
            case 2:
                System.out.print("请输入学生ID：");
                String studentId = scanner.nextLine();
                System.out.print("请输入新手机号：");
                String newPhone = scanner.nextLine();
                try {
                    StudentDao.updatePhone(studentId, newPhone);
                } catch (SQLException e) {
                    e.printStackTrace();
                }
                break;
            case 3:
                try {
                    List<Courses> courses = CourseDao.getAllcourses();
                    courses.forEach(s -> System.out.println(s.getCourseName() + " -学分: " + s.getCredit()));
                } catch (SQLException e) {
                    e.printStackTrace();
                }
                break;
            case 4:
                System.out.print("请输入要删除的课程ID：");
                int courseId = scanner.nextInt();
                scanner.nextLine(); // 清除缓冲区
                try {
                    CourseDao.deleteCourse(courseId);
                } catch (SQLException e) {
                    e.printStackTrace();
                }
                break;
            case 5:
                /*System.out.println("请输入要添加的课程名称及学分:");
                String AddcourseName = String.valueOf(scanner.nextInt());
                int Addcredit = scanner.nextInt();
                scanner.nextLine(); // 清除缓冲区
                try {
                    CourseDao.addCourse(AddcourseName,Addcredit);
                } catch (SQLException e) {
                    e.printStackTrace();
                }*/
                //private static void addNewCourse() {
                System.out.print("\n请输入新课程名称 ");
                String newCourse = scanner.next();
                System.out.print("请输入新课程学分: ");
                int newCredit = Integer.parseInt(scanner.next());

                try {
                    if (CourseDao.addCourse(newCourse, newCredit)) {
                        System.out.println("添加成功！");
                    } else {
                        System.out.println("该课程不存在！");
                    }
                } catch (SQLException e) {
                    System.out.println("添加失败: " + e.getMessage());
                }

            case 6:
                return;
            default:
                System.out.println("输入无效，请重新选择！");
        }
    }
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/
private static void studentMenu() {
    while (true) {
        System.out.println("===========================\n 学生菜单\n===========================");
        System.out.println("1. 查看可选课程");
        System.out.println("2. 选课");
        System.out.println("3. 退课");
        System.out.println("4. 查看已选课程");
        System.out.println("5. 修改手机号");
        System.out.println("6. 退出");
        int choice = scanner.nextInt();
        scanner.nextLine(); // 清除缓冲区

        switch (choice) {
            case 1:
                try {
                List<Courses> courses = CourseDao.getAllcourses();
                courses.forEach(s -> System.out.println(s.getCourseName() + " -学分: " + s.getCredit()));
            } catch (SQLException e) {
                e.printStackTrace();
            }
                break;

            case 2:
                System.out.println("请输入学生ID:");
                int studentId = scanner.nextInt();
                System.out.print("请输入所选课程ID：");
                int courseId = scanner.nextInt();
                scanner.nextLine(); // 清除缓冲区
                try {
                    if (CourseDao.courseChoice(studentId, courseId)) {
                        System.out.println("添加成功！请返回主界面登录。");
                    } else {
                        System.out.println("添加失败");
                    }
                } catch (SQLException e) {
                    e.printStackTrace();
                }
                break;
            case 3:
                System.out.println("请输入退课人ID");
                int dropStudentId = scanner.nextInt();
                System.out.print("请输入退课ID：");
                int dropCourseId = scanner.nextInt();
                scanner.nextLine(); // 清除缓冲区
                try {
                    CourseDao.dropCourse(dropStudentId,dropCourseId);
                } catch (SQLException e) {
                    e.printStackTrace();
                }
                break;
            case 4:
                System.out.print("\n请输入学生ID: ");
                String StudentId = scanner.next();
                CourseDao courseDao = new CourseDao();
                try {
                    List<Courses>list=courseDao.getSelectedCourses(StudentId);
                    for (Courses course : list) {
                        System.out.println("Course ID: " + course.getCourseId() + ", Name: " + course.getCourseName() +"Credit:" + course.getCredit());
                    }
                } catch (SQLException ex) {
                    throw new RuntimeException(ex);
                }
                break;
            case 5:
                System.out.print("请输入新手机号：");
                String newPhone = scanner.nextLine();
                try {
                    StudentDao.updatePhone(User.getUsername(), newPhone);
                } catch (SQLException e) {
                    e.printStackTrace();
                }
                break;
            case 6:
                return;
            default:
                System.out.println("输入无效，请重新选择！");
        }
    }
}
}