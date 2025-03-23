/*package work1;
import java.sql.*;

import static java.lang.Class.forName;

public class JDBC
{

       //1.加载驱动
       Class.forName("com.mysql.jdbc.Driver");
       //2.用户信息
       String url = "jdbc:mysql://localhost:3306/users?useSSL=false";
       String user = "root";
       String password = "061115Wkl";
    /*   //3.连接数据库对象
       Connection connection=DriverManager.getConnection(url,user,password);
       //4.执行sql对象
       Statement statement=connection.createStatement();

       String sql1 = "select * from users";
       ResultSet resultSet=statement.executeQuery(sql1);
       /*while(resultSet.next()){
           System.out.println(resultSet.getString("id"));
           System.out.println(resultSet.getString("username"));
           System.out.println(resultSet.getString("password"));
           System.out.println(resultSet.getString("role"));

       }*/
       //5.释放连接
      /* resultSet.close();
       statement.close();
       connection.close();
}*/


