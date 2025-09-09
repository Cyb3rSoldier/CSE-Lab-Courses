<?php
session_start();
require_once 'config.php';

// REGISTER
if (isset($_POST['register'])) {
    $name = $_POST['Name'];
    $email = $_POST['Email'];
    $password = password_hash($_POST['Password'], PASSWORD_DEFAULT);
    $role = $_POST['Role'];

    // Check if email exists
    $stmt = $conn->prepare("SELECT Email FROM users WHERE Email = ?");
    $stmt->bind_param("s", $email);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows > 0) {
        $_SESSION['register_error'] = "Email already exists! Please login.";
        $_SESSION['active_form'] = "register";
    } else {
        $stmt = $conn->prepare("INSERT INTO users (Name, Email, Password, Role) VALUES (?, ?, ?, ?)");
        $stmt->bind_param("ssss", $name, $email, $password, $role);
        $stmt->execute();

        $_SESSION['register_success'] = "You have registered successfully! Please login now.";
        $_SESSION['active_form'] = "login";
    }

    header("Location: registerIndex.php");
    exit();
}

// LOGIN
if (isset($_POST['login'])) {
    $email = $_POST['Email'];
    $password = $_POST['Password'];

    $stmt = $conn->prepare("SELECT * FROM users WHERE Email = ?");
    $stmt->bind_param("s", $email);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($row = $result->fetch_assoc()) {
        if (password_verify($password, $row['Password'])) {
            // store session
            $_SESSION['Name']  = $row['Name'];
            $_SESSION['Email'] = $row['Email'];
            $_SESSION['Role']  = $row['Role'];

            // redirect by role
            if ($row['Role'] === 'Admin') {
                header("Location: Admin_Page.php");
                exit();
            } else {
                header("Location: User_Page.php");
                exit();
            }
        }
    }

    // login failed
    $_SESSION['login_error'] = 'Incorrect email or password';
    $_SESSION['active_form'] = "login";
    header("Location: login.php");
    exit();
}
?>
