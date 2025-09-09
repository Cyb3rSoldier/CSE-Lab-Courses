<?php session_start(); ?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login Page</title>
    <link rel="stylesheet" href="design.css">
</head>
<body>
    <div class="form">
        <h2><b><u>Login Here!</u></b></h2><br>

         <!-- Show session messages -->
        <?php
        if (isset($_SESSION['login_error'])) {
            echo "<p align='center' style='color: red; font-weight: bold;'>" . $_SESSION['login_error'] . "</p>";
            unset($_SESSION['login_error']); // clear message after showing
        }

        ?>
        <br>
        <form action="register.php" method="post">
            <input type="Email" name="Email" placeholder="Email" required><br><br>
            <input type="Password" name="Password" placeholder="Password" required><br><br>
            <button type="submit" name="login">login</button>
        </form>
        <br>
        <p>Don't have Account? <a href="registerIndex.php">register </a>here!</p>

    </div>
</body>
</html>