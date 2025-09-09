<?php session_start(); ?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Register UI</title>
    <link rel="stylesheet" href="design.css">
</head>

<body>
    <div class="form">
        <h2 align="center"><b><u>Register Here!</u></b></h2><br>

        <!-- Show session messages -->
        <?php
        if (isset($_SESSION['register_error'])) {
            echo "<p align='center' style='color: red; font-weight: bold;'>" . $_SESSION['register_error'] . "</p>";
            unset($_SESSION['register_error']); // clear message after showing
        }
        if (isset($_SESSION['register_success'])) {
            echo "<p align='center' style='color: green; font-weight: bold;'>" . $_SESSION['register_success'] . "</p>";
            unset($_SESSION['register_success']);
        }

        ?>
        <br>
        <form action="register.php" method="post">
            <input type="text" name="Name" placeholder="Name" required><br><br>
            <input type="email" name="Email" placeholder="Email" required><br><br>
            <input type="password" name="Password" placeholder="Password" required><br><br>
            <select name="Role" required>
                <option value="">--Select Role--</option>
                <option value="User">User</option>
                <option value="Admin">Admin</option>
            </select><br><br>
            <button type="submit" name="register">Register</button>
        </form>
        <br>
        <p>Already have Account? <a href="login.php">login </a>here!</p>
    </div>
</body>

</html>