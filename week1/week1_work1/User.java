package work1;

public class User {
    private static int id;
    private static String username;
    private static String password;
    private static String role;

    public User(int id, String username, String password, String role) {
        this.id = id;
        this.username = username;
        this.password = password;
        this.role = role;
    }

    public static String getPassword() {
        return password;
    }

    public static Object getRole() {
        return role;
    }
    public static int getId() {
        return id;
    }
    public static String getUsername() {
        return username;
    }

}
