<?php
session_start();

// Block if not logged in
if (!isset($_SESSION['Email'])) {
    header("Location: login.php");
    exit();
}

// Block if not admin
if ($_SESSION['Role'] !== 'Admin') {
    header("Location: User_Page.php");
    exit();
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <h2 align="center">Hello <?php echo htmlspecialchars($_SESSION['Name']); ?>, Welcome to Admin Page!</h2>
    <a href="logout.php">Logout</a>
</body>

</html>